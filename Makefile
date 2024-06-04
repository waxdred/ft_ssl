
################################################################################
##                               Code color                                   ##
################################################################################

COLOR_NORM		=	\033[0m
COLOR_RED			=	\033[31m
COLOR_PURPLE	=	\033[35m

################################################################################
##                               SRCS                                         ##
################################################################################

SRCS_DIR = srcs
SRCS = digest/digest.c \
       digest/display.c \
       error.c \
       main.c \
       md5/algo.c \
       md5/md5.c \
       md5/table.c \
       parse.c \
       sha256/algo.c \
       sha256/math.c \
       sha256/sha256.c \
       sha256/table.c \
       utils/ft_printf.c \
       utils/readline.c \
       utils/utils.c
OBJS_DIR = build
OBJS = $(addprefix $(OBJS_DIR)/,$(subst $(SRCS_DIR),,$(SRCS:.c=.o)))

NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP -Iincludes
RM = rm -rf

# Set the number of object files 
NUM_OBJS = $(words $(OBJS))

################################################################################
##                       Compilation Environnement                            ##
################################################################################

# Define a function to print the progress bar 
define print_progress
	$(eval i = $(shell expr $(i) + 1))
	$(eval PERCENT = $(shell expr $(i) '*' 100 '/' $(NUM_OBJS)))
	@if [ $(i) -eq 1 ]; then \
        printf "$(COLOR_PURPLE)Starting compilation...\n$(COLOR_NORM)"; \
  fi
	@printf "\r\033[K\t$(COLOR_PURPLE)[$(PERCENT)%%]\t--> $(COLOR_NORM)$<\$(COLOR_NORM)"
endef

# Compilation rule for object files
$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call print_progress)
	@$(CC) $(CFLAGS) -c $< -o $@

# Include the dependency files
-include $(OBJ:.o=.d)

# Default target
all: $(NAME)

# Link the final executable
$(NAME): $(OBJS)
	@printf "\n[✅]\tCompilation of $(COLOR_PURPLE)$(NAME)\$(COLOR_NORM)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

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
