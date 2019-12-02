NAME = fdf

FLAGS = -Wall -Wextra -Werror -lm

MLXFLAGS_LINUX = -lmlx -lXext -lX11 -L minilibx/ -I minilibx/
MLXFLAGS_MACOS = -lmlx -L minilibx/ -I minilibx/ -framework OpenGL -framework AppKit

SRC = main.c	draw_line.c		input.c		print_map.c

LIBFT = libft/libft.a

OBJS = $(SRC:.c=.o)

HEADER = fdf.h

SYSTEM =	$(shell uname)

MACOS =		Darwin
LINUX =		Ubuntu

all: $(NAME)

$(NAME):
all:
	@make -C libft
ifeq ($(SYSTEM), $(MACOS))
	@rm -rf minilibx_linux
	@-mv -f minilibx_macos minilibx
	@gcc $(SRC) $(FLAGS) $(MLXFLAGS_MACOS) $(LIBFT) -o fdf
else ifeq ($(SYSTEM), $(LINUX))
	@rm -rf minilibx_macos
	@-mv -f minilibx_linux minilibx &> /dev/null
	@gcc $(SRC) $(FLAGS) $(MLXFLAGS_LINUX) $(LIBFT) -o fdf
endif

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

c: clean

f: fclean

g:
	@make g -C libft
ifeq ($(SYSTEM), $(MACOS))
	@rm -rf minilibx_linux
	@-mv -f minilibx_macos minilibx
	@gcc $(SRC) -g $(FLAGS) $(MLXFLAGS_MACOS) $(LIBFT) -o fdf
else ifeq ($(SYSTEM), $(LINUX))
	@rm -rf minilibx_macos
	@-mv -f minilibx_linux minilibx &> /dev/null
	@gcc $(SRC) -g $(FLAGS) $(MLXFLAGS_LINUX) $(LIBFT) -o fdf
endif