#include "../includes/md5.h"

t_digest *Get_digest(t_digest *d) {
  static t_digest *digest;
  if (d != NULL)
    digest = d;
  return digest;
}

t_digest *Init_digest(FlagType flag) {
  t_digest *d = malloc(sizeof(t_digest));
  if (d == NULL)
    return NULL;
  ft_bzero(d, sizeof(t_digest));
  if (flag & FLAG_S || flag & FLAG_IS_FILE)
    d->Write = &WriteFd;
  else
    d->Write = &Write;

  d->Reset = &Reset_digest;
  Get_digest(d);
  d->Reset();
  d->Get_K = &get_K;
  d->Get_R = &get_R;
  return d;
}

t_digest *Reset_digest() {
  t_digest *d = Get_digest(NULL);
  d->s[0] = INIT0;
  d->s[1] = INIT1;
  d->s[2] = INIT2;
  d->s[3] = INIT3;
  d->nx = 0;
  d->len = 0;
  return d;
}

void PrintSum() {
  t_digest *d = Get_digest(NULL);
  for (int i = 0; i < 16; i++) {
    printf("%02x", d->digest[i]);
  }
}

void digest(size_t new_length, uint8_t *padded_message) {
  t_digest *dig = Get_digest(NULL);
  for (size_t i = 0; i < new_length; i += BlockSize) {
    uint32_t w[DIGESTSIZE];
    for (int j = 0; j < DIGESTSIZE; j++) {
      w[j] = *(uint32_t *)(padded_message + i + j * 4);
    }

    uint32_t a = dig->s[0], b = dig->s[1], c = dig->s[2], d = dig->s[3];

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
      b = leftrotate((a + f + dig->Get_K()[i] + w[g]), dig->Get_R()[i]) + b;
      a = temp;
    }
    dig->s[0] += a;
    dig->s[1] += b;
    dig->s[2] += c;
    dig->s[3] += d;
  }
  free(padded_message);
  // Concaténation du résultat final
  dig->digest[0] = dig->s[0] & 0xFF;
  dig->digest[1] = (dig->s[0] >> 8) & 0xFF;
  dig->digest[2] = (dig->s[0] >> 16) & 0xFF;
  dig->digest[3] = (dig->s[0] >> 24) & 0xFF;
  dig->digest[4] = dig->s[1] & 0xFF;
  dig->digest[5] = (dig->s[1] >> 8) & 0xFF;
  dig->digest[6] = (dig->s[1] >> 16) & 0xFF;
  dig->digest[7] = (dig->s[1] >> 24) & 0xFF;
  dig->digest[8] = dig->s[2] & 0xFF;
  dig->digest[9] = (dig->s[2] >> 8) & 0xFF;
  dig->digest[10] = (dig->s[2] >> 16) & 0xFF;
  dig->digest[11] = (dig->s[2] >> 24) & 0xFF;
  dig->digest[12] = dig->s[3] & 0xFF;
  dig->digest[13] = (dig->s[3] >> 8) & 0xFF;
  dig->digest[14] = (dig->s[3] >> 16) & 0xFF;
  dig->digest[15] = (dig->s[3] >> 24) & 0xFF;
}
