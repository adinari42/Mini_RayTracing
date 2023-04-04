# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 21:40:31 by adinari           #+#    #+#              #
#    Updated: 2023/03/31 22:07:57 by miahmadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
MLX = ./mlx

FILES = src/main.c\
		src/gnl/get_next_line.c\
		src/gnl/get_next_line_utils.c\
		src/parse_utils.c\
		src/utils.c\
		src/parse.c\
		src/intersect.c\
		src/vector_op.c\
		src/matrix.c\
		src/lighting.c\
		src/intersect_utils.c\
		src/intersect_utils_2.c\
		src/intersect_utils_3.c\
		src/lighting_utils.c\
		src/matrix_utils.c\
		src/matrix_utils_2.c\
		src/parse_utils_2.c\
		src/parse_utils_3.c\
		src/parse_utils_4.c\
		src/vector_op_2.c\
		src/trace_ray.c\
		src/main_utils.c\
		src/utils_2.c\
		src/utils_3.c\
		src/utils_4.c\
		src/cyl_parse_utils.c\
		src/main_utils_2.c\
		src/main_utils_3.c\

OBJECTS = $(FILES:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -g -O1

all: $(NAME)
	
%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

LIBS =	src/libft/libft.a
$(NAME): $(OBJECTS) mlx
	make -C src/libft
	export LD_LIBRARY_PATH=/usr/lib/swift/
	$(CC)  $(OBJECTS) $(LIBS)  -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) 
clean:
	rm -rf $(OBJECTS)
	make clean -C src/libft
	@cd $(MLX) && $(MAKE) clean

mlx: 
	@make -C $(MLX)
	@cp $(MLX)/libmlx.dylib .
	@mv libmlx.dylib libmlx.dylib
	
fclean: clean
	rm -rf $(NAME) *.o
	make fclean -C src/libft

re: fclean all