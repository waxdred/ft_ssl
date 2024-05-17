#ifndef SHA256_H
#define SHA256_H
#include "./digest.h"
#include "./flag.h"
#include "./ft_printf.h"
#include "./utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCKSIZE 64
#define HASHSIZE 32
// The blocksize of SHA256 in bytes.
#define SHA256_INIT0 0x6a09e667
#define SHA256_INIT1 0xbb67ae85
#define SHA256_INIT2 0x3c6ef372
#define SHA256_INIT3 0xa54ff53a
#define SHA256_INIT4 0x510e527f
#define SHA256_INIT5 0x9b05688c
#define SHA256_INIT6 0x1f83d9ab
#define SHA256_INIT7 0x5be0cd19

typedef struct s_sha256 {
  t_digest *digest;
  t_flag flag;
  void (*Free)();
  void (*PrintSum)();
  int Stop;
  uint32_t (*LeftRotate)(uint32_t x, uint32_t c);
  uint32_t(*get_K);
  uint32_t(*get_R);
  uint32_t(*get_S);
} t_sha256;

t_sha256 *ft_NewSha256(t_flag flag);
t_sha256 *Get_sha256(t_sha256 *sha256);
uint32_t *get_sha256_S();
uint32_t *get_sha256_K();
int Runsha256();
void Print_Sha256(int reverse, TypeInput t, const char *str, void (*Print)());

uint32_t rotate_left(uint32_t value, uint32_t shift);
uint32_t rotate_right(uint32_t value, uint32_t shift);
uint32_t sha256_choice(uint32_t x, uint32_t y, uint32_t z);
uint32_t sha256_majority(uint32_t x, uint32_t y, uint32_t z);
uint32_t sha256_big_sigma_0(uint32_t x);
uint32_t sha256_big_sigma_1(uint32_t x);
uint32_t sha256_small_sigma_0(uint32_t x);
uint32_t sha256_small_sigma_1(uint32_t x);
#endif
