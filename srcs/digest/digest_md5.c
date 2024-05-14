#include "../../includes/digest.h"

void md5_transform(const BYTE data[]) {
  t_digest *dig = Get_digest(NULL);
  uint32_t a, b, c, d, m[16], i, j;

  for (i = 0, j = 0; i < 16; ++i, j += 4)
    m[i] = (data[j]) + (data[j + 1] << 8) + (data[j + 2] << 16) +
           (data[j + 3] << 24);

  a = dig->m[0];
  b = dig->m[1];
  c = dig->m[2];
  d = dig->m[3];

  FF(a, b, c, d, m[0], 7, 0xd76aa478);
  FF(d, a, b, c, m[1], 12, 0xe8c7b756);
  FF(c, d, a, b, m[2], 17, 0x242070db);
  FF(b, c, d, a, m[3], 22, 0xc1bdceee);
  FF(a, b, c, d, m[4], 7, 0xf57c0faf);
  FF(d, a, b, c, m[5], 12, 0x4787c62a);
  FF(c, d, a, b, m[6], 17, 0xa8304613);
  FF(b, c, d, a, m[7], 22, 0xfd469501);
  FF(a, b, c, d, m[8], 7, 0x698098d8);
  FF(d, a, b, c, m[9], 12, 0x8b44f7af);
  FF(c, d, a, b, m[10], 17, 0xffff5bb1);
  FF(b, c, d, a, m[11], 22, 0x895cd7be);
  FF(a, b, c, d, m[12], 7, 0x6b901122);
  FF(d, a, b, c, m[13], 12, 0xfd987193);
  FF(c, d, a, b, m[14], 17, 0xa679438e);
  FF(b, c, d, a, m[15], 22, 0x49b40821);

  GG(a, b, c, d, m[1], 5, 0xf61e2562);
  GG(d, a, b, c, m[6], 9, 0xc040b340);
  GG(c, d, a, b, m[11], 14, 0x265e5a51);
  GG(b, c, d, a, m[0], 20, 0xe9b6c7aa);
  GG(a, b, c, d, m[5], 5, 0xd62f105d);
  GG(d, a, b, c, m[10], 9, 0x02441453);
  GG(c, d, a, b, m[15], 14, 0xd8a1e681);
  GG(b, c, d, a, m[4], 20, 0xe7d3fbc8);
  GG(a, b, c, d, m[9], 5, 0x21e1cde6);
  GG(d, a, b, c, m[14], 9, 0xc33707d6);
  GG(c, d, a, b, m[3], 14, 0xf4d50d87);
  GG(b, c, d, a, m[8], 20, 0x455a14ed);
  GG(a, b, c, d, m[13], 5, 0xa9e3e905);
  GG(d, a, b, c, m[2], 9, 0xfcefa3f8);
  GG(c, d, a, b, m[7], 14, 0x676f02d9);
  GG(b, c, d, a, m[12], 20, 0x8d2a4c8a);

  HH(a, b, c, d, m[5], 4, 0xfffa3942);
  HH(d, a, b, c, m[8], 11, 0x8771f681);
  HH(c, d, a, b, m[11], 16, 0x6d9d6122);
  HH(b, c, d, a, m[14], 23, 0xfde5380c);
  HH(a, b, c, d, m[1], 4, 0xa4beea44);
  HH(d, a, b, c, m[4], 11, 0x4bdecfa9);
  HH(c, d, a, b, m[7], 16, 0xf6bb4b60);
  HH(b, c, d, a, m[10], 23, 0xbebfbc70);
  HH(a, b, c, d, m[13], 4, 0x289b7ec6);
  HH(d, a, b, c, m[0], 11, 0xeaa127fa);
  HH(c, d, a, b, m[3], 16, 0xd4ef3085);
  HH(b, c, d, a, m[6], 23, 0x04881d05);
  HH(a, b, c, d, m[9], 4, 0xd9d4d039);
  HH(d, a, b, c, m[12], 11, 0xe6db99e5);
  HH(c, d, a, b, m[15], 16, 0x1fa27cf8);
  HH(b, c, d, a, m[2], 23, 0xc4ac5665);

  II(a, b, c, d, m[0], 6, 0xf4292244);
  II(d, a, b, c, m[7], 10, 0x432aff97);
  II(c, d, a, b, m[14], 15, 0xab9423a7);
  II(b, c, d, a, m[5], 21, 0xfc93a039);
  II(a, b, c, d, m[12], 6, 0x655b59c3);
  II(d, a, b, c, m[3], 10, 0x8f0ccc92);
  II(c, d, a, b, m[10], 15, 0xffeff47d);
  II(b, c, d, a, m[1], 21, 0x85845dd1);
  II(a, b, c, d, m[8], 6, 0x6fa87e4f);
  II(d, a, b, c, m[15], 10, 0xfe2ce6e0);
  II(c, d, a, b, m[6], 15, 0xa3014314);
  II(b, c, d, a, m[13], 21, 0x4e0811a1);
  II(a, b, c, d, m[4], 6, 0xf7537e82);
  II(d, a, b, c, m[11], 10, 0xbd3af235);
  II(c, d, a, b, m[2], 15, 0x2ad7d2bb);
  II(b, c, d, a, m[9], 21, 0xeb86d391);

  dig->m[0] += a;
  dig->m[1] += b;
  dig->m[2] += c;
  dig->m[3] += d;
}

void Write_md5(BYTE *p) {
  if (p == NULL)
    return;
  t_digest *dig = Get_digest(NULL);
  if (p == NULL)
    return;
  dig->len = ft_strlen((char *)(p));

  size_t i;

  for (i = 0; i < dig->len; ++i) {
    dig->md5_digest[dig->len] = p[i];
    dig->len++;
    if (dig->len == 64) {
      md5_transform(dig->md5_digest);
      dig->lenbits += 512;
      dig->len = 0;
    }
  }
}

void md5_digest() {
  t_digest *dig = Get_digest(NULL);
  size_t i;

  i = dig->len;

  if (dig->len < 56) {
    dig->md5_digest[i++] = 0x80;
    while (i < 56)
      dig->md5_digest[i++] = 0x00;
  } else if (dig->len >= 56) {
    dig->md5_digest[i++] = 0x80;
    while (i < 64)
      dig->md5_digest[i++] = 0x00;
    md5_transform(dig->md5_digest);
    memset(dig->md5_digest, 0, 56);
  }

  dig->lenbits += dig->len * 8;
  dig->md5_digest[56] = dig->lenbits;
  dig->md5_digest[57] = dig->lenbits >> 8;
  dig->md5_digest[58] = dig->lenbits >> 16;
  dig->md5_digest[59] = dig->lenbits >> 24;
  dig->md5_digest[60] = dig->lenbits >> 32;
  dig->md5_digest[61] = dig->lenbits >> 40;
  dig->md5_digest[62] = dig->lenbits >> 48;
  dig->md5_digest[63] = dig->lenbits >> 56;
  md5_transform(dig->md5_digest);

  for (i = 0; i < 4; ++i) {
    dig->hash[i] = (dig->m[0] >> (i * 8)) & 0x000000ff;
    dig->hash[i + 4] = (dig->m[1] >> (i * 8)) & 0x000000ff;
    dig->hash[i + 8] = (dig->m[2] >> (i * 8)) & 0x000000ff;
    dig->hash[i + 12] = (dig->m[3] >> (i * 8)) & 0x000000ff;
  }
}
