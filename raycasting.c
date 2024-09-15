/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:31:43 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/15 19:50:35 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
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
	if (y_m >= mlx->data->h_size || x_m >= mlx->data->w_size)
		return (0);
	if (mlx->data->map[y_m] && x_m <= (int)ft_strlen(mlx->data->map[y_m]))
		if (mlx->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_horizontal_inter(t_mlx *mlx, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE / tan(angle);
	y_step= TILE_SIZE;
	h_y = floor(mlx->player->y_ply / TILE_SIZE) * TILE_SIZE;
	pixel = inter_chek(angle, &h_y, &y_step, 1);
	h_x = mlx->player->x_ply + (h_y - mlx->player->y_ply) / tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0)
		|| (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - mlx->player->x_ply, 2)
		+ pow(h_y - mlx->player->y_ply, 2)));
}

float	get_vertical_inter(t_mlx *mlx, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE / tan(angle);
	v_x = floor(mlx->player->x_ply / TILE_SIZE) * TILE_SIZE;
	pixel = inter_chek(angle, &v_x, &x_step, 0);
	v_y = mlx->player->y_ply + (v_x - mlx->player->x_ply) / tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0)
		|| (!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += x_step;
	}
	return (sqrt(pow(v_x - mlx->player->x_ply, 2) + pow(v_y - mlx->player->y_ply, 2)));
}
float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (M_PI * 2);
	else if (angle > (2 * M_PI))
		angle -= (M_PI * 2);
	return (angle);
}


void	cast_ray(t_mlx *mlx)
{
	double	v_inter;
	double	h_inter;
	int		ray;

	ray = 0;
	mlx->ray->ray_ngl = mlx->player->angle - (mlx->player->fov_rd / 2);
	while (ray < W_S)
	{
		mlx->ray->wall_flag = 0;
		v_inter = get_vertical_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		h_inter = get_horizontal_inter(mlx, nor_angle(mlx->ray->ray_ngl));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->wall_flag = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ray->ray_ngl += mlx->player->fov_rd / H_S;
	}
}