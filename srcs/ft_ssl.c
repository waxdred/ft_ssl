#include "../includes/ft_ssl.h"

t_ssl *Get_ssl(t_ssl *s) {
  static t_ssl *ssl;
  if (s != NULL)
    ssl = s;
  return ssl;
}

t_ssl *New_ssl() {
  t_ssl *ssl = (t_ssl *)malloc(sizeof(t_ssl));
  if (!ssl) {
    perror("malloc");
    exit(1);
  }
  ft_bzero(ssl, sizeof(t_ssl));
  Get_ssl(ssl);
  return ssl;
}

void Free_ssl() {
  t_ssl *ssl = Get_ssl(NULL);
  if (ssl->md5 != NULL) {
    ssl->md5->Free();
  }
  if (ssl->sha256 != NULL) {
    ssl->sha256->Free();
  }
  free(ssl);
}

int Init_ssl(t_flag flag) {
  t_ssl *ssl = Get_ssl(NULL);
  if (ssl == NULL) {
    return 1;
  }
  ssl->flag = flag;
  ssl->cmd = flag.cmd;
  ssl->Init_ssl = &Init_ssl;
  ssl->Free = &Free_ssl;
  switch (ssl->cmd) {
  case MD5:
    ssl->md5 = ft_NewMD5(flag);
    if (ssl->md5 == NULL) {
      ft_printf("Error: malloc failed\n");
      return (1);
    }
    ssl->Run = &RunMD5;
    break;
  case SHA256:
    ssl->sha256 = ft_NewSha256(flag);
    if (ssl->sha256 == NULL) {
      ft_printf("Error: malloc failed\n");
      return (1);
    }
    ssl->Run = &Runsha256;
    break;
    break;
  default:
    return 1;
    break;
  }
  return 0;
}
