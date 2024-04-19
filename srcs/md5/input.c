#include "../../includes/flag.h"

t_input *AddInput(t_input **input, char *str, TypeInput type, char *filename) {
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
