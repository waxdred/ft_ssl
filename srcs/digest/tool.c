#include "../../includes/digest.h"

uint32_t md5_leftrotate(uint32_t x, uint32_t c) {
  return (x << c) | (x >> (32 - c));
}
