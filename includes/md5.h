#ifndef MD5_H
#define MD5_H

#include <digest.h>

#define NOARG 0
#define WITHARG 1
#define BLOCKSIZE 64
#define HASHSIZE 32

// The blocksize of MD5 in bytes.
#define MD5_INIT 4
#define MD5_INIT0 0x67452301
#define MD5_INIT1 0xEFCDAB89
#define MD5_INIT2 0x98BADCFE
#define MD5_INIT3 0x10325476

#define byte uint8_t
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

// add a new algo to the list t_algo
t_func ft_NewMD5();

void PrintSum();
void Write_md5(byte *p);
void PrintSumMd5();

// Table of functions
uint32_t *get_md5_Init();
uint32_t *get_md5_K();
uint32_t *get_md5_R();
#endif
