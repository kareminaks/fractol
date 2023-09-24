DEFAULT_GOAL := all
NAME = fractol
CFLAGS = -Wall -Werror -Wextra -g
SRC = main.c fractals.c  math.c draw.c events.c math2.c
OBJ = $(SRC:.c=.o)
HEADER = $(NAME).h
INCLUDES += -Ilibft -Iminilibx

all: $(NAME)

libft/libft.a:
	make -C libft

minilibx/libmlx.a:
	make -C minilibx

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

$(NAME): $(OBJ) $(HEADER) libft/libft.a ./minilibx/libmlx.a
	$(CC) $(OBJ) ./libft/libft.a ./minilibx/libmlx.a -lXext -lX11 -lm -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C ./minilibx clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean


re: fclean all