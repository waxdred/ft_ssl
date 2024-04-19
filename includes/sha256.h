#ifndef SHA256_H
#define SHA256_H
#include "./digest.h"
#include "./flag.h"
#include "./utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_sha256 {
  t_digest *digest;
  t_flag flag;
  void (*Free)();
  void (*PrintSum)();
  int Stop;
  uint32_t (*LeftRotate)(uint32_t x, uint32_t c);
  uint32_t(*get_K);
  uint32_t(*get_R);
} t_sha256;

t_sha256 *ft_NewSha256(t_flag flag);
t_sha256 *Get_sha256(t_sha256 *sha256);
uint32_t *get_sha256_K();

#endif
