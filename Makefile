# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romlambe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:52:08 by romlambe          #+#    #+#              #
#    Updated: 2024/09/12 17:15:19 by romlambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
AUTHOR = romlambe

CC = gcc


SRC = parsing.c
LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx.a

LIBRARY = -L/usr/X11R6/lib -lX11 -lXext
OBJ = $(SRC:.c=.o)

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
	make -C minilibx

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBRARY) $(LIBFT) -o $(NAME) -lm
	echo "\n$(GREEN)Cub3D is created.$(NC)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	echo "$(GREEN)Cub3D: Cleaning object files..."
	rm -rf $(OBJ)

fclean: clean
	echo "$(GREEN)Cub3D: Cleaning all build files..."
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
