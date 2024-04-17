#include "../includes/utils.h"

int ft_strlen(const char *str) {
  int len = 0;
  while (str[len])
    len++;
  return len;
}

void *ft_memcpy(void *dst, const void *src, size_t n) {
  unsigned char *pdst;
  unsigned char *psrc;

  pdst = (unsigned char *)dst;
  psrc = (unsigned char *)src;
  while (n > 0) {
    *pdst++ = *psrc++;
    n--;
  }
  return (dst);
}

int ft_tolower(int c) {
  if (c >= 'A' && c <= 'Z')
    return c + 32;
  return c;
}

char *ft_strchr(const char *str, int c) {
  size_t i;

  i = 0;
  while (str[i]) {
    if (str[i] == c)
      return ((char *)str + i);
    i++;
  }
  if (str[i] == c)
    return ((char *)str + i);
  return (NULL);
}

void ft_bzero(void *s, size_t n) {
  unsigned char *ps;

  ps = (unsigned char *)s;
  while (n > 0) {
    *ps++ = '\0';
    n--;
  }
}

int ft_strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2 && *s1 == *s2) {
    s1++;
    s2++;
  }
  return (unsigned char)*s1 - (unsigned char)*s2;
}

int OpenFile(char *filename) {
  int fd;
  printf("OpenFile %s\n", filename);
  if ((fd = open(filename, O_RDONLY)) == -1) {
    return -1;
  }
  return fd;
}

char *ft_strdup(const char *s) {
  char *str;
  size_t len;
  len = ft_strlen(s);
  str = (char *)malloc(len + 1);
  if (str == NULL)
    return NULL;
  ft_memcpy(str, s, len);
  str[len] = '\0';
  return str;
}
