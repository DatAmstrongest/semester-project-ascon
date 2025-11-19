#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ascon.h"
#include "simpleserial.h"
#include "hal.h"

// --- Global Context and Buffers ---

// Global ASCON context (320 bits)
ascon_ctx_t ascon_ctx;

// Key buffer (128 bits) - Key remains static
uint8_t key[ASCON_KEY_LEN];

// Utility buffer for returning the 40-byte state
uint8_t state_output[ASCON_STATE_WORDS * 8];

// --- SimpleSerial Command Handlers ---

/**
 * @brief SimpleSerial command to set the 16-byte key ('k').
 * Format: k<16-byte-hex-key>
 */
uint8_t set_key(uint8_t* data, uint8_t len) {
    if (len != ASCON_KEY_LEN) return 0x01; // Error: Incorrect length

    memcpy(key, data, ASCON_KEY_LEN);
    return 0x00; // Success
}

/**
 * @brief SimpleSerial command to perform the ASCON initialization.
 *
 * Mapped to 'p' (Plaintext/Payload).
 * The input 'data' IS the 16-byte Nonce.
 * Format: p<16-byte-hex-nonce>
 * Returns: 40-byte final state (after initialization)
 */
uint8_t do_init_with_nonce(uint8_t* data, uint8_t len) {
    // Check if the Nonce length is correct (16 bytes)
    if (len != ASCON_NONCE_LEN) return 0x01;

    // 1. Set the trigger high to start capture
    trigger_high();

    // 2. Perform the ASCON initialization phase
    // We pass 'data' directly as the nonce.
    ascon_init(&ascon_ctx, key, data);

    // 3. Set the trigger low to stop capture
    trigger_low();

    // 4. Copy the resulting state to the output buffer
    ascon_state_to_bytes(state_output, &ascon_ctx);

    // 5. Send the 40-byte final state back to the host
    // CORRECTION HERE: Changed simpleserial_write to simpleserial_put
    simpleserial_put('r', ASCON_STATE_WORDS * 8, state_output);

    return 0x00; // Success
}

/**
 * @brief Command to reset the key and context ('z').
 */
uint8_t reset_ascon(uint8_t* data, uint8_t len) {
    (void)data; // unused
    (void)len;  // unused

    memset(&ascon_ctx, 0, sizeof(ascon_ctx_t));
    memset(key, 0, ASCON_KEY_LEN);
    
    return 0x00; // Success
}

// --- Main Program Loop ---

int main(void) {
    // Initialize hardware and SimpleSerial
    platform_init();
    init_uart();
    trigger_setup();

    // Define the SimpleSerial commands
    simpleserial_addcmd('k', ASCON_KEY_LEN, set_key);               // Set Key (Static)
    simpleserial_addcmd('p', ASCON_NONCE_LEN, do_init_with_nonce);  // Input Nonce & Trigger
    simpleserial_addcmd('z', 0, reset_ascon);                       // Reset state

    // Main event loop
    while (1) {
        simpleserial_get();
    }
}