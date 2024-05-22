#include "utils.h"
#include <stdio.h>

int ft_strlen(const char *str) {
  int len = 0;
  if (str == NULL)
    return 0;
  while (str[len])
    len++;
  return len;
}

char *ft_trimLastWhiteSpace(char *str) {
  int len = ft_strlen(str);
  while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' ||
                     str[len - 1] == '\n')) {
    str[len - 1] = 0;
    len--;
  }
  return str;
}

void *ft_memset(void *b, int c, size_t len) {
  unsigned char *pb;
  size_t i;

  pb = (unsigned char *)b;
  i = 0;
  while (i < len)
    pb[i++] = (unsigned char)c;
  return (b);
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

char ft_toupper(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 32;
  }
  return c;
}

char *ft_strtoupper(char *str) {
  int i = 0;
  while (str[i]) {
    str[i] = ft_toupper(str[i]);
    i++;
  }
  return str;
}

int ft_strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2 && *s1 == *s2) {
    s1++;
    s2++;
  }
  return (unsigned char)*s1 - (unsigned char)*s2;
}

int CheckStdin() {
  int ret = 0;
  char buffer[1];
  int flags = fcntl(STDIN_FILENO, F_GETFL);
  fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

  int bytes_read = read(STDIN_FILENO, buffer, 1);
  if (bytes_read > 0) {
    ret = 1;
  }

  fcntl(STDIN_FILENO, F_SETFL, flags); // restore original flags
  return ret;
}

int OpenFile(const char *filename) {
  int fd;
  char *tmp;

  fd = open(filename, O_RDONLY);
  tmp = NULL;
  if (fd == -1)
    return (-1);
  if (read(fd, tmp, 0) == -1) {
    return (-1);
  }
  return (fd);
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
