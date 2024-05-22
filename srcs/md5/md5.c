#include <md5.h>

t_func ft_NewMD5() {
  t_func func = {0};
  func.Get_Init = &get_md5_Init;
  func.Write = &Write_md5;
  func.Print = &PrintSumMd5;
  return func;
}
