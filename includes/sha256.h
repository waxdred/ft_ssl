#ifndef SHA256_H
#define SHA256_H

#include <digest.h>

#define NOARG 0
#define WITHARG 1
#define BLOCKSIZE 64
#define HASHSIZE 32

// The blocksize of MD5 in bytes.
#define SHA256_INIT 8
#define SHA256_INIT0 0x6a09e667
#define SHA256_INIT1 0xbb67ae85
#define SHA256_INIT2 0x3c6ef372
#define SHA256_INIT3 0xa54ff53a
#define SHA256_INIT4 0x510e527f
#define SHA256_INIT5 0x9b05688c
#define SHA256_INIT6 0x1f83d9ab
#define SHA256_INIT7 0x5be0cd19

#define byte uint8_t
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

// add a new algo to the list t_algo
t_func ft_NewSHA256();

// interface for digest
void PrintSum();
void Write_sha256(byte *p);
void PrintSumSha256();

// Table of functions
uint32_t *get_sha256_Init();
uint32_t *get_sha256_K();
uint32_t *get_sha256_R();

// math
uint32_t ROTLEFT(uint32_t a, uint32_t b);
uint32_t ROTRIGHT(uint32_t a, uint32_t b);
uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);
uint32_t CH(uint32_t x, uint32_t y, uint32_t z);
uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z);
uint32_t EP0(uint32_t x);
uint32_t EP1(uint32_t x);
#endif
