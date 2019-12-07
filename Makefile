NAME = fdf

FLAGS = -Wall -Wextra -Werror -I./libft/includes

MLXFLAGS_LINUX = -L minilibx/minilibx_linux -I minilibx/minilibx_linux	-lmlx -lXext -lX11
MLXFLAGS_MACOS = -L minilibx/minilibx_macos -I minilibx/minilibx_macos 	-lmlx -framework OpenGL -framework AppKit


SRC =	main.c			draw_line.c			input.c		draw_map.c		\
		keyboard.c		map_actions.c		mouse.c		threads.c

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

SYSTEM =	$(shell uname)

MACOS =		Darwin
LINUX =		Linux

HEADER =	fdf.h

%.o: %.c $(HEADER)
	gcc $(FLAGS) $(SRC) -c

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
ifeq ($(SYSTEM), $(MACOS))
	@make -C minilibx/minilibx_macos
	@gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLXFLAGS_MACOS)
else ifeq ($(SYSTEM), $(LINUX))
	@gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLXFLAGS_LINUX) -pthread -lm
endif

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

c: clean

f: fclean

g:
	@make g -C libft
ifeq ($(SYSTEM), $(MACOS))
	@make -C minilibx/minilibx_macos
	@gcc -g $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLXFLAGS_MACOS)
else ifeq ($(SYSTEM), $(LINUX))
	@gcc -g $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLXFLAGS_LINUX) -pthread -lm
endif

#---------------------------------------------------------------#

#NAME = fillit
#
#CC = gcc
#
#CFLAGS = -Wall -Wextra -Werror -g
#
#PATH_LIBFT = libft
#
#SRC = main.c fillit.c validation.c writer.c
#
#OBJ = $(patsubst %.c,%.o,$(SRC))
#
#all: $(NAME)
#
#$(NAME): $(PATH_LIBFT)/libft.a $(OBJ)
#
#$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(PATH_LIBFT) -lft
#
#$(PATH_LIBFT)/libft.a:
#
#make -C $(PATH_LIBFT)
#
#%.o: %.c fillit.h
#
#$(CC) $(CFLAGS) -c $< -I $(PATH_LIBFT)
#
#clean:
#
#rm -f $(OBJ)
#
#make -C $(PATH_LIBFT) clean
#
#fclean: clean
#
#rm -f $(NAME)
#
#make -C $(PATH_LIBFT) fclean
#
#re: fclean all
#
#.PHONY: all clean fclean re
