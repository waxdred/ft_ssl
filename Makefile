
SRCS_DIR = srcs

SRCS = digest/digest.c \
       digest/display.c \
       error.c \
       main.c \
       md5/algo.c \
       md5/md5.c \
       md5/table.c \
       parse.c \
       utils/ft_printf.c \
       utils/readline.c \
       utils/utils.c

OBJS_DIR = build

OBJS = $(addprefix $(OBJS_DIR)/,$(subst $(SRCS_DIR),,$(SRCS:.c=.o)))

NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP -Iincludes
RM = rm -rf

# Compilation rule for object files
$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Include the dependency files
-include $(OBJ:.o=.d)

# Default target
all: $(NAME)

# Link the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Clean up object files and dependency files
clean:
	@$(RM) $(OBJS_DIR)
	@$(RM) $(DEPS_DIR)

# Clean up object files, dependency files, and the executable
fclean: clean
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
