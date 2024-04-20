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

int Runsha256() {
  t_sha256 *sha256 = Get_sha256(NULL);
  if (sha256->flag.head == NULL) {
    // char *s = ReadStdin();
    // AddInput(&sha256->flag.head, s, TYPE_STDIN, "");
    // sha256->PrintSum();
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
  // sha256->PrintSum = &PrintAllSum;
  // sha256->digest->Write = &Write;
  return sha256;
}
