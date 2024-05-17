#ifndef FT_FLAG_H
#define FT_FLAG_H

#include "ft_printf.h"
#include "utils.h"

typedef int FlagType;
typedef int FlagCmd;
typedef int FD;
typedef char InputType;
typedef int TypeInput;

#define TYPE_ERR_FILE -1
#define TYPE_ERR_STRING -2
#define TYPE_ERR_STDIN -3
#define TYPE_ERR_USAGE -4
#define TYPE_ERR_CMD -5
#define TYPE_FILE 1
#define TYPE_STRING 2
#define TYPE_STDIN 3
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define MD5 1
#define SHA256 2
#define FLAG_P (1 << 1)
#define FLAG_Q (1 << 2)
#define FLAG_R (1 << 3)
#define FLAG_S (1 << 4)
#define FLAG_IS_FILE (1 << 5)

typedef struct s_input {
  TypeInput type;
  InputType *input;
  char *filename;
  struct s_input *next;
} t_input;

typedef struct s_flag {
  FlagType flag;
  char *cmd;
  t_input *head;
} t_flag;
int parse(t_flag *flag, int ac, char **av, char **hashList);
t_input *AddInput(t_input **input, char *str, TypeInput type, char *filename);
void PrintHelp();
void FreeFlag(t_flag *flag);
void PrintError(TypeInput type, const char *name, char *cmd);

#endif
