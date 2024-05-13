#ifndef DIGEST_H
#define DIGEST_H
#include "./flag.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MD5_INIT0 0x67452301
#define MD5_INIT1 0xEFCDAB89
#define MD5_INIT2 0x98BADCFE
#define MD5_INIT3 0x10325476

#define SHA256_INIT0 0x6a09e667;
#define SHA256_INIT1 0xbb67ae85;
#define SHA256_INIT2 0x3c6ef372;
#define SHA256_INIT3 0xa54ff53a;
#define SHA256_INIT4 0x510e527f;
#define SHA256_INIT5 0x9b05688c;
#define SHA256_INIT6 0x1f83d9ab;
#define SHA256_INIT7 0x5be0cd19;

// The blocksize of MD5 in bytes.
#define DIGESTSIZE 16
#define DIGESTSIZESHA 64
#define BlockSize 64
#define BUF_SIZE 512

// MACROS sha256
#define ROTLEFT(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define ROTRIGHT(a, b) (((a) >> (b)) | ((a) << (32 - (b))))

#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

typedef unsigned int uint32_t;
typedef unsigned char byte;

typedef struct s_digest {
  uint32_t m[4];
  uint32_t s[8];
  uint8_t md5_digest[DIGESTSIZE];
  uint8_t sha256_digest[BlockSize];
  int nx;
  unsigned long long lenbits;
  uint64_t len;
  uint8_t hash[32];

  // INTERFACE
  struct s_digest *(*Reset)();
  uint32_t *(*Get_K)();
  uint32_t *(*Get_R)();
  void (*Print)();
  void (*SetGet_RK)(uint32_t *(*Get_R)(), uint32_t *(*Get_K)());
  void (*Write)(char *f);
  void (*digest)(size_t new_length, uint8_t *padded_message);
} t_digest;

void PrintSha256();
void sha256_update(char *data);
t_digest *Get_digest(t_digest *d);
uint32_t md5_leftrotate(uint32_t x, uint32_t c);
t_digest *Reset_digest_sha256();
t_digest *Reset_digest_md5();
void md5_digest(size_t new_length, uint8_t *padded_message);
void Print_Digest(int reverse, TypeInput t, const char *str, void());
t_digest *Init_digest(FlagCmd cmd);
void Write_md5(char *p);
void Print_Digest(int reverse, TypeInput t, const char *str, void (*Print)());

#endif
