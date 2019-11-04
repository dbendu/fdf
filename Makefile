NAME = fdf

CC = clang

FLAGS = -Wall -Wextra -Werror -g

FLAGS2 = -lmlx -lXext -lX11 -L minilibx/ -I minilibx/ -lm

SRC = main.c input.c draw_line.c #mlxkeys.c makemap.c draweverything.c draweverything2.c draweverything3.c getinfo.c

LIBFT_DIR = libft
LIBS = libft/libft.a

OBJS = $(SRC:.c=.o)

HEADER = fdf.h

all: $(NAME)

$(LIBS):
	make -C $(LIBFT_DIR)

$(NAME): $(SRC) $(LIBS)
	$(CC) $(SRC) $(FLAGS) $(FLAGS2) $(LIBS) -o fdf

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
