#ifndef ASCON_H
#define ASCON_H

#include <stdint.h>
#include <stddef.h>

// ASCON-128 Constants
#define ASCON_KEY_LEN     16 // 128 bits
#define ASCON_NONCE_LEN   16 // 128 bits
#define ASCON_STATE_WORDS 5  // 5x 64-bit words = 320 bits
#define ASCON_P_INIT      12 // Rounds for initialization permutation

typedef struct {
    uint64_t x[ASCON_STATE_WORDS];
} ascon_ctx_t;

void ascon_p(ascon_ctx_t* ctx, const int rounds);
void ascon_init(ascon_ctx_t* ctx, const uint8_t* key, const uint8_t* nonce);
void ascon_state_to_bytes(uint8_t* dst, const ascon_ctx_t* ctx);

#endif // ASCON_H