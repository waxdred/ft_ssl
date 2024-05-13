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

void PrintSumMd5() {
  t_digest *d = Get_digest(NULL);
  for (int i = 0; i < 16; i++) {
    printf("%02x", d->md5_digest[i]);
  }
}

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
    break;
  }
  Get_digest(d);
  d->SetGet_RK = &SetGet_RK;
  d->Reset();
  return d;
}

t_digest *Reset_digest_sha256() {
  t_digest *d = Get_digest(NULL);
  ft_bzero(d->md5_digest, DIGESTSIZE);
  d->s[0] = SHA256_INIT0;
  d->s[1] = SHA256_INIT1;
  d->s[2] = SHA256_INIT2;
  d->s[3] = SHA256_INIT3;
  d->s[4] = SHA256_INIT4;
  d->s[5] = SHA256_INIT5;
  d->s[6] = SHA256_INIT6;
  d->s[7] = SHA256_INIT7;
  d->nx = 0;
  d->len = 0;
  return d;
}

t_digest *Reset_digest_md5() {
  t_digest *d = Get_digest(NULL);
  ft_bzero(d->md5_digest, DIGESTSIZE);

  d->m[0] = MD5_INIT0;
  d->m[1] = MD5_INIT1;
  d->m[2] = MD5_INIT2;
  d->m[3] = MD5_INIT3;
  d->nx = 0;
  d->len = 0;
  return d;
}
