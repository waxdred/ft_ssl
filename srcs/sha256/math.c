#include <sha256.h>

// Function definitions for the macro replacements
uint32_t ROTRIGHT(uint32_t a, uint32_t b) {
  return ((a) >> (b)) | ((a) << (32 - (b)));
}
uint32_t CH(uint32_t x, uint32_t y, uint32_t z) {
  return ((x) & (y)) ^ (~(x) & (z));
}

uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z) {
  return ((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z));
}

uint32_t EP0(uint32_t x) {
  return ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22);
}

uint32_t EP1(uint32_t x) {
  return ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25);
}

uint32_t SIG0(uint32_t x) {
  return ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3);
}

uint32_t SIG1(uint32_t x) {
  return ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10);
}
