#ifndef MD5_H
#define MD5_H
#include "./digest.h"
#include "./flag.h"
#include "./ft_printf.h"
#include "./utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NOARG 0
#define WITHARG 1
#define BLOCKSIZE 64
#define HASHSIZE 32
// The blocksize of MD5 in bytes.
#define MD5_INIT0 0x67452301
#define MD5_INIT1 0xEFCDAB89
#define MD5_INIT2 0x98BADCFE
#define MD5_INIT3 0x10325476

typedef struct s_md5 {
  t_digest *digest;
  t_flag flag;
  void (*Free)();
  void (*PrintSum)();
  int Stop;
} t_md5;

int RunMD5();
void PrintSum();
void Write(char *p);
t_digest *Init_digest();
t_digest *Get_digest(t_digest *d);
t_md5 *Get_md5(t_md5 *md5);
t_digest *Reset_digest();
void digest(size_t new_length, uint8_t *padded_message);
t_md5 *ft_NewMD5(t_flag flag);
void ft_blockGeneric(t_digest *dig, const char *p);
uint32_t *get_md5_K();
uint32_t *get_md5_R();
uint32_t *get_md5_S();
void PrintHelp();
void PrintMd5(int reverse, TypeInput t, const char *str, void (*Print)());

uint32_t rotate_left(uint32_t value, uint32_t shift);
uint32_t md5_round_ff(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                      uint32_t x, uint32_t shift, uint32_t constant);
uint32_t md5_round_gg(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                      uint32_t x, uint32_t shift, uint32_t constant);
uint32_t md5_round_hh(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                      uint32_t x, uint32_t shift, uint32_t constant);
uint32_t md5_round_ii(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                      uint32_t x, uint32_t shift, uint32_t constant);

#endif
