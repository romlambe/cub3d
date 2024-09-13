# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romlambe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:52:08 by romlambe          #+#    #+#              #
#    Updated: 2024/09/13 13:14:40 by romlambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
AUTHOR = romlambe

CC = gcc


SRC = parsing.c initialization.c
LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx.a
GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

LIBRARY = -L/usr/X11R6/lib -lX11 -lXext
OBJ = $(SRC:.c=.o)
GNL_OBJ = $(GNL:.c=.o)

GREEN = \033[0;32m
NC = \033[0m

all: intro $(NAME)

intro:
	echo "\n==================================="
	echo "Compiling:	$(NAME)"
	echo "Author:		$(AUTHOR)"
	echo "==================================="

$(LIBFT):
	make -C libft

$(MINILIBX):
	make -C minilibx-linux

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) $(LIBRARY) $(LIBFT) $(GNL_OBJ) -o $(NAME) -lm
	echo "\n$(GREEN)Cub3D is created.$(NC)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	echo "$(GREEN)Cub3D: Cleaning object files..."
	rm -rf $(OBJ)
	rm -rf $(GNL_OBJ)
	make clean -C libft
	make clean -C minilibx-linux

fclean: clean
	echo "$(GREEN)Cub3D: Cleaning all build files..."
	rm -f $(NAME)
	make clean -C libft
	make clean -C minilibx

re: fclean all

.PHONY: all clean fclean re
