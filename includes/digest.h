#ifndef DIGEST_H
#define DIGEST_H
#include "./flag.h"
#include "./ft_printf.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define byte uint8_t

// The blocksize of MD5 in bytes.
#define DIGESTSIZE 16
#define DIGESTSIZESHA 64
#define BLOCKSIZE 64
#define HASHSIZE 32
#define BUF_SIZE 512

typedef unsigned int uint32_t;

typedef struct s_digest {
  uint32_t m[BLOCKSIZE];
  byte digest_hash[BLOCKSIZE];
  int nx;
  uint init_size;
  unsigned long long lenbits;
  uint64_t len;
  byte hash[HASHSIZE];

  // INTERFACE
  struct s_digest *(*Reset)();
  uint32_t *(*Get_K)();
  uint32_t *(*Get_R)();
  uint32_t *(*Get_S)();
  void (*Print)();
  void (*SetGet_RK)(uint32_t *(*Get_R)(), uint32_t *(*Get_K)());
  void (*Write)(byte *f);
  void (*digest)(size_t new_length, uint8_t *padded_message);
} t_digest;

void PrintSha256();
static char hex[2][6];
void Write_sha256(byte *data);
t_digest *Get_digest(t_digest *d);
t_digest *Reset_digest_sha256();
t_digest *Reset_digest_md5();
void Print_Digest(int reverse, TypeInput t, const char *str, void());
t_digest *Init_digest(FlagCmd cmd);
void Print_Digest(int reverse, TypeInput t, const char *str, void (*Print)());
void PrintSumMd5();

#endif
