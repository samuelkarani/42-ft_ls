CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = ft_ls

SRC = main.c ft_ls*.c long_format*.c files*.c utils*.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft
	@make -C libft/ft_printf
	@$(CC) $(CFLAGS) $(SRC) -Llibft/ft_printf -lftprintf -Llibft -lft -o $@

clean:
	@make clean -C libft
	@make clean -C libft/ft_printf
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@make fclean -C libft/ft_printf
	@rm -f $(NAME)

norm:
	norminette $(SRC) ft_ls.h

norm-all: norm
	norminette libft/{*.c,*.h} libft/ft_printf/{*.c,*.h}

re: fclean all

.PHONY: all clean fclean re norm norm-all