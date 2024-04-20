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

void FreeFlag(t_flag *flag) {
  t_input *tmp = flag->head;
  while (tmp) {
    t_input *next = tmp->next;
    free(tmp->input);
    free(tmp->filename);
    free(tmp);
    tmp = next;
  }
}

int parse(t_flag *flag, int ac, char **av) {
  int opt;
  int i;
  int fd;

  opt = 0;
  i = 1;
  // FIRST get stdin
  if ((fd = OpenFile("/dev/stdin")) != -1) {
    char *c = ReadFile(STDIN_FILENO);
    if (c != NULL) {
      AddInput(&flag->head, c, TYPE_STDIN, "");
    }
  }
  if (ft_strcmp(av[i], "md5") == 0) {
    flag->cmd = MD5;
  } else if (ft_strcmp(av[i], "sha256") == 0) {
    flag->cmd = SHA256;
  } else if (ft_strcmp(av[i], "-h") == 0) {
    PrintHelp();
    return EXIT_FAILURE;
  } else {
    PrintError(TYPE_ERR_CMD, av[i]);
    return EXIT_FAILURE;
  }
  i++;
  while (i < ac) {
    ft_getopt(av[i], "hpqrs?", &opt);
    if (opt == -1) {
      int fd;
      if ((fd = OpenFile(av[i])) != -1) {
        char *c = ReadFile(fd);
        if (c != NULL) {
          AddInput(&flag->head, c, TYPE_FILE, av[i]);
        }
      } else {
        AddInput(&flag->head, "", TYPE_ERR_FILE, av[i]);
      }
    } else if (opt == -1) {
      return EXIT_FAILURE;
    }
    switch (opt) {
    case 'h':
      PrintHelp();
      break;
    case '?':
      PrintError(TYPE_ERR_USAGE, av[i]);
      return EXIT_FAILURE;
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
      // Add string to input
      if (i + 1 <= ac)
        AddInput(&flag->head, ft_strdup(av[i + 1]), TYPE_STRING, av[i]);
      flag->flag |= FLAG_S;
      ++i;
      break;
    }
    ++i;
  }
  return EXIT_SUCCESS;
}
