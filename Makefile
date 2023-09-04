DEFAULT_GOAL := all
NAME = fractol
CFLAGS = -Wall -Werror -Wextra
SRC = main.c fractals.c 
OBJ = $(SRC:.c=.o)
HEADER = $(NAME).h
INCLUDES += -Ilibft -Iminilibx

all: $(NAME)

libft/libft.a:
	make -C libft

minilibx/libmlx.a:
	make -C mlx_linux

%.o: %.c $(HEADER)
	$(CC) -Wall -Wextra -Werror $(INCLUDES) -O3 -c $< -o $@

$(NAME): $(OBJ) $(HEADER) libft/libft.a ./minilibx/libmlx.a
	$(CC) $(OBJ) ./libft/libft.a ./minilibx/libmlx.a -lXext -lX11 -lm -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C ./mlx_linux clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean


re: fclean all