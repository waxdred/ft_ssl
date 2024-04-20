#include "../includes/flag.h"

void PrintError(TypeInput type, const char *name, FlagCmd cmd) {
  char *cmd_name = cmd == MD5 ? "md5" : "sha256";
  switch (type) {
  case TYPE_ERR_STDIN:
    break;
  case TYPE_ERR_STRING:
    printf("ft_ssl: %s: %s: No such file or directory\n", cmd_name, name);
    break;
  case TYPE_ERR_FILE:
    printf("ft_ssl: %s: %s: No such file or directory\n", cmd_name, name);
    break;
  case TYPE_ERR_USAGE:
    printf("ft_ssl: Error: '%s' is an invalid command.\n", name);
    break;
  case TYPE_ERR_CMD:
    printf("ft_ssl: Error: '%s' is an invalid "
           "command.\nCommands:\n\tmd5\n\tsha-256\n",
           name);
    break;
  }
}
