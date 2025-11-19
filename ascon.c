#include "ascon.h"
#include <string.h>

// --- Helper Macros ---

// Rotate right by 'k' bits for a 64-bit word
#define ROR(x, k) (((x) >> (k)) | ((x) << (64 - (k))))

// Load a 64-bit word from a big-endian byte array
static uint64_t LOAD_BIG_ENDIAN(const uint8_t* x) {
    uint64_t r = 0;
    for (int i = 0; i < 8; ++i) {
        r |= (uint64_t)x[i] << (56 - 8 * i);
    }
    return r;
}

// Store a 64-bit word to a big-endian byte array
static void STORE_BIG_ENDIAN(uint8_t* x, uint64_t w) {
    for (int i = 0; i < 8; ++i) {
        x[i] = (uint8_t)(w >> (56 - 8 * i));
    }
}

// --- ASCON Core Permutation Implementation ---

static inline void ascon_round(ascon_ctx_t* ctx, uint64_t C) {
    uint64_t x0 = ctx->x[0], x1 = ctx->x[1], x2 = ctx->x[2], x3 = ctx->x[3], x4 = ctx->x[4];

    // 1. Add Round Constant
    x2 ^= C;

    // 2. S-box Layer
    x0 ^= x4; x4 ^= x3; x2 ^= x1;
    x0 = ~x0; x1 = ~x1; x2 = ~x2; x3 = ~x3; x4 = ~x4;
    x0 ^= x4; x4 ^= x3; x2 ^= x1;
    x0 = ~x0; x1 = ~x1; x2 = ~x2; x3 = ~x3; x4 = ~x4;

    // 3. Linear Layer (XOR-shifts)
    x0 ^= ROR(x0, 19) ^ ROR(x0, 28);
    x1 ^= ROR(x1, 61) ^ ROR(x1, 39);
    x2 ^= ROR(x2, 1)  ^ ROR(x2, 6);  // Syntax error fixed here
    x3 ^= ROR(x3, 10) ^ ROR(x3, 17);
    x4 ^= ROR(x4, 7)  ^ ROR(x4, 41);

    ctx->x[0] = x0; ctx->x[1] = x1; ctx->x[2] = x2; ctx->x[3] = x3; ctx->x[4] = x4;
}

// Round constants for the full 12 rounds
const uint64_t ASCON_RC[] = {
    0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87, 0x78, 0x69, 0x5a, 0x4b
};

void ascon_p(ascon_ctx_t* ctx, const int rounds) {
    for (int i = 12 - rounds; i < 12; i++) {
        ascon_round(ctx, ASCON_RC[i]);
    }
}

// --- Initialization Phase Implementation ---

void ascon_init(ascon_ctx_t* ctx, const uint8_t* key, const uint8_t* nonce) {
    // ASCON-128 IV
    const uint64_t IV = 0x80400c0600000000;

    // 1. Initialize State with IV, Key, and Nonce
    ctx->x[0] = IV;
    ctx->x[1] = LOAD_BIG_ENDIAN(&key[0]);
    ctx->x[2] = LOAD_BIG_ENDIAN(&key[8]);
    ctx->x[3] = LOAD_BIG_ENDIAN(&nonce[0]);
    ctx->x[4] = LOAD_BIG_ENDIAN(&nonce[8]);

    // 2. Apply Permutation (Ascon-p[12])
    ascon_p(ctx, ASCON_P_INIT);

    // 3. Finalize Initialization
    ctx->x[3] ^= LOAD_BIG_ENDIAN(&key[0]);
    ctx->x[4] ^= LOAD_BIG_ENDIAN(&key[8]);
}

void ascon_state_to_bytes(uint8_t* dst, const ascon_ctx_t* ctx) {
    STORE_BIG_ENDIAN(&dst[0],  ctx->x[0]);
    STORE_BIG_ENDIAN(&dst[8],  ctx->x[1]);
    STORE_BIG_ENDIAN(&dst[16], ctx->x[2]);
    STORE_BIG_ENDIAN(&dst[24], ctx->x[3]);
    STORE_BIG_ENDIAN(&dst[32], ctx->x[4]);
}