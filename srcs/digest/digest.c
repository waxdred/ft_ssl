#include "../../includes/digest.h"

t_digest *Get_digest(t_digest *d) {
  static t_digest *digest;
  if (d != NULL)
    digest = d;
  return digest;
}

void SetGet_RK(uint32_t *(*Get_R)(), uint32_t *(*Get_K)()) {
  t_digest *d = Get_digest(NULL);
  if (Get_R != NULL)
    d->Get_R = Get_R;
  if (Get_K != NULL)
    d->Get_K = Get_K;
}

// TODO: need found way not use if else or switch statement
t_digest *Init_digest(FlagCmd cmd) {
  t_digest *d = malloc(sizeof(t_digest));
  if (d == NULL)
    return NULL;
  ft_bzero(d, sizeof(t_digest));
  switch (cmd) {
  case MD5:
    d->Reset = &Reset_digest_md5;
    d->digest = &md5_digest;
    d->Write = &Write_md5;
    d->Print = &PrintSumMd5;
    break;
  case SHA256:
    d->Reset = &Reset_digest_sha256;
    d->Print = &PrintSha256;
    d->Reset = &Reset_digest_sha256;
    d->Write = &Write_sha256;
    break;
  }
  Get_digest(d);
  d->SetGet_RK = &SetGet_RK;
  d->Reset();
  return d;
}

t_digest *Reset_digest_sha256() {
  t_digest *d = Get_digest(NULL);
  for (int i = 0; i <= d->init_size; i++) {
    d->m[i] = d->Get_S()[i];
  }
  d->nx = 0;
  d->len = 0;
  d->lenbits = 0;
  return d;
}

t_digest *Reset_digest_md5() {
  t_digest *d = Get_digest(NULL);
  for
    d->m[0] = MD5_INIT0;
  d->m[1] = MD5_INIT1;
  d->m[2] = MD5_INIT2;
  d->m[3] = MD5_INIT3;
  d->nx = 0;
  d->len = 0;
  return d;
}
