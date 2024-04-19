#ifndef FT_SSL_H
#define FT_SSL_H
#include "./flag.h"
#include "./md5.h"

typedef struct s_ssl {
  t_md5 *md5;
  t_flag flag;
  void (*Free)();
  int (*Run)();
  int (*Handler)();
  int (*Init_ssl)(t_flag flag);
  FlagCmd cmd;
} t_ssl;

t_ssl *New_ssl();
int Init_ssl(t_flag flag);
t_ssl *Get_ssl(t_ssl *s);

#endif
