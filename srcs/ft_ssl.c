#include "../includes/ft_ssl.h"

t_ssl *Get_ssl(t_ssl *s) {
  static t_ssl *ssl;
  if (s != NULL)
    ssl = s;
  return ssl;
}

int Handler_ssl() {
  t_ssl *ssl = Get_ssl(NULL);
  switch (ssl->cmd) {
  case MD5:
    return ssl->Run();
  case SHA256:
    break;
  }
  return 0;
}

t_ssl *New_ssl() {
  t_ssl *ssl = (t_ssl *)malloc(sizeof(t_ssl));
  if (!ssl) {
    perror("malloc");
    exit(1);
  }
  ft_bzero(ssl, sizeof(t_ssl));
  ssl->Handler = &Handler_ssl;
  return ssl;
}

void Free_ssl() {
  t_ssl *ssl = Get_ssl(NULL);
  if (ssl->md5 != NULL) {
    ssl->Free();
  }
  /// Need to implement Free_sha256
  free(ssl);
}

int Init_ssl(t_flag flag) {
  t_ssl *ssl = Get_ssl(NULL);
  ssl->flag = flag;
  ssl->cmd = flag.cmd;
  ssl->Init_ssl = &Init_ssl;
  switch (ssl->cmd) {
  case MD5:
    ssl->md5 = ft_NewMD5(flag);
    if (ssl->md5 == NULL) {
      printf("Error: malloc failed\n");
      return (1);
    }
    ssl->Run = &RunMD5;
    break;
  case SHA256:
    // TODO implement
    // ssl->sha256 = New_sha256(flag);
    break;
  default:
    return 1;
    break;
  }
  return 0;
}
