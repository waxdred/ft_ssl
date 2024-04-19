#ifndef MD5_H
#define MD5_H
#include "./flag.h"
#include "./utils.h"
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// The blocksize of MD5 in bytes.
#define DIGESTSIZE 16
#define BlockSize 64
#define BUF_SIZE 512

typedef unsigned int uint32_t;
typedef unsigned char byte;

#define INIT0 0x67452301
#define INIT1 0xEFCDAB89
#define INIT2 0x98BADCFE
#define INIT3 0x10325476

#define NOARG 0
#define WITHARG 1

typedef struct s_digest {
  uint32_t s[4];
  uint8_t digest[DIGESTSIZE];
  int nx;
  uint64_t len;
  void (*Write)(char *f);
  uint32_t *(*Get_R)();
  uint32_t *(*Get_K)();
  void (*Print)();
  struct s_digest *(*Reset)();
} t_digest;

typedef struct s_md5 {
  t_digest *digest;
  t_flag flag;
  void (*Free)();
  void (*PrintSum)();
  int Stop;
  uint32_t (*LeftRotate)(uint32_t x, uint32_t c);
} t_md5;

int RunMD5();
void PrintSum();
char *ReadStdin();
void Write(char *p);
t_digest *Init_digest();
t_digest *Get_digest(t_digest *d);
t_md5 *Get_md5(t_md5 *md5);
t_digest *Reset_digest();
void digest(size_t new_length, uint8_t *padded_message);
t_md5 *ft_NewMD5(t_flag flag);
void ft_blockGeneric(t_digest *dig, const char *p);
uint32_t *get_K();
uint32_t *get_R();
uint32_t leftrotate(uint32_t x, uint32_t c);
void signal_handler(int signum);

#endif
