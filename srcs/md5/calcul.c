#include "../../includes/md5.h"

// Perform a left rotation on a 32-bit integer 'value' by 'shift' bits.
uint32_t rotate_left(uint32_t value, uint32_t shift) {
  return (value << shift) | (value >> (32 - shift));
}

// MD5 auxiliary function F: Non-linear function combining three inputs.
uint32_t md5_function_f(uint32_t x, uint32_t y, uint32_t z) {
  return (x & y) | (~x & z);
}

// MD5 auxiliary function G: Non-linear function combining three inputs.
uint32_t md5_function_g(uint32_t x, uint32_t y, uint32_t z) {
  return (x & z) | (~z & y);
}

// MD5 auxiliary function H: Non-linear function combining three inputs using
// XOR.
uint32_t md5_function_h(uint32_t x, uint32_t y, uint32_t z) {
  return x ^ y ^ z;
}

// MD5 auxiliary function I: Non-linear function combining three inputs using
// XOR and NOT.
uint32_t md5_function_i(uint32_t x, uint32_t y, uint32_t z) {
  return y ^ (x | ~z);
}

// Perform one round of the MD5 transformation using function F.
uint32_t md5_round_ff(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                      uint32_t x, uint32_t shift, uint32_t constant) {
  a += md5_function_f(b, c, d) + x + constant;
  a = rotate_left(a, shift);
  return a + b;
}

// Perform one round of the MD5 transformation using function G.
uint32_t md5_round_gg(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                      uint32_t x, uint32_t shift, uint32_t constant) {
  a += md5_function_g(b, c, d) + x + constant;
  a = rotate_left(a, shift);
  return a + b;
}

// Perform one round of the MD5 transformation using function H.
uint32_t md5_round_hh(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                      uint32_t x, uint32_t shift, uint32_t constant) {
  a += md5_function_h(b, c, d) + x + constant;
  a = rotate_left(a, shift);
  return a + b;
}

// Perform one round of the MD5 transformation using function I.
uint32_t md5_round_ii(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                      uint32_t x, uint32_t shift, uint32_t constant) {
  a += md5_function_i(b, c, d) + x + constant;
  a = rotate_left(a, shift);
  return a + b;
}
