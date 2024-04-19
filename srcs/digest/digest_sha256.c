#include "../../includes/digest.h"

void sha256_transform(const uint8_t data[]) {
  t_digest *dig = Get_digest(NULL);
  uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

  for (i = 0, j = 0; i < 16; ++i, j += 4)
    m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) |
           (data[j + 3]);
  for (; i < 64; ++i)
    m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

  a = dig->s[0];
  b = dig->s[1];
  c = dig->s[2];
  d = dig->s[3];
  e = dig->s[4];
  f = dig->s[5];
  g = dig->s[6];
  h = dig->s[7];

  for (i = 0; i < 64; ++i) {
    t1 = h + EP1(e) + CH(e, f, g) + dig->Get_K()[i] + m[i];
    t2 = EP0(a) + MAJ(a, b, c);
    h = g;
    g = f;
    f = e;
    e = d + t1;
    d = c;
    c = b;
    b = a;
    a = t1 + t2;
  }

  dig->s[0] += a;
  dig->s[1] += b;
  dig->s[2] += c;
  dig->s[3] += d;
  dig->s[4] += e;
  dig->s[5] += f;
  dig->s[6] += g;
  dig->s[7] += h;
}

void sha256_update(char *data) {
  t_digest *dig = Get_digest(NULL);
  uint32_t i;
  size_t len = ft_strlen(data);

  for (i = 0; i < len; ++i) {
    dig->sha256_digest[dig->len] = data[i];
    dig->len++;
    if (dig->len == 64) {
      sha256_transform(dig->sha256_digest);
      dig->lenbits += 512;
      dig->len = 0;
    }
  }
}

void sha256_final() {
  t_digest *dig = Get_digest(NULL);
  uint32_t i;

  ft_bzero(dig->hash, 32);

  i = dig->len;

  // Pad whatever data is left in the buffer.
  if (dig->len < 56) {
    dig->sha256_digest[i++] = 0x80;
    while (i < 56)
      dig->sha256_digest[i++] = 0x00;
  } else {
    dig->sha256_digest[i++] = 0x80;
    while (i < 64)
      dig->sha256_digest[i++] = 0x00;
    sha256_transform(dig->sha256_digest);
    memset(dig->sha256_digest, 0, 56);
  }

  // Append to the padding the total message's length in bits and transform.
  dig->lenbits += dig->len * 8;
  dig->sha256_digest[63] = dig->lenbits;
  dig->sha256_digest[62] = dig->lenbits >> 8;
  dig->sha256_digest[61] = dig->lenbits >> 16;
  dig->sha256_digest[60] = dig->lenbits >> 24;
  dig->sha256_digest[59] = dig->lenbits >> 32;
  dig->sha256_digest[58] = dig->lenbits >> 40;
  dig->sha256_digest[57] = dig->lenbits >> 48;
  dig->sha256_digest[56] = dig->lenbits >> 56;
  sha256_transform(dig->sha256_digest);

  // Since this implementation uses little endian byte ordering and SHA uses big
  // endian, reverse all the bytes when copying the final state to the output
  // hash.
  for (i = 0; i < 4; ++i) {
    dig->hash[i] = (dig->s[0] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 4] = (dig->s[1] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 8] = (dig->s[2] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 12] = (dig->s[3] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 16] = (dig->s[4] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 20] = (dig->s[5] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 24] = (dig->s[6] >> (24 - i * 8)) & 0x000000ff;
    dig->hash[i + 28] = (dig->s[7] >> (24 - i * 8)) & 0x000000ff;
  }
}

void PrintSha256() {
  t_digest *dig = Get_digest(NULL);
  sha256_final();
  for (int i = 0; i < 32; i++)
    printf("%02x", dig->hash[i]);
  printf("\n");
}
