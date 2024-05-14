#include "../../includes/md5.h"

void PrintHelp() {
  ft_printf("usage: ft_ssl command [flags] [file/string]\n");
  ft_printf("Commands:\n\tmd5\n\tsha-256\n");
  ft_printf("Flags:\n");
  ft_printf("\t-h\tPrints the help\n");
  ft_printf("\t-q\tQuiet mode\n");
  ft_printf("\t-r\tReverse the output format\n");
  ft_printf("\t-s\tPrint the sum of the given string\n");
  ft_printf("\t-p\tEcho STDIN to STDOUT and append the checksum to STDOUT\n");
}

void PrintMd5(int reverse, TypeInput t, const char *str, void (*Print)()) {
  int r = !(reverse & FLAG_R);
  int p = !(reverse & FLAG_P);
  int q = !(reverse & FLAG_Q);
  char *s = NULL;
  switch (t) {
  case TYPE_STDIN:
    s = ft_strdup(str);
    s = ft_trimLastWhiteSpace(s);
    if (q) {
      p ? ft_printf("(stdin)= ") : ft_printf("(\"%s\")= ", s);
    }
    Print();
    ft_printf("\n");
    free(s);
    break;
  case TYPE_STRING:
    if (r) {
      if (q) {
        ft_printf("MD5 (\"%s\") = ", str);
      }
      Print();
      ft_printf("\n");
    } else {
      Print();
      q ? ft_printf(" \"%s\"\n", str) : ft_printf("\n");
    }
    break;
  case TYPE_FILE:
    if (r) {
      if (q) {
        ft_printf("MD5 (%s) = ", str);
      }
      Print();
      ft_printf("\n");
    } else {
      Print();
      q ? ft_printf(" %s\n", str) : ft_printf("\n");
    }
  }
}
