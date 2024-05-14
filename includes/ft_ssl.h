#ifndef FT_SSL_H
#define FT_SSL_H
#include "./digest.h"
#include "./flag.h"
#include "./ft_printf.h"
#include "./md5.h"
#include "./sha256.h"

#define MD5_INIT0 0x67452301
#define MD5_INIT1 0xEFCDAB89
#define MD5_INIT2 0x98BADCFE
#define MD5_INIT3 0x10325476

typedef struct s_ssl {
  t_md5 *md5;
  t_sha256 *sha256;
  t_flag flag;
  void (*Free)();
  int (*Run)();
  int (*Init_ssl)(t_flag flag);
  FlagCmd cmd;
} t_ssl;

t_ssl *New_ssl();
int Init_ssl(t_flag flag);
t_ssl *Get_ssl(t_ssl *s);

#endif
