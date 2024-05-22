#include <sha256.h>

t_func ft_NewSHA256() {
  t_func func = {0};
  func.Get_Init = &get_sha256_Init;
  func.Write = &Write_sha256;
  func.Print = &PrintSumSha256;
  return func;
}
