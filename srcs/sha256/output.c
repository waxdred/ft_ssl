#include "../../includes/sha256.h"

void Print_Sha256(int reverse, TypeInput t, const char *str, void (*Print)()) {
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
        printf("SHA256 (\"%s\") = ", str);
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
        printf("SHA256 (%s) = ", str);
      }
      Print();
      printf("\n");
    } else {
      Print();
      q ? printf(" %s\n", str) : printf("\n");
    }
  }
}
