#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdarg.h>
#include <unistd.h>
#include <utils.h>

void ft_dprintf(int fd, const char *format, ...);

#endif
