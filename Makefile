# NAME = fdf

# FLAGS = -Wall -Wextra -Werror -lm

# MLXFLAGS_LINUX = -lmlx -lXext -lX11							-L minilibx/minilibx_linux -I minilibx/minilibx_linux
# MLXFLAGS_MACOS = -lmlx -framework OpenGL -framework AppKit	-L minilibx/minilibx_macos -I minilibx/minilibx_macos

# SRC = main.c	draw_line.c		input.c		print_map.c		$(LIBFT)

# LIBFT = libft/libft.a

# OBJS = $(SRC:.c=.o)

# HEADER = fdf.h

# SYSTEM =	$(shell uname)

# MACOS =		Darwin
# LINUX =		Linux

# all: $(NAME)

# $(NAME):
# all:
# 	@make -C libft
# ifeq ($(SYSTEM), $(MACOS))
# 	@gcc $(FLAGS) $(MLXFLAGS_MACOS) $(SRC) $(HEADER) -o fdf
# else ifeq ($(SYSTEM), $(LINUX))
# 	@gcc $(FLAGS) $(MLXFLAGS_LINUX) $(SRC) $(HEADER) -o fdf
# endif

# clean:
# 	@make clean -C libft
# 	@rm -rf $(OBJS)

# fclean: clean
# 	@make fclean -C libft
# 	@rm -f $(NAME)

# re: fclean all

# c: clean

# f: fclean

# g:
# 	@make g -C libft
# ifeq ($(SYSTEM), $(MACOS))
# 	@rm -rf minilibx_linux
# 	@-mv -f minilibx_macos minilibx
# 	@gcc $(SRC) -g $(FLAGS) $(MLXFLAGS_MACOS) $(HEADER) -o fdf
# else ifeq ($(SYSTEM), $(LINUX))
# 	@rm -rf minilibx_macos
# 	@-mv -f minilibx_linux minilibx &> /dev/null
# 	@gcc $(SRC) -g $(FLAGS) $(MLXFLAGS_LINUX) $(HEADER) -o fdf
# endif

NAME = fdf

FLAGS = -Wall -Wextra -Werror -lm

MLXFLAGS_LINUX = -lmlx -lXext -lX11 -L minilibx/minilibx_linux -I minilibx/minilibx_linux -Ilibft/includes
MLXFLAGS_MACOS = -lmlx -L minilibx/minilibx_macos -I minilibx/minilibx_macos -framework OpenGL -framework AppKit -Ilibft/includes


SRC = main.c	draw_line.c		input.c		print_map.c		keyboard.c		map_actions.c		mouse.c

LIBFT = libft/libft.a

OBJS = $(SRC:.c=.o)

HEADER = fdf.h

SYSTEM =	$(shell uname)

MACOS =		Darwin
LINUX =		Ubuntu

all: $(NAME)

$(NAME): $(SRC)
	@make -C libft
ifeq ($(SYSTEM), $(MACOS))
	@gcc $(SRC) $(FLAGS) $(MLXFLAGS_MACOS) $(LIBFT) -o $(NAME)
else ifeq ($(SYSTEM), $(LINUX))
	@gcc $(SRC) $(FLAGS) $(MLXFLAGS_LINUX) $(LIBFT) -o $(NAME)
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
	@gcc $(SRC) -g $(FLAGS) $(MLXFLAGS_MACOS) $(LIBFT) -o $(NAME)
else ifeq ($(SYSTEM), $(LINUX))
	@gcc $(SRC) -g $(FLAGS) $(MLXFLAGS_LINUX) $(LIBFT) -o $(NAME)
endif