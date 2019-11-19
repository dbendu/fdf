NAME = fdf

CC = clang

FLAGS = -Wall -Wextra -Werror

FLAGS2 = -lmlx -lXext -lX11 -L minilibx/ -I minilibx/ -I libft/includes/ -lm

GFLAGS = -g -Wall -Wextra -Werror

SRC = main.c input.c draw_line.c

LIBFT_DIR = libft
LIBS = libft/libft.a

OBJS = $(SRC:.c=.o)

HEADER = fdf.h

all: $(NAME)

g:
	@$(CC) $(SRC) $(GFLAGS) $(FLAGS2) libft/glibft.a -o fdf

$(LIBS):
	make -C $(LIBFT_DIR)

$(NAME): $(SRC) $(LIBS)
	@$(CC) $(SRC) $(FLAGS) $(FLAGS2) $(LIBS) -o fdf

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all
