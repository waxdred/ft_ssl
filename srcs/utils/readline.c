#include <utils.h>

char *ft_readline(char *file, void (*Write)(unsigned char *f), int retStr) {
  int fd;
  char buf[512];
  int ret;
  char *str = NULL;
  char *tmp = NULL;
  ft_bzero(buf, 512);
  if ((fd = OpenFile(file)) != -1) {
    while ((ret = read(fd, buf, 64)) > 0) {
      buf[ret] = '\0';
      if (retStr == 1) {
        tmp = str;
        str = ft_strjoint(str, buf);
        if (tmp != NULL)
          free(tmp);
      }
      Write((unsigned char *)(buf));
    }
    if (ret == -1) {
      return NULL;
    }
  }
  close(fd);
  return (retStr == 1 ? str : NULL);
}
