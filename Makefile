# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adinari <adinari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 21:40:31 by adinari           #+#    #+#              #
#    Updated: 2023/01/09 01:21:10 by adinari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MiniRT

FILES = src/main.c\
		src/gnl/get_next_line.c\
		src/gnl/get_next_line_utils.c\
		src/parse_utils.c\
		src/utils.c

OBJECTS = $(FILES:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)
	
%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

LIBS = codam_MLX/libmlx42.a -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"\
		src/libft/libft.a
$(NAME): $(OBJECTS)
	make -C src/libft
	export LD_LIBRARY_PATH=/usr/lib/swift/
	$(CC) $(OBJECTS) $(LIBS)  -o $(NAME)

clean:
	rm -rf $(OBJECTS)
	make clean -C src/libft
	
fclean: clean
	rm -rf $(NAME) *.o
#make fclean -C src/libft

re: fclean all