# Library name
NAME		= libft.a

# Tools
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
AR			= /usr/bin/ar
RANLIB		= /usr/bin/ranlib

# Directories
SRCS_DIR	= srcs
INCL_DIR	= includes

# Source files (explicit list, no wildcards)
SRCS		= $(SRCS_DIR)/ft_putchar.c \
			  $(SRCS_DIR)/ft_swap.c \
			  $(SRCS_DIR)/ft_putstr.c \
			  $(SRCS_DIR)/ft_strlen.c \
			  $(SRCS_DIR)/ft_strcmp.c

# Object files (same directory as their .c)
OBJS		= $(SRCS:.c=.o)

# ================== Rules ================== #

# Default rule: 'make' == 'make all'
all: $(NAME)

# Build static library from object files
$(NAME): $(OBJS)
	$(AR) rcs $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

# Compile any .c into matching .o (in same dir)
.c.o:
	$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $@

# Remove only object files
clean:
	$(RM) $(OBJS)

# Remove objects and the library
fclean: clean
	$(RM) $(NAME)

# Rebuild everything from scratch
re: fclean all

# These targets are not real files
.PHONY: all clean fclean re
