#include "utils.h"
#include <digest.h>

void Display_hash(FlagType flag, char *NameHash, void (*Print)(), int is_file,
                  char *input) {

  char *upper = ft_strdup(NameHash);

  upper = ft_strtoupper(upper);

  if (flag & FLAG_Q) {
    if (flag & FLAG_R) {
      Print();
    } else {
      Print();
    }
  } else {
    if (flag & FLAG_R) {
      Print();
      if (flag & FLAG_S) {
        ft_dprintf(1, " \"%s\"", input);
      } else if (is_file) {
        ft_dprintf(1, " %s", input);
      }
    } else {
      if (flag & FLAG_S) {
        ft_dprintf(1, "%s (\"%s\") = ", upper, input);
      } else if (is_file) {
        ft_dprintf(1, "%s (%s) = ", upper, input);
      } else {
        if (flag & FLAG_P) {
          ft_dprintf(1, "(\"%s\") = ", input);
        } else {
          ft_dprintf(1, "(%s) = ", input);
        }
      }
      Print();
    }
  }
  ft_dprintf(1, "\n");
  free(upper);
}
