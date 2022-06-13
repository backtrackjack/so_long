# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 13:50:37 by jsellars          #+#    #+#              #
#    Updated: 2022/06/13 13:05:53 by jsellars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
UNAME := $(shell uname)
SOURCE_FILES = so_long.c get_next_line.c get_next_line_utils.c my_mlx.c utils.c init.c display.c hooks.c
SOURCES = $(addprefix srcs/, $(SOURCE_FILES))
OBJECTS = $(SOURCES:.c=.o)
INCLUDES = inc
CC = gcc
CFLAGS = -g -I/usr/include -Wall -Werror -Wextra
all: $(NAME)

$(NAME): $(OBJECTS)
ifeq ($(UNAME), Darwin)
	$(CC)  $? -I$(INCLUDES) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
endif
ifeq ($(UNAME), Linux)
	$(CC)  $? -I$(INCLUDES) -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -o $(NAME)
endif

%.o: %.c mlx
ifeq ($(UNAME), Darwin)
	$(CC) -c -I$(INCLUDES) $(CFLAGS) -Imlx $< -o $@
endif
ifeq ($(UNAME), Linux)
	$(CC) -c -Lmlx_linux -lmlx -L/usr/lib -O3 -lXext -lX11 -lm -I$(INCLUDES) $(CFLAGS) $< -o $@
endif

mlx:	
ifeq ($(UNAME), Darwin)
	make -C mlx
endif
ifeq ($(UNAME), Linux)
	make -C mlx_linux
endif


clean:
	rm -f $(OBJECTS)
	make -C mlx clean

fclean: clean
	rm -rf so_long.dSYM so_long valgrind-out.txt

re: fclean all

.PHONY: all mlx clean fclean re libft
