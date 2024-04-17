#include "../includes/md5.h"

void Write(void *f) {
  printf("Write\n");
  char *p = (char *)f;
  if (p == NULL)
    return;
  t_digest *dig = Get_digest(NULL);
  if (p == NULL)
    return;
  dig->len = strlen(p);
  size_t new_length = (dig->len + 8) / BlockSize * BlockSize + BlockSize;
  uint8_t *padded_message = (uint8_t *)malloc(new_length * sizeof(uint8_t));
  memcpy(padded_message, p, dig->len);
  padded_message[dig->len] = 0x80;
  padded_message[new_length - 8] = dig->len * 8;
  digest(new_length, padded_message);
}

void WriteFd(void *f) {
  printf("WriteFd\n");
  FdData *fd = (FdData *)f;
  t_digest *d = Get_digest(NULL);
  char *p = NULL;
  char buf[BUF_SIZE];
  int ret;
  t_digest *dig = Get_digest(NULL);
  d->len = 0;
  ft_bzero(buf, BUF_SIZE);
  while ((ret = read(fd->fd, buf, BUF_SIZE)) > 0) {
    p = realloc(p, d->len + ret);
    memcpy(p + d->len, buf, ret);
    d->len += ret;
  }
  printf("p = %s", p);
  if (p == NULL)
    return;
  dig->len = strlen(p);
  size_t new_length = (dig->len + 8) / BlockSize * BlockSize + BlockSize;
  uint8_t *padded_message = (uint8_t *)malloc(new_length * sizeof(uint8_t));
  memcpy(padded_message, p, dig->len);
  padded_message[dig->len] = 0x80;
  padded_message[new_length - 8] = dig->len * 8;
  digest(new_length, padded_message);
}
