#include "../../includes/sha256.h"

void Print_Sha256(int reverse, TypeInput t, const char *str, void (*Print)()) {
  int r = !(reverse & FLAG_R);
  int p = !(reverse & FLAG_P);
  int q = !(reverse & FLAG_Q);
  switch (t) {
  case TYPE_STDIN:
    q ? p ? printf("SHA256 (\"stdin\") = ") : printf("(\"%s\") = ", str)
      : printf(" ");
    Print();
    printf("\n");
    break;
  case TYPE_STRING:
    if (r) {
      q ? printf("SHA256 (\"%s\") = ", str) : printf(" ");
      Print();
      printf("\n");
    } else {
      Print();
      q ? printf(" \"%s\"\n", str) : printf("\n");
    }
    break;
  case TYPE_FILE:
    if (r) {
      q ? printf("SHA256 (%s) = ", str) : printf(" ");
      Print();
      printf("\n");
    } else {
      Print();
      q ? printf(" %s\n", str) : printf("\n");
    }
  }
}
