#include <sha256.h>

void sha256_transform(const byte data[]) {
  t_digest *dig = Get_digest(NULL);
  uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];
  uint32_t *k = get_sha256_K();

  for (i = 0, j = 0; i < 16; ++i, j += 4)
    m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) |
           (data[j + 3]);
  for (; i < 64; ++i)
    m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

  a = dig->m[0];
  b = dig->m[1];
  c = dig->m[2];
  d = dig->m[3];
  e = dig->m[4];
  f = dig->m[5];
  g = dig->m[6];
  h = dig->m[7];

  for (i = 0; i < BLOCKSIZE; ++i) {
    t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
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

  dig->m[0] += a;
  dig->m[1] += b;
  dig->m[2] += c;
  dig->m[3] += d;
  dig->m[4] += e;
  dig->m[5] += f;
  dig->m[6] += g;
  dig->m[7] += h;
}

void Write_sha256(byte *p) {
  t_digest *dig = Get_digest(NULL);
  uint32_t i;
  size_t len = ft_strlen((char *)(p));

  for (i = 0; i < len; ++i) {
    dig->digest_hash[dig->len] = p[i];
    dig->len++;
    if (dig->len == 64) {
      sha256_transform(dig->digest_hash);
      dig->lenbits += 512;
      dig->len = 0;
    }
  }
}

void sha256_digest() {
  t_digest *dig = Get_digest(NULL);
  uint32_t i;

  ft_bzero(dig->hash, HASHSIZE);
  i = dig->len;

  if (dig->len < 56) {
    dig->digest_hash[i++] = 0x80;
    while (i < 56)
      dig->digest_hash[i++] = 0x00;
  } else {
    dig->digest_hash[i++] = 0x80;
    while (i < 64)
      dig->digest_hash[i++] = 0x00;
    sha256_transform(dig->digest_hash);
    ft_memset(dig->digest_hash, 0, 56);
  }

  dig->lenbits += dig->len * 8;
  for (i = 0; i < 8; ++i) {
    dig->digest_hash[63 + i] = dig->lenbits >> (i * 8);
  }
  sha256_transform(dig->digest_hash);

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

void PrintSumSha256() {
  t_digest *d = Get_digest(NULL);
  sha256_digest();
  for (int i = 0; i < 32; i++) {
    ft_dprintf(1, "%02x", d->hash[i]);
  }
}
