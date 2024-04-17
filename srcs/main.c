#include "../includes/ft_ssl.h"

int main(int argc, char **argv) {
  t_md5 *md5;
  t_flag flag;
  if (argc < 2)
    return (1);

  if (parse(&flag, argc, argv)) {
    printf("ft_ssl: Error: '%s' is an invalid command.\n\n", argv[1]);
    return (1);
  }

  md5 = ft_NewMD5(flag);
  if (md5 == NULL)
    return (1);
  printf("flag = %d\n", md5->flag.flag);
  md5->Write(flag.input);
  md5->PrintSum();
  md5->Free();
  return (0);
}
