#include "utils.h"

void ft_readline(char *file, void (*Write)(unsigned char *f)) {
  int fd;
  char buf[512];
  int ret;
  ft_bzero(buf, 512);
  if ((fd = OpenFile(file)) != -1) {
    while ((ret = read(fd, buf, 512)) > 0) {
      buf[ret] = '\0';
      Write((unsigned char *)(buf));
    }
  }
  close(fd);
}
