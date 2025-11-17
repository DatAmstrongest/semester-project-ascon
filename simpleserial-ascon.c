#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ascon.h"
#include "simpleserial.h"
#include "hal.h"

// The explicit 'extern' declarations are removed as they did not resolve the error.


// --- Global Context and Buffers ---

// Global ASCON context (320 bits)
ascon_ctx_t ascon_ctx;

// Buffers for key and nonce (128 bits each)
uint8_t key[ASCON_KEY_LEN];
uint8_t nonce[ASCON_NONCE_LEN];

// Utility buffer for returning the 40-byte state (Kept for optional use, but currently unused)
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
 * @brief SimpleSerial command to set the 16-byte nonce ('n').
 * Format: n<16-byte-hex-nonce>
 */
uint8_t set_nonce(uint8_t* data, uint8_t len) {
    if (len != ASCON_NONCE_LEN) return 0x01; // Error: Incorrect length

    memcpy(nonce, data, ASCON_NONCE_LEN);
    return 0x00; // Success
}

/**
 * @brief SimpleSerial command to perform the ASCON initialization ('i').
 *
 * This function calls ascon_init() and includes trigger calls for tracing.
 * Format: i
 * Returns: 0x00 (Success)
 */
uint8_t do_init(uint8_t* data, uint8_t len) {
    // 1. Set the trigger high
    trigger_high();

    // 2. Perform the ASCON initialization phase
    // This is the function we want to target for side-channel analysis.
    ascon_init(&ascon_ctx, key, nonce);

    // 3. Set the trigger low
    trigger_low();

    // The result (40-byte state) is calculated and stored here,
    // but is NOT sent back, as requested (no simpleserial_write).
    ascon_state_to_bytes(state_output, &ascon_ctx);

    return 0x00; // Success
}


/**
 * @brief Command to reset the key, nonce, and context ('z').
 * This is useful for clearing state between traces.
 */
uint8_t reset_ascon(uint8_t* data, uint8_t len) {
    (void)data; // unused
    (void)len;  // unused

    memset(&ascon_ctx, 0, sizeof(ascon_ctx_t));
    memset(key, 0, ASCON_KEY_LEN);
    memset(nonce, 0, ASCON_NONCE_LEN);

    return 0x00; // Success
}

// --- Main Program Loop ---

int main(void) {
    // Initialize hardware and SimpleSerial
    platform_init();
    init_uart();
    
    // Initializing SimpleSerial for command processing
    simpleserial_init();
    
    trigger_setup();

    // Define the SimpleSerial commands
    simpleserial_addcmd('k', ASCON_KEY_LEN, set_key);   // Set Key
    simpleserial_addcmd('n', ASCON_NONCE_LEN, set_nonce); // Set Nonce
    simpleserial_addcmd('i', 0, do_init);             // Perform Initialization
    simpleserial_addcmd('z', 0, reset_ascon);         // Reset state

    // Main event loop
    while (1) {
        simpleserial_get();
    }
}