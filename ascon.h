#ifndef ASCON_H
#define ASCON_H

#include <stdint.h>
#include <stddef.h>

// ASCON-128 Constants
#define ASCON_KEY_LEN     16 // 128 bits
#define ASCON_NONCE_LEN   16 // 128 bits
#define ASCON_STATE_WORDS 5  // 5x 64-bit words = 320 bits
#define ASCON_P_INIT      12 // Rounds for initialization permutation

// Structure to hold the 320-bit internal state (5x 64-bit words)
typedef struct {
    uint64_t x[ASCON_STATE_WORDS];
} ascon_ctx_t;

/**
 * @brief Performs the ASCON-p permutation on the state for a specified number of rounds.
 *
 * @param ctx The ASCON context containing the state.
 * @param rounds The number of rounds (e.g., 12 for initialization).
 */
void ascon_p(ascon_ctx_t* ctx, const int rounds);

/**
 * @brief Initializes the ASCON state for ASCON-128.
 *
 * This function sets the initial state with the IV, Key, and Nonce,
 * applies the 12-round permutation, and finalizes the initialization with the Key.
 *
 * @param ctx The ASCON context to be initialized.
 * @param key The 16-byte (128-bit) encryption key.
 * @param nonce The 16-byte (128-bit) nonce.
 */
void ascon_init(ascon_ctx_t* ctx, const uint8_t* key, const uint8_t* nonce);

/**
 * @brief Stores the 320-bit state into a byte array (for output/tracing).
 *
 * @param dst The destination byte array (must be 40 bytes long).
 * @param ctx The ASCON context containing the state.
 */
void ascon_state_to_bytes(uint8_t* dst, const ascon_ctx_t* ctx);

#endif // ASCON_H