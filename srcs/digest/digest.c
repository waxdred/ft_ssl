#include "digest.h"
#include <stdio.h>

t_digest *Get_digest(t_digest *d) {
  static t_digest *digest;
  if (d != NULL)
    digest = d;
  return digest;
}

t_algo **AddAlgo(t_algo **algo, char *name, t_func *f, uint8_t m_size) {
  t_algo *new_algo;
  new_algo = malloc(sizeof(t_algo));
  if (!new_algo) {
    return NULL;
  }
  ft_bzero(new_algo, sizeof(t_algo));
  new_algo->name = name;
  new_algo->func = f;
  new_algo->m_size = m_size;
  if (!*algo) {
    *algo = new_algo;
  } else {
    t_algo *current = *algo;
    while (current->next) {
      current = current->next;
    }
    current->next = new_algo;
  }

  return algo;
}

void Free() {
  t_digest *dig = Get_digest(NULL);
  t_algo *algo = dig->algo;
  while (algo) {
    t_algo *next = algo->next;
    free(algo);
    algo = next;
  }
  free(dig);
}

static void SetAlgo(char *name, t_func *f, uint8_t m_size) {
  t_digest *dig = Get_digest(NULL);
  AddAlgo(&(dig->algo), name, f, m_size);
}

static void Reset_algo() {
  t_digest *dig = Get_digest(NULL);
  t_algo *algo = dig->algo_run;
  ft_bzero(dig->m, BLOCKSIZE);
  ft_bzero(dig->hash, HASHSIZE);
  ft_bzero(dig->digest_hash, BLOCKSIZE);
  for (int i = 0; i < algo->m_size; i++) {
    dig->m[i] = algo->func->Get_Init()[i];
  }
  dig->nx = 0;
  dig->len = 0;
  dig->lenbits = 0;
}

static t_algo *get_algo(char *algo) {
  t_algo *a = Get_digest(NULL)->algo;
  while (a) {
    if (!ft_strcmp(algo, a->name)) {
      return a;
    }
    a = a->next;
  }
  return NULL;
}

static void Run(t_flag *flag) {
  t_input *tmp = flag->head;
  t_digest *dig = Get_digest(NULL);
  dig->algo_run = get_algo(flag->algo);
  t_algo *algo = dig->algo_run;

  if (!dig->algo_run) {
    ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n", flag->algo);
    return;
  }

  dig->Reset();
  if ((flag->flag & FLAG_P || tmp == NULL)) {
    char *input = "stdin";
    char *inputRead = NULL;
    inputRead = ft_readline("/dev/stdin", algo->func->Write, 1);
    if (inputRead != NULL) {
      Display_hash(flag->flag, 0, algo->name, algo->func->Print, 0,
                   flag->flag & FLAG_P ? inputRead : input);
      if (inputRead != NULL) {
        free(inputRead);
      }
    } else {
      Display_hash(flag->flag, 0, algo->name, algo->func->Print, 0,
                   flag->flag & FLAG_P ? "" : input);
    }
  }
  while (tmp) {
    char *input = tmp->input;
    int is_file = 0;
    dig->Reset();
    if (tmp->type == TYPE_ERR_FILE) {
      PrintError(tmp->type, tmp->filename, algo->name);
      tmp = tmp->next;
      continue;
    } else if (tmp->type == TYPE_ERR_STRING) {
      PrintError(tmp->type, input, dig->algo_run->name);
      tmp = tmp->next;
      continue;
    }
    if (tmp->type == TYPE_STDIN || tmp->type == TYPE_STRING) {
      algo->func->Write((byte *)input);
    } else if (tmp->type == TYPE_FILE) {
      ft_readline(tmp->filename, algo->func->Write, 0);
      input = tmp->filename;
      is_file = 1;
    }

    Display_hash(flag->flag, tmp->type, algo->name, algo->func->Print, is_file,
                 input);
    tmp = tmp->next;
  }
}

t_digest *Init_digest() {
  t_digest *dig;

  dig = malloc(sizeof(t_digest));
  if (!dig) {
    return NULL;
  }
  ft_bzero(dig, sizeof(t_digest));
  Get_digest(dig);
  dig->AddAlgo = &SetAlgo;
  dig->Reset = &Reset_algo;
  dig->Run = &Run;
  dig->Free = &Free;
  return dig;
}
