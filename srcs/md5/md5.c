#include "../../includes/md5.h"

t_md5 *Get_md5(t_md5 *md5) {
  static t_md5 *m;
  if (md5 != NULL)
    m = md5;
  return m;
}

void FreeMD5() {
  t_md5 *md5 = Get_md5(NULL);
  free(md5->digest);
  free(md5);
}

int RunMD5() {
  t_md5 *md5 = Get_md5(NULL);
  if (md5->flag.head == NULL) {
    char *s = ReadStdin();
    AddInput(&md5->flag.head, s, TYPE_STDIN, "");
    md5->PrintSum();
    return (0);
  }
  md5->PrintSum();
  return 0;
}

static void PrintAllSum() {
  t_md5 *md5 = Get_md5(NULL);
  t_input *tmp_input = md5->flag.head;
  unsigned long checkFlagP = (unsigned long)tmp_input->next;

  while (tmp_input) {
    char *input = tmp_input->input;
    md5->digest->Reset();
    if (tmp_input->type == TYPE_ERR_FILE) {
      PrintError(tmp_input->type, tmp_input->filename, md5->flag.cmd);
    } else if (tmp_input->type == TYPE_ERR_STRING) {
      PrintError(tmp_input->type, input, md5->flag.cmd);
    }
    if (tmp_input->type == TYPE_STDIN) {
      if (checkFlagP != 0 && md5->flag.flag & FLAG_P) {
        md5->digest->Write((BYTE *)(input));
        PrintMd5(md5->flag.flag, tmp_input->type, input, md5->digest->Print);
      } else if (checkFlagP == 0) {
        md5->digest->Write((BYTE *)(input));
        PrintMd5(md5->flag.flag, tmp_input->type, input, md5->digest->Print);
      }
    } else if (tmp_input->type == TYPE_STRING) {
      md5->digest->Write((BYTE *)(input));
      PrintMd5(md5->flag.flag, tmp_input->type, input, md5->digest->Print);
    } else if (tmp_input->type == TYPE_FILE) {
      md5->digest->Write((BYTE *)(input));
      PrintMd5(md5->flag.flag, tmp_input->type, tmp_input->filename,
               md5->digest->Print);
    }
    tmp_input = tmp_input->next;
  }
}

t_md5 *ft_NewMD5(t_flag flag) {
  t_md5 *md5 = malloc(sizeof(t_md5));
  if (md5 == NULL)
    return NULL;
  ft_bzero(md5, sizeof(t_md5));
  md5->digest = Init_digest(flag.cmd);
  if (md5->digest == NULL) {
    free(md5);
    return NULL;
  }
  md5->digest->SetGet_RK(&get_md5_R, &get_md5_K);
  md5->flag = flag;
  md5->Free = &FreeMD5;
  md5->PrintSum = &PrintAllSum;
  Get_md5(md5);
  return md5;
}
