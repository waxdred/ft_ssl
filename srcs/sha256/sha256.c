#include "../../includes/sha256.h"

t_sha256 *Get_sha256(t_sha256 *sha256) {
  static t_sha256 *digest;
  if (sha256 != NULL)
    digest = sha256;
  return digest;
}

void FreeSha256() {
  t_sha256 *sha256 = Get_sha256(NULL);
  free(sha256->digest);
  free(sha256);
}

static void PrintAllSum() {
  t_sha256 *sha256 = Get_sha256(NULL);
  t_input *tmp_input = sha256->flag.head;

  while (tmp_input) {
    printf("PrintAllSum\n");
    char *input = tmp_input->input;
    sha256->digest->Reset();
    if (tmp_input->type == TYPE_ERR_FILE) {
      PrintError(tmp_input->type, tmp_input->filename, sha256->flag.cmd);
    } else if (tmp_input->type == TYPE_ERR_STRING) {
      PrintError(tmp_input->type, input, sha256->flag.cmd);
    }
    if (tmp_input->type == TYPE_STDIN) {
      if (sha256->flag.flag & FLAG_P) {
        int len = ft_strlen(input);
        if (input[len - 1] == '\n') {
          char *tmp = ft_strdup(input);
          tmp[len - 1] = 0;
          sha256->digest->Write(tmp);
          Print_Sha256(sha256->flag.flag, tmp_input->type, tmp,
                       sha256->digest->Print);
          free(tmp);
        } else {
          sha256->digest->Write(input);
          Print_Sha256(sha256->flag.flag, tmp_input->type, input,
                       sha256->digest->Print);
        }
      } else {
        sha256->digest->Write(input);
        Print_Sha256(sha256->flag.flag, tmp_input->type, "stdin",
                     sha256->digest->Print);
      }
    } else if (tmp_input->type == TYPE_STRING) {
      sha256->digest->Write(input);
      Print_Sha256(sha256->flag.flag, tmp_input->type, input,
                   sha256->digest->Print);
    } else if (tmp_input->type == TYPE_FILE) {
      sha256->digest->Write(input);
      Print_Sha256(sha256->flag.flag, tmp_input->type, tmp_input->filename,
                   sha256->digest->Print);
    }
    tmp_input = tmp_input->next;
  }
}

int Runsha256() {
  t_sha256 *sha256 = Get_sha256(NULL);
  // sha256->digest->Write = &sha256_update;
  // sha256->digest->Print = &PrintSha256;
  // sha256->digest->Write("test");
  // sha256->digest->Print();
  if (sha256->flag.head == NULL) {
    char *s = ReadStdin();
    AddInput(&sha256->flag.head, s, TYPE_STDIN, "");
    sha256->PrintSum();
    return (0);
  }
  sha256->PrintSum();
  return 0;
}

t_sha256 *ft_NewSha256(t_flag flag) {
  t_sha256 *sha256 = (t_sha256 *)malloc(sizeof(t_sha256));
  if (!sha256) {
    perror("malloc");
    exit(1);
  }
  ft_bzero(sha256, sizeof(t_sha256));
  sha256->digest = Init_digest(flag.cmd);
  if (sha256->digest == NULL) {
    free(sha256);
    return NULL;
  }
  sha256->digest->SetGet_RK(NULL, &get_sha256_K);
  // TODO add init digest
  Get_sha256(sha256);
  sha256->flag = flag;
  sha256->Free = &FreeSha256;
  sha256->PrintSum = &PrintAllSum;
  sha256->digest->Write = &sha256_update;
  // sha256->digest->Write = &Write;
  return sha256;
}
