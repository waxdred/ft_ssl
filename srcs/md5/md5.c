#include "../../includes/md5.h"
#include <unistd.h>

t_md5 *Get_md5(t_md5 *md5) {
  static t_md5 *digest;
  if (md5 != NULL)
    digest = md5;
  return digest;
}

void FreeMD5() {
  t_md5 *md5 = Get_md5(NULL);
  while (md5->flag.head) {
    t_input *tmp = md5->flag.head;
    md5->flag.head = md5->flag.head->next;
    free(tmp->input);
    free(tmp->filename);
    free(tmp);
  }
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

  while (tmp_input) {
    char *input = tmp_input->input;
    md5->digest->Reset();
    if (tmp_input->type == TYPE_ERR_FILE) {
      PrintError(tmp_input->type, tmp_input->filename);
    } else if (tmp_input->type == TYPE_ERR_STRING) {
      PrintError(tmp_input->type, input);
    }
    if (tmp_input->type == TYPE_STDIN) {
      if (md5->flag.flag & FLAG_P) {
        int len = ft_strlen(input);
        if (input[len - 1] == '\n') {
          char *tmp = ft_strdup(input);
          tmp[len - 1] = 0;
          md5->digest->Write(tmp);
          PrintMd5(md5->flag.flag, tmp_input->type, tmp, md5->digest->Print);
          free(tmp);
        } else {
          md5->digest->Write(input);
          PrintMd5(md5->flag.flag, tmp_input->type, input, md5->digest->Print);
        }
      } else {
        md5->digest->Write(input);
        PrintMd5(md5->flag.flag, tmp_input->type, "stdin", &PrintSum);
      }
    } else if (tmp_input->type == TYPE_STRING) {
      md5->digest->Write(input);
      PrintMd5(md5->flag.flag, tmp_input->type, input, &PrintSum);
    } else if (tmp_input->type == TYPE_FILE) {
      md5->digest->Write(input);
      PrintMd5(md5->flag.flag, tmp_input->type, tmp_input->filename, &PrintSum);
    }
    tmp_input = tmp_input->next;
  }
}

t_md5 *ft_NewMD5(t_flag flag) {
  t_md5 *md5 = malloc(sizeof(t_md5));
  if (md5 == NULL)
    return NULL;
  ft_bzero(md5, sizeof(t_md5));
  md5->digest = Init_digest();
  if (md5->digest == NULL) {
    free(md5);
    return NULL;
  }
  md5->Stop = 1;
  md5->flag = flag;
  md5->LeftRotate = &leftrotate;
  md5->Free = &FreeMD5;
  md5->PrintSum = &PrintAllSum;
  Get_md5(md5);
  return md5;
}

char *ReadStdin() {
  char buf[512];
  char *p = NULL;
  char *tmp = NULL;
  t_md5 *md5 = Get_md5(NULL);
  int fd = 0, ret = 0;
  fd_set readfds;
  int len = 0;
  struct timeval timeout;

  if ((fd = dup(STDIN_FILENO)) < 0)
    return NULL;

  while (md5->Stop) {
    ft_bzero(buf, 512);
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    ret = select(fd + 1, &readfds, NULL, NULL, &timeout);
    if (ret == -1)
      break;
    else if (ret == 0)
      continue; /* a timeout occured */
    else {
      if (FD_ISSET(fd, &readfds)) {
        if ((ret = read(STDIN_FILENO, buf, 512)) > 0) {
          buf[ret - 1] = 0;
          tmp = p;
          p = ft_strjoin(p, buf);
          if (tmp)
            free(tmp);
          len += ret;
          len += ret;
        } else {
          return p;
        }
      }
    }
  }
  return p;
}
