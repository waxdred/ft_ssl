#include "../../includes/md5.h"

void Write(char *p) {
  if (p == NULL)
    return;
  t_digest *dig = Get_digest(NULL);
  if (p == NULL)
    return;
  dig->len = ft_strlen(p);
  size_t new_length = (dig->len + 8) / BlockSize * BlockSize + BlockSize;
  uint8_t *padded_message = (uint8_t *)malloc(new_length * sizeof(uint8_t));
  ft_bzero(padded_message, new_length * sizeof(uint8_t));
  memcpy(padded_message, p, dig->len);
  padded_message[dig->len] = 0x80;
  padded_message[new_length - 8] = dig->len * 8;
  digest(new_length, padded_message);
}
