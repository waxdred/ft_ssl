#ifndef MD5_H
#define MD5_H
#include "./flag.h"
#include "./utils.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// The blocksize of MD5 in bytes.
#define DIGESTSIZE 16
#define BlockSize 64
#define BUF_SIZE 512

typedef unsigned int uint32_t;
typedef unsigned char byte;
extern int enc64(char *, byte *, int);

#define INIT0 0x67452301
#define INIT1 0xEFCDAB89
#define INIT2 0x98BADCFE
#define INIT3 0x10325476

typedef struct s_digest {
  uint32_t s[4];
  uint8_t digest[DIGESTSIZE];
  int nx;
  uint64_t len;
  void (*Write)(void *f);
  uint32_t *(*Get_R)();
  uint32_t *(*Get_K)();
  struct s_digest *(*Reset)();
} t_digest;

typedef struct {
  int fd;
} FdData;

typedef struct s_md5 {
  t_digest *digest;
  t_flag flag;
  void (*Write)(void *data);
  void (*Free)();
  void (*PrintSum)();
  uint32_t (*LeftRotate)(uint32_t x, uint32_t c);
} t_md5;

void PrintSum();
void Write(void *f);
void WriteFd(void *f);
t_digest *Init_digest(FlagType flag);
t_digest *Get_digest(t_digest *d);
t_digest *Reset_digest();
void digest(size_t new_length, uint8_t *padded_message);
t_md5 *ft_NewMD5(t_flag flag);
void ft_blockGeneric(t_digest *dig, const char *p);
uint32_t *get_K();
uint32_t *get_R();
uint32_t leftrotate(uint32_t x, uint32_t c);

#endif
