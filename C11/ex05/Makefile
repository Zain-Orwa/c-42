NAME    = do-op
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRCS    = op_main.c \
					do_op_ops.c \
					get_operator.c \
					utils.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c do_op.h
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

