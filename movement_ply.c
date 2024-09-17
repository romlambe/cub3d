/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_ply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:19:51 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/17 15:11:05 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_reles(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_Q)
		mlx->player->l_r = 0;
	else if (keycode == KEY_D)
		mlx->player->l_r = 0;
	else if (keycode == KEY_Z)
		mlx->player->u_d = 0;
	else if (keycode == KEY_S)
		mlx->player->u_d = 0;
	else if (keycode == LEFT)
		mlx->player->rot = 0;
	else if (keycode == RIGHT)
		mlx->player->rot = 0;
	return (0);
}

int	keypress(int keycode, void *ml)
{
	t_mlx *mlx = ml;

	if (keycode == KEY_Q)
		mlx->player->l_r = -1;
	else if (keycode == KEY_D)
		mlx->player->l_r = 1;
	else if (keycode == KEY_Z)
		mlx->player->u_d = 1;
	else if (keycode == KEY_S)
		mlx->player->u_d = -1;
	else if (keycode == LEFT)
		mlx->player->rot = -1;
	else if (keycode == RIGHT)
		mlx->player->rot = 1;
	// ft_reles(keycode, mlx);
	return (0);
}

void	rotation_player(t_mlx *mlx, int i)
{
	// mlx->player->rot = (double)0.05;
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

void	move_player(t_mlx *mlx, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->player->x_ply + move_x); // get the new x position
	new_y = roundf(mlx->player->y_ply + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (mlx->data->map[map_grid_y][map_grid_x] != '1' && \
	(mlx->data->map[map_grid_y][mlx->player->x_ply / TILE_SIZE] != '1' && \
	mlx->data->map[mlx->player->y_ply / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		mlx->player->x_ply = new_x; // move the player
		mlx->player->y_ply = new_y; // move the player
	}
}

void	hook(t_mlx *mlx, double move_x, double move_y)	// hook the player
{
	if (mlx->player->rot == 1) //rotate right
		rotation_player(mlx, 1);
	if (mlx->player->rot == -1) //rotate left
		rotation_player(mlx, 0);
	if (mlx->player->l_r == 1) //move right
	{
		move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->l_r == -1) //move left
	{
		move_x = sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->u_d == 1) //move up
	{
		move_x = cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = sin(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->u_d == -1) //move down
	{
		move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
	}
	move_player(mlx, move_x, move_y); // move the player
}
