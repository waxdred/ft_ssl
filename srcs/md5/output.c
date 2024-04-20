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
  switch (t) {
  case TYPE_STDIN:
    q ? p ? printf("MD5 (\"stdin\") = ") : printf("(\"%s\") = ", str)
      : printf(" ");
    Print();
    printf("\n");
    break;
  case TYPE_STRING:
    if (r) {
      q ? printf("MD5 (\"%s\") = ", str) : printf(" ");
      Print();
      printf("\n");
    } else {
      Print();
      q ? printf(" \"%s\"\n", str) : printf("\n");
    }
    break;
  case TYPE_FILE:
    if (r) {
      q ? printf("MD5 (%s) = ", str) : printf(" ");
      Print();
      printf("\n");
    } else {
      Print();
      q ? printf(" %s\n", str) : printf("\n");
    }
  }
}
