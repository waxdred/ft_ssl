#include "flag.h"

void PrintHelp(char *algo) {
  ft_dprintf(2, "usage: ft_ssl command [flags] [file/string]\n");
  ft_dprintf(2, "Commands:\n\t%s\n\tsha-256\n", algo);
  ft_dprintf(2, "Flags:\n");
  ft_dprintf(2, "\t-h\tPrints the help\n");
  ft_dprintf(2, "\t-q\tQuiet mode\n");
  ft_dprintf(2, "\t-r\tReverse the output format\n");
  ft_dprintf(2, "\t-s\tPrint the sum of the given string\n");
  ft_dprintf(2,
             "\t-p\tEcho STDIN to STDOUT and append the checksum to STDOUT\n");
}

void PrintError(TypeInput type, const char *name, InputAlgo *algo) {
  switch (type) {
  case TYPE_ERR_STDIN:
    break;
  case TYPE_ERR_STRING:
    ft_dprintf(2, "ft_ssl: %s: %s: No such file or directory\n", algo, name);
    break;
  case TYPE_ERR_FILE:
    ft_dprintf(2, "ft_ssl: %s: %s: No such file or directory\n", algo, name);
    break;
  case TYPE_ERR_USAGE:
    ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n", name);
    break;
  case TYPE_ERR_CMD:
    ft_dprintf(2,
               "ft_ssl: Error: '%s' is an invalid "
               "command.\nCommands:\n\tmd5\n\tsha-256\n",
               name);
    break;
  }
}
