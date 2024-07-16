#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

char *ft_readline(char *file, void (*Write)(unsigned char *f, size_t len),
                  int retStr) {
  int fd;
  char *buf = NULL;
  char chunk[512];
  size_t len = 0;
  size_t ret;

  if ((fd = OpenFile(file)) != -1) {
    if (ft_strcmp(file, "/dev/stdin") == 0) {
      fd = 0;
    }
    ft_bzero(chunk, 512);
    while ((ret = read(fd, chunk, 64)) > 0) {
      if (retStr == 1) {
        char *new_buffer = ft_realloc(buf, len, len + ret + 1);
        if (new_buffer == NULL) {
          write(2, "Erreur d'allocation mémoire.\n", 30);
          if (buf != NULL)
            free(buf);
          return NULL;
        }

        buf = new_buffer;
        ft_memcpy(buf + len, chunk, ret);
        len += ret;
      }
      Write((unsigned char *)(chunk), ret);
      ft_bzero(chunk, 512);
    }
  }
  if (buf != NULL) {
    buf[len] = '\0';
  }
  close(fd);
  return buf;
}
