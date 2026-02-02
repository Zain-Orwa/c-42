NAME    = ft_cat
GCC     = gcc
CFLAGS  = -Wall -Werror -Wextra
SRCS    = ft_cat.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(GCC) $(CFLAGS) -c $^ -o $@


$(NAME): $(OBJS)
	$(GCC) $(CFLAGS) -o $@ $(OBJS)

clean: 
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

