/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_ply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:19:51 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/17 18:09:37 by anporced         ###   ########.fr       */
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

void    update_player_direction(t_player *player)
{
    player->dir_x = cos(player->angle);
    player->dir_y = sin(player->angle);
    player->plane_x = -player->dir_y * tan(player->fov_rd / 2);
    player->plane_y = player->dir_x * tan(player->fov_rd / 2);
}


void    rotation_player(t_mlx *mlx, int i)
{
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
    update_player_direction(mlx->player);
}



void    move_player(t_mlx *mlx, double move_x, double move_y)
{
    double  new_x;
    double  new_y;
    int     map_grid_x;
    int     map_grid_y;
    double  margin = 5.0; // Ajustez la marge selon vos besoins

    new_x = mlx->player->x_ply + move_x;
    new_y = mlx->player->y_ply + move_y;

    // Vérifier la collision pour la nouvelle position X
    map_grid_x = (int)((new_x + margin * (move_x > 0 ? 1 : -1)) / TILE_SIZE);
    map_grid_y = (int)(mlx->player->y_ply / TILE_SIZE);
    if (mlx->data->map[map_grid_y][map_grid_x] != '1')
        mlx->player->x_ply = new_x;

    // Vérifier la collision pour la nouvelle position Y
    map_grid_x = (int)(mlx->player->x_ply / TILE_SIZE);
    map_grid_y = (int)((new_y + margin * (move_y > 0 ? 1 : -1)) / TILE_SIZE);
    if (mlx->data->map[map_grid_y][map_grid_x] != '1')
        mlx->player->y_ply = new_y;
}


void    hook(t_mlx *mlx, double move_x, double move_y)
{
    if (mlx->player->rot == 1) // rotate right
        rotation_player(mlx, 1);
    if (mlx->player->rot == -1) // rotate left
        rotation_player(mlx, 0);

    double move_speed = PLAYER_SPEED;
    move_x = 0;
    move_y = 0;

    if (mlx->player->u_d == 1) // move forward
    {
        move_x += mlx->player->dir_x * move_speed;
        move_y += mlx->player->dir_y * move_speed;
    }
    if (mlx->player->u_d == -1) // move backward
    {
        move_x -= mlx->player->dir_x * move_speed;
        move_y -= mlx->player->dir_y * move_speed;
    }
    if (mlx->player->l_r == 1) // move right (strafe)
    {
        move_x += mlx->player->plane_x * move_speed;
        move_y += mlx->player->plane_y * move_speed;
    }
    if (mlx->player->l_r == -1) // move left (strafe)
    {
        move_x -= mlx->player->plane_x * move_speed;
        move_y -= mlx->player->plane_y * move_speed;
    }
    move_player(mlx, move_x, move_y);
}
