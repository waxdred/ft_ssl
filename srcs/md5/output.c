#include "../../includes/md5.h"

void PrintHelp() {
  printf("usage: ft_ssl command [flags] [file/string]\n");
  printf("Commands:\n\tmd5\n\tsha-256\n");
  printf("Flags:\n");
  printf("\t-h\tPrints the help\n");
  printf("\t-q\tQuiet mode\n");
  printf("\t-r\tReverse the output format\n");
  printf("\t-s\tPrint the sum of the given string\n");
  printf("\t-p\tEcho STDIN to STDOUT and append the checksum to STDOUT\n");
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
      p ? printf("(stdin)= ") : printf("(\"%s\")= ", s);
    }
    Print();
    printf("\n");
    free(s);
    break;
  case TYPE_STRING:
    if (r) {
      if (q) {
        printf("MD5 (\"%s\") = ", str);
      }
      Print();
      printf("\n");
    } else {
      Print();
      q ? printf(" \"%s\"\n", str) : printf("\n");
    }
    break;
  case TYPE_FILE:
    if (r) {
      if (q) {
        printf("MD5 (%s) = ", str);
      }
      Print();
      printf("\n");
    } else {
      Print();
      q ? printf(" %s\n", str) : printf("\n");
    }
  }
}
