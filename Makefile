# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 16:13:26 by lshellie          #+#    #+#              #
#    Updated: 2019/11/29 21:13:33 by dbendu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c draw_line.c input.c

OBJ = main.o draw_line.o input.o

NAME = fdf

LIB = libft.a

MLX = mlx

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(MLX)
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) -lm -L. libft/$(LIB) -L ./mlx -lmlx -framework OpenGL -framework AppKit
$(LIB):
	make -C ./libft
$(MLX):
	make -C ./mlx
%.o: %.c
	gcc -c $<
clean:
	make clean -C ./libft
	rm -rf $(OBJ)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
make re: fclean all