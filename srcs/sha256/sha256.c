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
  unsigned long checkFlagP = (unsigned long)tmp_input->next;

  while (tmp_input) {
    char *input = tmp_input->input;
    sha256->digest->Reset();
    if (tmp_input->type == TYPE_ERR_FILE) {
      PrintError(tmp_input->type, tmp_input->filename, sha256->flag.cmd);
    } else if (tmp_input->type == TYPE_ERR_STRING) {
      PrintError(tmp_input->type, input, sha256->flag.cmd);
    }
    if (tmp_input->type == TYPE_STDIN) {
      if (checkFlagP != 0 && sha256->flag.flag & FLAG_P) {
        sha256->digest->Write((BYTE *)(input));
        Print_Sha256(sha256->flag.flag, tmp_input->type, input,
                     sha256->digest->Print);
      } else if (checkFlagP == 0) {
        sha256->digest->Write((BYTE *)(input));
        Print_Sha256(sha256->flag.flag, tmp_input->type, input,
                     sha256->digest->Print);
      }
    } else if (tmp_input->type == TYPE_STRING) {
      sha256->digest->Write((BYTE *)(input));
      Print_Sha256(sha256->flag.flag, tmp_input->type, input,
                   sha256->digest->Print);
    } else if (tmp_input->type == TYPE_FILE) {
      ft_readline(tmp_input->filename, sha256->digest->Write);
      // sha256->digest->Write(input);
      Print_Sha256(sha256->flag.flag, tmp_input->type, tmp_input->filename,
                   sha256->digest->Print);
    }
    tmp_input = tmp_input->next;
  }
}

int Runsha256() {
  t_sha256 *sha256 = Get_sha256(NULL);
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
    ft_printf("Error: malloc failed\n");
  }
  ft_bzero(sha256, sizeof(t_sha256));
  sha256->digest = Init_digest(flag.cmd);
  if (sha256->digest == NULL) {
    free(sha256);
    return NULL;
  }
  sha256->digest->SetGet_RK(NULL, &get_sha256_K);
  Get_sha256(sha256);
  sha256->flag = flag;
  sha256->Free = &FreeSha256;
  sha256->PrintSum = &PrintAllSum;
  sha256->digest->Write = &Write_sha256;
  return sha256;
}
