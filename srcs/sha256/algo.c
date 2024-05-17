#include "../../includes/sha256.h"

void sha256_transform(const byte data[]) {
  t_digest *dig = Get_digest(NULL);
  uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

  // convert the 64-byte data array into 16 32-bit words big-endian
  for (i = 0, j = 0; i < 16; ++i, j += 4)
    m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) |
           (data[j + 3]);
  // prepare the message schedule
  for (; i < 64; ++i)
    m[i] = sha256_small_sigma_1(m[i - 2]) + m[i - 7] +
           sha256_small_sigma_0(m[i - 15]) + m[i - 16];

  // save the hash values for this block
  a = dig->m[0];
  b = dig->m[1];
  c = dig->m[2];
  d = dig->m[3];
  e = dig->m[4];
  f = dig->m[5];
  g = dig->m[6];
  h = dig->m[7];

  // round using the sha256_round functions and table
  for (i = 0; i < BLOCKSIZE; ++i) {
    t1 = h + sha256_big_sigma_1(e) + sha256_choice(e, f, g) + dig->Get_K()[i] +
         m[i];
    t2 = sha256_big_sigma_0(a) + sha256_majority(a, b, c);

    h = g;
    g = f;
    f = e;
    e = d + t1;
    d = c;
    c = b;
    b = a;
    a = t1 + t2;
  }

  dig->m[0] += a;
  dig->m[1] += b;
  dig->m[2] += c;
  dig->m[3] += d;
  dig->m[4] += e;
  dig->m[5] += f;
  dig->m[6] += g;
  dig->m[7] += h;
}

void Write_sha256(byte *data) {
  t_digest *dig = Get_digest(NULL);
  uint32_t i;
  size_t len = ft_strlen((char *)(data));

  for (i = 0; i < len; ++i) {
    dig->digest_hash[dig->len] = data[i];
    dig->len++;
    if (dig->len == BLOCKSIZE) {
      sha256_transform(dig->digest_hash);
      dig->lenbits += 512;
      dig->len = 0;
    }
  }
}

void sha256_final() {
  t_digest *dig = Get_digest(NULL);
  uint32_t i;

  ft_bzero(dig->hash, HASHSIZE);
  i = dig->len;

  // pad the message with a single bit '1' and zeros '0' until the end of the
  if (dig->len < 56) {
    dig->digest_hash[i++] = 0x80;
    while (i < 56)
      dig->digest_hash[i++] = 0x00;
  } else {
    dig->digest_hash[i++] = 0x80;
    // pad the rest of the block with zeros
    while (i < BLOCKSIZE)
      dig->digest_hash[i++] = 0x00;
    // transform the current block and pad the rest of the block with zeros
    sha256_transform(dig->digest_hash);
    ft_memset(dig->digest_hash, 0, 56);
  }

  // append the total message length in bits as a 64-bit big-endian integer
  for (i = 0; i < 8; ++i) {
    dig->digest_hash[56 + i] = dig->lenbits >> (i * 8);
  }
  sha256_transform(dig->digest_hash);

  // store the hash in the digest structure
  for (i = 0; i < 4; ++i) {
    dig->hash[i] = (dig->m[0] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 4] = (dig->m[1] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 8] = (dig->m[2] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 12] = (dig->m[3] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 16] = (dig->m[4] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 20] = (dig->m[5] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 24] = (dig->m[6] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 28] = (dig->m[7] >> (24 - i * 8)) & 0x000000ff;
  }
}

void PrintSha256() {
  t_digest *dig = Get_digest(NULL);
  sha256_final();
  for (int i = 0; i < 32; i++)
    ft_printf("%02x", dig->hash[i]);
}
