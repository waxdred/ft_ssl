#include "../includes/flag.h"
#include <stdio.h>

static void ft_getopt(char *av, char *flag, int *opt) {
  const char *optchar;

  if (av[0] != '-') {
    *opt = -1;
    return;
  } else if (av[0] == '-' && av[2] != '\0') {
    *opt = -2;
    // check if cmd
    return;
  }
  *opt = av[1];
  optchar = ft_strchr(flag, *opt);
  if (optchar == NULL) {
    *opt = '?';
    return;
  }
}

int parse(t_flag *flag, int ac, char **av) {
  int opt;
  int i;

  opt = 0;
  i = 1;
  while (i < ac) {
    ft_getopt(av[i], "hpqrs?", &opt);
    if (opt == -1 && flag->cmd == 0) {
      if (ft_strcmp(av[i], "md5") == 0) {
        flag->cmd = MD5;
      } else if (ft_strcmp(av[i], "sha256") == 0) {
        flag->cmd = SHA256;
      } else {
        return EXIT_FAILURE;
      }
    } else if (opt == -1 && !flag->input) {
      int fd;
      if ((fd = OpenFile(av[i])) != -1) {
        printf("add ->fd = %d\n", fd);
        flag->fd = fd;
        flag->flag |= FLAG_IS_FILE;
      } else {
        flag->input = ft_strdup(av[i]);
      }
    } else if (opt == -1) {
      return EXIT_FAILURE;
    }
    switch (opt) {
    case 'h':
      printf("Usage: ft_ssl command [command opts] [command args]\n");
      break;
    case '?':
      printf("ft_ssl: Error: '%c' is an invalid command.\n\n", opt);
      break;
    case 'p':
      flag->flag |= FLAG_P;
      break;
    case 'q':
      flag->flag |= FLAG_Q;
      break;
    case 'r':
      flag->flag |= FLAG_R;
      break;
    case 's':
      flag->flag |= FLAG_S;
      break;
    }
    ++i;
  }
  if (flag->cmd == 0)
    // print no cmd
    return EXIT_FAILURE;
  if (flag->fd != 0 && flag->flag & FLAG_IS_FILE) {
    printf("succes\n");
    return EXIT_SUCCESS;
  }
  if (!(flag->flag & FLAG_S) && !flag->input) {
    // print no input
    return EXIT_FAILURE;
  }
  printf("flag = %d\n", flag->flag);
  return EXIT_SUCCESS;
}
