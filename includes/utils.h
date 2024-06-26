#ifndef UTILS_H
#define UTILS_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(const char *s);
void *ft_memcpy(void *dst, const void *src, size_t n);
int ft_tolower(int c);
char *ft_strchr(const char *str, int c);
void ft_bzero(void *s, size_t n);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strdup(const char *s);
int OpenFile(char *filename);
char *ReadFile(int fd);
char *ft_strjoin(char const *s1, char const *s2);
char *ReadStdin();
char *ft_trimLastWhiteSpace(char *str);
void ft_readline(char *file, void (*Write)(unsigned char *f));
void *ft_memset(void *b, int c, size_t len);

#endif
