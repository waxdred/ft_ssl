#include "../includes/ft_ssl.h"

int main(int argc, char **argv) {
  t_ssl *ssl = New_ssl();
  t_flag flag = {0};

  if (ssl == NULL) {
    return (1);
  }

  if (argc < 2) {
    printf("usage: ft_ssl command [flags] [file/string]");
    return (1);
  }

  if (parse(&flag, argc, argv)) {
    return (1);
  }

  if (Init_ssl(flag)) {
    return (1);
  }
  ssl->Run();
  ssl->Free();
  FreeFlag(&flag);
  return (0);
}
