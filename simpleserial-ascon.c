#include "hal.h"
#include "simpleserial.h"
#include <stdint.h>
#include <string.h>
#include "ascon.h"  // contains ascon_aead_encrypt()

// Buffers for key, nonce, and AD
static uint8_t key[16];
static uint8_t nonce[16];
static uint8_t ad[32];
static unsigned long long ad_len = 0;

/*
 * SS Command: set key
 */
uint8_t cmd_set_key(uint8_t *buf, uint8_t len) {
    memcpy(key, buf, 16);
    return 0x00;
}


/*
 * SS Command: set AD
 */

uint8_t cmd_set_ad(uint8_t *buf, uint8_t len) {
    memcpy(ad, buf, len);
    ad_len = len;
    return 0x00;
}

/*
 * SS Command: encrypt plaintext
 */
uint8_t cmd_encrypt_with_nonce(uint8_t *buf, uint8_t len) {
    memcpy(nonce, buf, 16); // first 16 bytes = nonce
    uint8_t *pt = buf + 16; // next 16 bytes = plaintext

    uint8_t ciphertext[32];
    unsigned long long clen = 0;

    trigger_high();
    ascon_aead_encrypt(ciphertext, &clen, pt, 16, ad, ad_len, NULL, nonce, key);
    trigger_low();

    simpleserial_put('r', (uint8_t)clen, ciphertext);
    return 0x00;
}

int main(void) {
    platform_init();
    init_uart();
    trigger_setup();

    // Add SimpleSerial commands
    simpleserial_init();
    simpleserial_addcmd('k', 16, cmd_set_key);    
    simpleserial_addcmd('a', 32, cmd_set_ad);              
    simpleserial_addcmd('e', 32, cmd_encrypt_with_nonce);         

    while (1)
        simpleserial_get();

    return 0;
}
