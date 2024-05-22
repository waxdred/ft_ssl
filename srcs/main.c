#include "flag.h"
#include <digest.h>
#include <md5.h>

int main(int argc, char **argv) {
  t_flag flag = {0};
  t_func f = {0};
  t_digest *dig = Init_digest();

  if (!dig) {
    ft_dprintf(2, "malloc error\n");
    return (1);
  }

  // Init algo to digest
  f = ft_NewMD5();
  dig->AddAlgo("md5", &f, 4);

  if (argc < 2) {
    ft_dprintf(2, "usage: ft_ssl command [flags] [file/string]");
    dig->Free();
    return (1);
  }

  if (parse(&flag, argc, argv)) {
    dig->Free();
    return (1);
  }
  dig->Run(&flag);
  FreeFlag(&flag);
  dig->Free();

  return (0);
}
