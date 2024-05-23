#include "flag.h"

static t_input *AddInput(t_input **input, char *str, TypeInput type,
                         char *filename) {
  t_input *new_input;
  new_input = (t_input *)malloc(sizeof(t_input));
  if (!new_input) {
    perror("malloc");
    exit(1);
  }
  ft_bzero(new_input, sizeof(t_input));
  new_input->type = type;
  new_input->input = str;
  new_input->filename = ft_strdup(filename);
  new_input->next = NULL;
  if (!*input) {
    *input = new_input;
  } else {
    t_input *current = *input;
    while (current->next) {
      current = current->next;
    }
    current->next = new_input;
  }
  return new_input;
}

static void ft_getopt(char *av, char *flag, int *opt) {
  const char *optchar;

  if (av[0] != '-') {
    *opt = -1;
    return;
  } else if (av[0] == '-' && av[2] != '\0') {
    *opt = -2;
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
    if (tmp->input != NULL) {
      free(tmp->input);
    }
    if (tmp->filename != NULL) {
      free(tmp->filename);
    }
    free(tmp);
    tmp = next;
  }
}

int parse(t_flag *flag, int ac, char **av) {
  int opt;
  int i;
  int fd;
  int done = 0;

  opt = 0;
  i = 1;
  flag->algo = av[1];
  i++;
  while (i < ac) {
    if (done == 1) {
      while (i < ac) {
        if ((fd = OpenFile(av[i])) != -1) {
          AddInput(&flag->head, ft_strdup(""), TYPE_FILE, av[i]);
        } else {
          AddInput(&flag->head, ft_strdup(""), TYPE_ERR_FILE, av[i]);
        }
        i++;
      }
      break;
    }
    ft_getopt(av[i], "hpqrs?", &opt);
    if (opt == -1) {
      int fd;
      if ((fd = OpenFile(av[i])) != -1) {
        AddInput(&flag->head, ft_strdup(""), TYPE_FILE, av[i]);
        done = 1;
      } else {
        AddInput(&flag->head, ft_strdup(""), TYPE_ERR_FILE, av[i]);
        done = 1;
      }
    } else if (opt == -1) {
      return EXIT_FAILURE;
    }
    switch (opt) {
    case 'h':
      PrintHelp(flag->algo);
      break;
    case '?':
      PrintError(TYPE_ERR_USAGE, av[i], flag->algo);
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
      if (i + 1 <= ac)
        AddInput(&flag->head, ft_strdup(av[i + 1]), TYPE_STRING, av[i]);
      flag->flag |= FLAG_S;
      done = 1;
      ++i;
      break;
    }
    ++i;
  }
  return EXIT_SUCCESS;
}
