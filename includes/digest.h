#ifndef DIGEST_H
#define DIGEST_H
#include <flag.h>
#include <ft_printf.h>
#include <stdint.h>
#include <unistd.h>
#include <utils.h>

#define byte uint8_t

#define DIGESTSIZE 16
#define DIGESTSIZESHA 64
#define BLOCKSIZE 64
#define HASHSIZE 32
#define BUF_SIZE 512

typedef unsigned int uint32_t;

typedef struct s_func {
  void (*Print)();
  void (*Write)(byte *f);
  uint32_t *(*Get_Init)();
} t_func;

typedef struct s_algo {
  char *name;
  t_func *func;
  uint8_t m_size;

  struct s_algo *next;
} t_algo;

typedef struct s_digest {
  uint32_t m[BLOCKSIZE];
  byte digest_hash[BLOCKSIZE];
  int nx;
  uint init_size;
  unsigned long long lenbits;
  uint64_t len;
  byte hash[HASHSIZE];

  t_algo *algo;
  t_algo *algo_run;

  // INTERFACE
  void (*Reset)();
  void (*AddAlgo)(char *name, t_func *f, uint8_t m_size);
  void (*Run)(t_flag *flag);
  void (*Free)();
} t_digest;

t_digest *NewDigest();
t_digest *Init_digest();
// add a new algo to the list t_algo
t_digest *Get_digest(t_digest *d);
void Display_hash(FlagType flag, char *NameHash, void (*Print)(), int is_file,
                  char *input);

#endif
