
HEADERS = includes/ft_ssl.h \
          includes/flag.h    \
          includes/md5.h    \
          includes/digest.h    \
          includes/sha256.h    \
          includes/ft_printf.h    \
          includes/utils.h

SRCS_DIR = srcs/


SRCS = $(SRCS_DIR)error.c \
       $(SRCS_DIR)utils.c \
       $(SRCS_DIR)readline.c \
       $(SRCS_DIR)parse.c \
       $(SRCS_DIR)digest/digest.c \
       $(SRCS_DIR)digest/digest_md5.c \
       $(SRCS_DIR)digest/digest_sha256.c \
       $(SRCS_DIR)digest/tool.c \
       $(SRCS_DIR)sha256/sha256.c \
       $(SRCS_DIR)sha256/output.c \
       $(SRCS_DIR)sha256/table.c \
       $(SRCS_DIR)md5/input.c \
       $(SRCS_DIR)md5/md5.c  \
       $(SRCS_DIR)md5/output.c \
       $(SRCS_DIR)md5/table.c \
       $(SRCS_DIR)printf/ft_printf.c \
       $(SRCS_DIR)ft_ssl.c \
       $(SRCS_DIR)main.c
OBJS_DIR = objs

OBJS = $(addprefix $(OBJS_DIR)/,$(subst $(SRCS_DIR),,$(SRCS:.c=.o)))
NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
RM = rm -rf


$(OBJS_DIR)/%.o : $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all:	${NAME}

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@${RM} ${OBJS}

fclean:
	@${RM} ${OBJS} ${NAME}

re: fclean all
