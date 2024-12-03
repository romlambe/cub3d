# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:52:08 by romlambe          #+#    #+#              #
#    Updated: 2024/11/19 05:47:27 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = 2_complet.c # parsing.c initialization.c raycasting.c render.c movement_ply.c
LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx.a
GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

LIBRARY = -L/usr/X11R6/lib -lX11 -lXext
OBJ = $(addprefix compile/, $(SRC:.c=.o))
GNL_OBJ = $(addprefix compile/, $(GNL:.c=.o))

HEADER = cub3d.h

# Animation et couleur
RESET = \033[0m
GREEN = \033[32m
BLUE = \033[34m

all: banner $(NAME)

banner:
	@echo "$(BLUE)Compiling cub3d by tgerardi and a little bit of romlambe...$(RESET)"

$(LIBFT):
	@$(MAKE) -C libft > /dev/null

$(MINILIBX):
	@$(MAKE) -C minilibx-linux > /dev/null || true

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX) $(GNL_OBJ)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) $(LIBRARY) $(LIBFT) $(GNL_OBJ) -o $(NAME) -lm

compile/%.o: %.c $(HEADER) | compile_dirs
	@echo -n "Compiling $< ... "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Done$(RESET)"

compile_dirs:
	@mkdir -p compile compile/gnl

clean:
	@rm -rf compile
	@$(MAKE) clean -C libft > /dev/null
	@$(MAKE) clean -C minilibx-linux > /dev/null || true
	@echo "$(BLUE)Cleaned up!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C libft > /dev/null
	@echo "$(BLUE)Full cleanup done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re banner compile_dirs