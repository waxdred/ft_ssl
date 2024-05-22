#include <digest.h>
#include <flag.h>
#include <md5.h>
#include <sha256.h>

int main(int argc, char **argv) {
  t_flag flag = {0};
  t_func f_md5 = {0};
  t_func f_sha256 = {0};
  t_digest *dig = Init_digest();

  if (!dig) {
    ft_dprintf(2, "malloc error\n");
    return (1);
  }

  // Init algo to digest
  f_md5 = ft_NewMD5();
  dig->AddAlgo("md5", &f_md5, MD5_INIT);
  f_sha256 = ft_NewSHA256();
  dig->AddAlgo("sha256", &f_sha256, SHA256_INIT);

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
