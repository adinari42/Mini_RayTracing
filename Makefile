# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adinari <adinari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 21:40:31 by adinari           #+#    #+#              #
#    Updated: 2023/03/26 07:18:11 by adinari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MiniRT

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

OBJECTS = $(FILES:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -g -O1

all: $(NAME)
	
%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

LIBS =	src/libft/libft.a
$(NAME): $(OBJECTS)
	make -C src/libft
	export LD_LIBRARY_PATH=/usr/lib/swift/
	$(CC)  $(OBJECTS) $(LIBS) -o $(NAME) 
clean:
	rm -rf $(OBJECTS)
	make clean -C src/libft
	
fclean: clean
	rm -rf $(NAME) *.o
	make fclean -C src/libft

re: fclean all