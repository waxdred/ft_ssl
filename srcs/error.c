#include "../includes/flag.h"

void PrintError(TypeInput type, const char *name, char *cmd) {
  switch (type) {
  case TYPE_ERR_STDIN:
    break;
  case TYPE_ERR_STRING:
    ft_printf("ft_ssl: %s: %s: No such file or directory\n", cmd, name);
    break;
  case TYPE_ERR_FILE:
    ft_printf("ft_ssl: %s: %s: No such file or directory\n", cmd, name);
    break;
  case TYPE_ERR_USAGE:
    ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", name);
    break;
  case TYPE_ERR_CMD:
    ft_printf("ft_ssl: Error: '%s' is an invalid "
              "command.\nCommands:\n\tmd5\n\tsha-256\n",
              name);
    break;
  }
}
