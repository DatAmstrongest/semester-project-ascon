#include "hal.h"
#include "simpleserial.h"
#include <stdint.h>
#include <string.h>
#include "ascon.h"  // contains ascon_aead_encrypt()

// Buffers for key and nonce
static uint8_t key[ASCON_KEYBYTES];
static uint8_t nonce[ASCON_NPUBBYTES];

/*
 * SS Command: set key
 */
uint8_t cmd_set_key(uint8_t *buf, uint8_t len) {
    if (len != ASCON_KEYBYTES) return 1;
    memcpy(key, buf, ASCON_KEYBYTES);
    return 0x00;
}

/*
 * SS Command: set nonce
 */
uint8_t cmd_set_nonce(uint8_t *buf, uint8_t len) {
    if (len != ASCON_NPUBBYTES) return 1;
    memcpy(nonce, buf, ASCON_NPUBBYTES);
    return 0x00;
}

/*
 * SS Command: encrypt plaintext
 */
uint8_t cmd_encrypt(uint8_t *pt, uint8_t len) {

    uint8_t ciphertext[32];       // plaintext + tag
    unsigned long long clen = 0;

    const unsigned char ad[1] = {0};  // empty AD
    unsigned long long adlen = 0;

    trigger_high();  // start of encryption for SCA
    ascon_aead_encrypt(ciphertext, &clen, pt, len, ad, adlen, NULL, nonce, key);
    trigger_low();   // end of encryption

    // Send ciphertext + tag over SimpleSerial
    simpleserial_put('r', (uint8_t)clen, ciphertext);

    return 0x00;
}

int main(void) {
    platform_init();
    init_uart();
    trigger_setup();

    // Add SimpleSerial commands
    simpleserial_init();
    simpleserial_addcmd('k', ASCON_KEYBYTES, cmd_set_key);    // set key
    simpleserial_addcmd('n', ASCON_NPUBBYTES, cmd_set_nonce); // set nonce
    simpleserial_addcmd('p', 16, cmd_encrypt);                // encrypt plaintext

    while (1)
        simpleserial_get();

    return 0;
}
