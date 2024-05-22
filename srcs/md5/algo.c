#include "md5.h"

void md5_transform(const byte data[]) {
  t_digest *dig = Get_digest(NULL);
  uint32_t a, b, c, d, m[16], i, j;
  uint32_t *r = get_md5_R();
  uint32_t *k = get_md5_K();

  // convert the 64-byte data array into 16 32-bit words
  for (i = 0, j = 0; i < 16; ++i, j += 4)
    m[i] = (data[j]) + (data[j + 1] << 8) + (data[j + 2] << 16) +
           (data[j + 3] << 24);

  // save the hash values for this block
  a = dig->m[0];
  b = dig->m[1];
  c = dig->m[2];
  d = dig->m[3];

  i = 0;
  for (i = 0; i < 64; ++i) {
    uint32_t f, g;
    if (i < 16) {
      f = (b & c) | (~b & d);
      g = i;
    } else if (i < 32) {
      f = (d & b) | (~d & c);
      g = (5 * i + 1) % 16;
    } else if (i < 48) {
      f = b ^ c ^ d;
      g = (3 * i + 5) % 16;
    } else {
      f = c ^ (b | ~d);
      g = (7 * i) % 16;
    }
    uint32_t temp = d;
    d = c;
    c = b;
    b = b +
        ((a + f + k[i] + m[g]) << r[i] | (a + f + k[i] + m[g]) >> (32 - r[i]));
    a = temp;
  }

  // add this block's hash to the result so far
  dig->m[0] += a;
  dig->m[1] += b;
  dig->m[2] += c;
  dig->m[3] += d;
}

void Write_md5(byte *p) {
  t_digest *dig = Get_digest(NULL);
  size_t len = ft_strlen((char *)(p));
  size_t i;
  if (p == NULL)
    return;

  for (i = 0; i < len; ++i) {
    dig->digest_hash[dig->len] = p[i];
    dig->len++;
    if (dig->len == BLOCKSIZE) {
      md5_transform(dig->digest_hash);
      dig->lenbits += 512;
      dig->len = 0;
    }
  }
}

void md5_digest() {
  t_digest *dig = Get_digest(NULL);
  size_t i;

  ft_bzero(dig->hash, HASHSIZE);
  i = dig->len;

  if (dig->len < 56) {
    dig->digest_hash[i++] = 0x80;
    while (i < 56)
      dig->digest_hash[i++] = 0x00;
  } else if (dig->len >= 56) {
    dig->digest_hash[i++] = 0x80;
    while (i < 64)
      dig->digest_hash[i++] = 0x00;
    md5_transform(dig->digest_hash);
    ft_memset(dig->digest_hash, 0, 56);
  }

  dig->lenbits += dig->len * 8;
  for (i = 0; i < 8; ++i) {
    dig->digest_hash[56 + i] = dig->lenbits >> (i * 8);
  }
  md5_transform(dig->digest_hash);

  for (i = 0; i < 4; ++i) {
    dig->hash[i] = (dig->m[0] >> (i * 8)) & 0x000000ff;
    dig->hash[i + 4] = (dig->m[1] >> (i * 8)) & 0x000000ff;
    dig->hash[i + 8] = (dig->m[2] >> (i * 8)) & 0x000000ff;
    dig->hash[i + 12] = (dig->m[3] >> (i * 8)) & 0x000000ff;
  }
}

void PrintSumMd5() {
  t_digest *d = Get_digest(NULL);
  md5_digest();
  for (int i = 0; i < 16; i++) {
    ft_dprintf(1, "%02x", d->hash[i]);
  }
}
