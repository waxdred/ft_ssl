#ifndef FT_FLAG_H
#define FT_FLAG_H

#include "utils.h"

typedef int FlagType;
typedef int FlagCmd;
typedef int FD;
typedef char InputType;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define MD5 1
#define SHA256 2
#define FLAG_P (1 << 1)
#define FLAG_Q (1 << 2)
#define FLAG_R (1 << 3)
#define FLAG_S (1 << 4)
#define FLAG_IS_FILE (1 << 5)

typedef struct s_flag {
  FlagType flag;
  FlagCmd cmd;
  InputType *input;
  FD fd;
} t_flag;
int parse(t_flag *flag, int ac, char **av);

#endif
