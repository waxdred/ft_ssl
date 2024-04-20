#include "../../includes/digest.h"

void Write_md5(char *p) {
  if (p == NULL)
    return;
  t_digest *dig = Get_digest(NULL);
  if (p == NULL)
    return;
  dig->len = ft_strlen(p);
  size_t new_length = (dig->len + 8) / BlockSize * BlockSize + BlockSize;
  uint8_t *padded_message = (uint8_t *)malloc(new_length * sizeof(uint8_t));
  ft_bzero(padded_message, new_length * sizeof(uint8_t));
  ft_memcpy(padded_message, p, dig->len);
  padded_message[dig->len] = 0x80;
  padded_message[new_length - 8] = dig->len * 8;
  dig->digest(new_length, padded_message);
}

void md5_digest(size_t new_length, uint8_t *padded_message) {
  t_digest *dig = Get_digest(NULL);
  for (size_t i = 0; i < new_length; i += BlockSize) {
    uint32_t w[DIGESTSIZE];
    for (int j = 0; j < DIGESTSIZE; j++) {
      w[j] = *(uint32_t *)(padded_message + i + j * 4);
    }
    uint32_t a = dig->m[0], b = dig->m[1], c = dig->m[2], d = dig->m[3];
    for (int i = 0; i < BlockSize; i++) {
      uint32_t f, g;
      if (i <= 15) {
        f = (b & c) | ((~b) & d);
        g = i;
      } else if (i <= 31) {
        f = (d & b) | ((~d) & c);
        g = (5 * i + 1) % 16;
      } else if (i <= 47) {
        f = b ^ c ^ d;
        g = (3 * i + 5) % 16;
      } else {
        f = c ^ (b | (~d));
        g = (7 * i) % 16;
      }
      uint32_t temp = d;
      d = c;
      c = b;
      b = md5_leftrotate((a + f + dig->Get_K()[i] + w[g]), dig->Get_R()[i]) + b;
      a = temp;
    }
    dig->m[0] += a;
    dig->m[1] += b;
    dig->m[2] += c;
    dig->m[3] += d;
  }
  free(padded_message);
  // Concaténation du résultat final
  dig->md5_digest[0] = dig->m[0] & 0xFF;
  dig->md5_digest[1] = (dig->m[0] >> 8) & 0xFF;
  dig->md5_digest[2] = (dig->m[0] >> 16) & 0xFF;
  dig->md5_digest[3] = (dig->m[0] >> 24) & 0xFF;
  dig->md5_digest[4] = dig->m[1] & 0xFF;
  dig->md5_digest[5] = (dig->m[1] >> 8) & 0xFF;
  dig->md5_digest[6] = (dig->m[1] >> 16) & 0xFF;
  dig->md5_digest[7] = (dig->m[1] >> 24) & 0xFF;
  dig->md5_digest[8] = dig->m[2] & 0xFF;
  dig->md5_digest[9] = (dig->m[2] >> 8) & 0xFF;
  dig->md5_digest[10] = (dig->m[2] >> 16) & 0xFF;
  dig->md5_digest[11] = (dig->m[2] >> 24) & 0xFF;
  dig->md5_digest[12] = dig->m[3] & 0xFF;
  dig->md5_digest[13] = (dig->m[3] >> 8) & 0xFF;
  dig->md5_digest[14] = (dig->m[3] >> 16) & 0xFF;
  dig->md5_digest[15] = (dig->m[3] >> 24) & 0xFF;
}
