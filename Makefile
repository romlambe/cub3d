# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romlambe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:52:08 by romlambe          #+#    #+#              #
#    Updated: 2024/12/10 16:28:33 by romlambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = cub3d

# CC = gcc
# CFLAGS = -Wall -Wextra -Werror

# SRC = parsing/copy_map.c parsing/manage_map.c parsing/parsing_map.c parsing/utils_parsing.c \
# 	render/checker.c render/cub3d.c render/drawer.c render/fryer.c render/initialisation.c \
# 	render/manager.c render/mlx_utils.c render/movement.c render/render_ray.c  render/render.c\
# 	render/sprites_manager.c render/sprites.c render/texture.c render/utils.c
# MINILIBX = minilibx-linux/libmlx.a
# GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

# LIBRARY = -L/usr/X11R6/lib -lX11 -lXext
# OBJ = $(SRC:.c=.o)
# GNL_OBJ = $(GNL:.c=.o)

# HEADER = cub3d.h

# # Animation et couleur
# RESET = \033[0m
# GREEN = \033[32m
# BLUE = \033[34m

# all: banner $(NAME)

# banner:
# 	@echo "$(BLUE)Compiling cub3d by tgerardi and a little bit of romlambe...$(RESET)"

# $(LIBFT):
# 	@$(MAKE) -C libft > /dev/null

# $(MINILIBX):
# 	@$(MAKE) -C minilibx-linux > /dev/null || true

# $(NAME): $(OBJ) $(LIBFT) $(MINILIBX) $(GNL_OBJ)
# 	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
# 	@$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) $(LIBRARY) $(LIBFT) $(GNL_OBJ) -o $(NAME) -lm

# %.o: %.c $(HEADER)
# 	@echo -n "Compiling $< ... "
# 	@$(CC) $(CFLAGS) -c $< -o $@
# 	@echo "$(GREEN)Done$(RESET)"

# clean:
# 	@rm -rf compile
# 	@$(MAKE) clean -C libft > /dev/null
# 	@$(MAKE) clean -C minilibx-linux > /dev/null || true
# 	@echo "$(BLUE)Cleaned up!$(RESET)"

# fclean: clean
# 	@rm -f $(NAME)
# 	@$(MAKE) fclean -C libft > /dev/null
# 	@echo "$(BLUE)Full cleanup done!$(RESET)"

# re: fclean all

# .PHONY: all clean fclean re banner compile_dirs


# Nom du programme
NAME := cub3d

# Compilateur et flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -I.

# Animation et couleur
RESET = \033[0m
GREEN = \033[32m
BLUE = \033[34m

# Dossiers
SRC_DIR := render parsing gnl
LIBFT_DIR := libft
MLX_DIR := minilibx-linux
GNL := gnl/get_next_line.c gnl/get_next_line_utils.c

# Fichiers source
SRCS := parsing/copy_map.c parsing/manage_map.c parsing/parsing_map.c parsing/utils_parsing.c \
	render/checker.c render/cub3d.c render/drawer.c render/fryer.c render/initialisation.c \
	render/manager.c render/mlx_utils.c render/movement.c render/render_ray.c  render/render.c\
	render/sprites_manager.c render/sprites.c render/texture.c render/utils.c
OBJS := $(SRCS:.c=.o)
LIBRARY = -L/usr/X11R6/lib -lX11 -lXext

# Dépendances
LIBFT := $(LIBFT_DIR)/libft.a
MLX := $(MLX_DIR)/libmlx.a
GNL_OBJ := $(GNL:.c=.o)
# Règles
all: banner $(NAME)

banner:
	@echo "$(BLUE)Compiling cub3d by tgerardi and a little bit of romlambe...$(RESET)"

$(NAME): $(OBJS) $(LIBFT) $(MLX) $(GNL_OBJ)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(LIBRARY) -o $@ $^ -lm

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@ rm -rf $(OBJS) $(GNL_OBJ)
	@echo "$(BLUE)Cleaned up!$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(BLUE)Full cleaned up!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
