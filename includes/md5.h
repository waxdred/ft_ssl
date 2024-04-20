#ifndef MD5_H
#define MD5_H
#include "./digest.h"
#include "./flag.h"
#include "./utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NOARG 0
#define WITHARG 1

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
void PrintHelp();
void PrintMd5(int reverse, TypeInput t, const char *str, void (*Print)());

#endif
