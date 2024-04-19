#include "../../includes/md5.h"

uint32_t leftrotate(uint32_t x, uint32_t c) {
  return (x << c) | (x >> (32 - c));
}
