# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romlambe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:52:08 by romlambe          #+#    #+#              #
#    Updated: 2024/09/11 15:54:03 by romlambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
AUTHOR = romlambe

CC = gcc
CFLAGS = -Wall -Wextra -g -I./MLX42/include -I/opt/homebrew/Cellar/sdl2/2.30.7/include/SDL2 -I/opt/homebrew/Cellar/glfw/3.3.8/include
LDFLAGS = -L./MLX42/build -lmlx42 -L/opt/homebrew/Cellar/sdl2/2.30.7/lib -lSDL2 -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw

SRC := init_game.c

OBJ = $(SRC:.c=.o)

GREEN = \033[0;32m
NC = \033[0m

all: intro $(NAME)

intro:
	@echo "\n==================================="
	@echo "Compiling:	$(NAME)"
	@echo "Author:		$(AUTHOR)"
	@echo "==================================="

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "\n$(GREEN)Cub3D is created.$(NC)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(GREEN)Cub3D: Cleaning object files..."
	@rm -rf $(OBJ)

fclean: clean
	@echo "$(GREEN)Cub3D: Cleaning all build files..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
