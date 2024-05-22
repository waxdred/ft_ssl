#include "ft_printf.h"

void ft_dputchar(int fd, char c) { write(fd, &c, 1); }

void ft_dputstr(int fd, char *str) {
  if (!str)
    return;
  while (*str)
    ft_dputchar(fd, *str++);
}

// check string has %02x
int ft_checkX(const char *s1) {
  int i = 0;
  int len = ft_strlen(s1);
  while (s1[i]) {
    if (i + 2 >= len)
      break;
    if (s1[i] == '0' && s1[i + 1] == '2' && s1[i + 2] == 'x')
      return (1);
  }
  return (0);
}

// Presion to handle %02x
void ft_putnbr_base(int fd, int nbr, char *base, int count) {
  unsigned int lnbr;
  unsigned int size;

  lnbr = nbr;
  size = ft_strlen(base);
  if (size <= 1)
    return;
  if (nbr < 0) {
    ft_dputchar(fd, '-');
    lnbr *= -1;
  }
  if (lnbr / size) {
    ft_putnbr_base(fd, lnbr / size, base, count + 1);
    ft_dputchar(fd, base[lnbr % size]);
  } else {
    if (count == 0)
      ft_dputchar(fd, '0');
    ft_dputchar(fd, base[lnbr % size]);
  }
}

// format to handle %s %02x
void ft_read_args(int fd, va_list *args, const char *str, int *idx) {
  str++;
  if (!str)
    return;
  else if (*str == 'c')
    ft_dputchar(fd, va_arg(*args, int));
  else if (*str == 's')
    ft_dputstr(fd, va_arg(*args, char *));
  else if (ft_checkX(str)) {
    ft_putnbr_base(fd, va_arg(*args, int), "0123456789abcdef", 0);
    *idx += 2;
  } else if (*str == '%')
    ft_dputchar(fd, '%');
  *idx += 1;
}

void ft_dprintf(int fd, const char *format, ...) {
  va_list args;
  int i = 0;
  if (!format)
    return;
  va_start(args, format);
  while (format[i]) {
    if (format[i] == '%')
      ft_read_args(fd, &args, &format[i], &i);
    else
      ft_dputchar(fd, format[i]);
    i++;
  }
  va_end(args);
}
