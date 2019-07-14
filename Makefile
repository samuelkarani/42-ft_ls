CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = ft_ls

SRC = main.c ft_ls.c ft_ls2.c long_format.c long_format2.c \
	long_format3.c files.c files2.c utils.c utils2.c utils3.c utils4.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	make -C libft
	cp libft/libft.a .
	make -C libft/ft_printf
	cp libft/ft_printf/libftprintf.a .
	$(CC) $(CFLAGS) libft.a libftprintf.a $^ -o $@

clean:
	@make clean -C libft
	@make clean -C libft/ft_printf
	@rm -f $(OBJ)

fclean:
	@make fclean -C libft
	@make fclean -C libft/ft_printf
	@rm -f $(OBJ)
	@rm -f libft.a libftprintf.a
	@rm -f $(NAME)

norm:
	norminette $(SRC) ft_ls.h

norm-all: norm
	norminette libft/{*.c,*.h} libft/ft_printf/{*.c,*.h}

re: fclean all

.PHONY: all clean fclean re norm norm-all