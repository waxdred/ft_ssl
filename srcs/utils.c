#include "../includes/utils.h"

int ft_strlen(const char *str) {
  int len = 0;
  if (str == NULL)
    return 0;
  while (str[len])
    len++;
  return len;
}

char *ReadStdin() {
  char buf[512];
  char *p = NULL;
  char *tmp = NULL;
  int fd = 0, ret = 0;
  fd_set readfds;
  int len = 0;
  struct timeval timeout;

  if ((fd = dup(STDIN_FILENO)) < 0)
    return NULL;

  while (1) {
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

int CheckStdin() {
  fd_set readfds;
  struct timeval timeout;

  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);
  ft_bzero(&timeout, sizeof(timeout));
  if (select(1, &readfds, NULL, NULL, &timeout))
    return 1;
  return 0;
}

char *ReadFile(int fd) {
  char buf[512];
  char *p = NULL;
  char *tmp = NULL;
  int ret;
  int len = 0;

  if (fd == STDIN_FILENO && !CheckStdin()) {
    return NULL;
  }
  // check EOF for handle stdin ctrl+d
  while ((ret = read(fd, buf, 512)) > 0) {
    buf[ret] = '\0';
    tmp = p;
    p = ft_strjoin(p, buf);
    if (tmp)
      free(tmp);
    len += ret;
    ft_bzero(buf, 512);
  }
  return p;
}

char *ft_joint(char *dest, char const *s2, size_t i, char *tmp) {
  size_t len;
  size_t j;

  len = ft_strlen(tmp);
  j = 0;
  while (j < len) {
    dest[i] = tmp[j];
    j++;
    i++;
  }
  if (tmp == s2)
    return (dest);
  return (ft_joint(dest, s2, i, (char *)s2));
}

void *ft_memset(void *b, int c, size_t l) {
  size_t i;
  unsigned char *r;

  i = 0;
  r = (unsigned char *)b;
  while (i < l) {
    r[i] = c;
    i++;
  }
  return (b);
}

void *ft_malloc(size_t size) {
  void *ret;

  if ((ret = malloc(size)))
    ft_memset(ret, '\0', size);
  return (ret);
}

char *ft_strjoin(char const *s1, char const *s2) {
  char *str;
  int l_s1;
  int l_s2;
  int i;

  i = 0;
  if (!s1 && !s2)
    return (NULL);
  if (s1 && !s2)
    return (ft_strdup((char *)s1));
  if (!s1 && s2)
    return (ft_strdup((char *)s2));
  l_s1 = ft_strlen(s1);
  l_s2 = ft_strlen(s2);
  str = NULL;
  if ((str = (char *)ft_malloc(sizeof(char) * ((l_s1 + l_s2) + 1))) == NULL)
    return (NULL);
  l_s1 = 0;
  while (s1[l_s1])
    str[i++] = s1[l_s1++];
  l_s2 = 0;
  while (s2[l_s2])
    str[i++] = s2[l_s2++];
  str[i] = '\0';
  return (str);
}
