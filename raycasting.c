/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:31:43 by romlambe          #+#    #+#             */
/*   Updated: 2024/11/19 05:47:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
		else
			return (0);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	inter_chek(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > (M_PI / 2) && angle < (3 * M_PI) / 2))
		{
			*inter *= TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if (y_m >= mlx->data->h_size || x_m >= (int)ft_strlen(mlx->data->map[y_m]))
	return (0);
	if (mlx->data->map[y_m] && x_m <= (int)ft_strlen(mlx->data->map[y_m]))
		if (mlx->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float get_horizontal_inter(t_mlx *mlx, float angle) {
	float h_x, h_y, x_step, y_step;
	int facing_down = angle > 0 && angle < M_PI;

	y_step = TILE_SIZE;
	if (!facing_down)
		y_step *= -1;

	h_y = floor(mlx->player->y_ply / TILE_SIZE) * TILE_SIZE;
	if (facing_down)
		h_y += TILE_SIZE;
	else
		h_y -= 0.0001;

	x_step = TILE_SIZE / tan(angle);
	if ((facing_down && x_step < 0) || (!facing_down && x_step > 0))
		x_step *= -1;

	h_x = mlx->player->x_ply + (h_y - mlx->player->y_ply) / tan(angle);

	while (wall_hit(h_x, h_y, mlx)) {
		h_x += x_step;
		h_y += y_step;
	}

	return sqrt(pow(h_x - mlx->player->x_ply, 2) + pow(h_y - mlx->player->y_ply, 2));
}


float get_vertical_inter(t_mlx *mlx, float angle) {
	float v_x, v_y, x_step, y_step;
	int facing_right = angle < M_PI / 2 || angle > 3 * M_PI / 2;

	x_step = TILE_SIZE;
	if (!facing_right)
		x_step *= -1;

	v_x = floor(mlx->player->x_ply / TILE_SIZE) * TILE_SIZE;
	if (facing_right)
		v_x += TILE_SIZE;
	else
		v_x -= 0.0001;

	y_step = TILE_SIZE * tan(angle);
	if ((facing_right && y_step < 0) || (!facing_right && y_step > 0))
		y_step *= -1;

	v_y = mlx->player->y_ply + (v_x - mlx->player->x_ply) * tan(angle);

	while (wall_hit(v_x, v_y, mlx)) {
		v_x += x_step;
		v_y += y_step;
	}

	return (sqrt(pow(v_x - mlx->player->x_ply, 2) + pow(v_y - mlx->player->y_ply, 2)));
}

float	nor_angle(float angle) {
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}



void	cast_ray(t_mlx *mlx)
{
	int	ray;

	ray = 0;
	while (ray < W_S)
	{
		double camera_x = 2 * ray / (double)W_S - 1;
		double ray_dir_x = mlx->player->dir_x + mlx->player->plane_x * camera_x;
		double ray_dir_y = mlx->player->dir_y + mlx->player->plane_y * camera_x;

		mlx->ray->wall_flag = 0;

		int map_x = (int)(mlx->player->x_ply / TILE_SIZE);
		int map_y = (int)(mlx->player->y_ply / TILE_SIZE);

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		int step_x, step_y;
		double side_dist_x, side_dist_y;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (mlx->player->x_ply / TILE_SIZE - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - mlx->player->x_ply / TILE_SIZE) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (mlx->player->y_ply / TILE_SIZE - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - mlx->player->y_ply / TILE_SIZE) * delta_dist_y;
		}

		mlx->ray->ray_dir_x = ray_dir_x;
		mlx->ray->ray_dir_y = ray_dir_y;
		int hit = 0;
		int side;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (mlx->data->map[map_y][map_x] == '1')
				hit = 1;
		}

		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - mlx->player->x_ply / TILE_SIZE + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - mlx->player->y_ply / TILE_SIZE + (1 - step_y) / 2) / ray_dir_y;

		mlx->ray->distance = perp_wall_dist * TILE_SIZE;
		mlx->ray->wall_flag = side;

		// Rendre le mur
		render_wall(mlx, ray);

		ray++;
	}
}

