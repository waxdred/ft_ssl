#include "../includes/md5.h"
#include <unistd.h>

t_md5 *Get_md5(t_md5 *md5) {
  static t_md5 *digest;
  if (md5 != NULL)
    digest = md5;
  return digest;
}

void FreeMD5() {
  t_md5 *md5 = Get_md5(NULL);
  free(md5->digest);
  free(md5);
}

void WriteData(void *data) {
  t_md5 *md5 = Get_md5(NULL);
  if (md5 == NULL)
    return;
  if (md5->flag.flag & FLAG_S) {
    FdData data = {
        .fd = STDIN_FILENO,
    };
    md5->digest->Write(&data);
  } else if (md5->flag.flag & FLAG_IS_FILE) {
    FdData data = {
        .fd = md5->flag.fd,
    };
    md5->digest->Write(&data);
    close(md5->flag.fd);
  } else {
    md5->digest->Write(data);
  }
}

t_md5 *ft_NewMD5(t_flag flag) {
  t_md5 *md5 = malloc(sizeof(t_md5));
  if (md5 == NULL)
    return NULL;
  ft_bzero(md5, sizeof(t_md5));
  md5->digest = Init_digest(flag.flag);
  if (md5->digest == NULL) {
    free(md5);
    return NULL;
  }
  md5->flag = flag;
  md5->Write = &WriteData;
  md5->LeftRotate = &leftrotate;
  md5->Free = &FreeMD5;
  md5->PrintSum = &PrintSum;
  Get_md5(md5);
  return md5;
}
