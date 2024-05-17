#include "../../includes/sha256.h"

// Perform a left rotation on a 32-bit integer 'value' by 'shift' bits.
uint32_t rotate_left(uint32_t value, uint32_t shift) {
  return (value << shift) | (value >> (32 - shift));
}

// Perform a right rotation on a 32-bit integer 'value' by 'shift' bits.
uint32_t rotate_right(uint32_t value, uint32_t shift) {
  return (value >> shift) | (value << (32 - shift));
}

// SHA-256 'choice' function: Select bits from 'y' or 'z' based on 'x'.
uint32_t sha256_choice(uint32_t x, uint32_t y, uint32_t z) {
  return (x & y) ^ (~x & z);
}

// SHA-256 'majority' function: Select majority bits among 'x', 'y', and 'z'.
uint32_t sha256_majority(uint32_t x, uint32_t y, uint32_t z) {
  return (x & y) ^ (x & z) ^ (y & z);
}

// SHA-256 'big sigma 0' function: Combination of right rotations by 2, 13, and
// 22 bits.
uint32_t sha256_big_sigma_0(uint32_t x) {
  return rotate_right(x, 2) ^ rotate_right(x, 13) ^ rotate_right(x, 22);
}

// SHA-256 'big sigma 1' function: Combination of right rotations by 6, 11, and
// 25 bits.
uint32_t sha256_big_sigma_1(uint32_t x) {
  return rotate_right(x, 6) ^ rotate_right(x, 11) ^ rotate_right(x, 25);
}

// SHA-256 'small sigma 0' function: Combination of right rotations by 7, 18,
// and a right shift by 3 bits.
uint32_t sha256_small_sigma_0(uint32_t x) {
  return rotate_right(x, 7) ^ rotate_right(x, 18) ^ (x >> 3);
}

// SHA-256 'small sigma 1' function: Combination of right rotations by 17, 19,
// and a right shift by 10 bits.
uint32_t sha256_small_sigma_1(uint32_t x) {
  return rotate_right(x, 17) ^ rotate_right(x, 19) ^ (x >> 10);
}
