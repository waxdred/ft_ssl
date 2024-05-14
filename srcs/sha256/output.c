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
      p ? ft_printf("(stdin)= ") : ft_printf("(\"%s\")= ", s);
    }
    Print();
    ft_printf("\n");
    free(s);
    break;
  case TYPE_STRING:
    if (r) {
      if (q) {
        ft_printf("SHA256 (\"%s\") = ", str);
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
        ft_printf("SHA256 (%s) = ", str);
      }
      Print();
      ft_printf("\n");
    } else {
      Print();
      q ? ft_printf(" %s\n", str) : ft_printf("\n");
    }
  }
}
