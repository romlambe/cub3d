/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:08:34 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 23:08:21 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_side(t_ray *ray, int axis)
{
	if (axis == 3)
	{
		if (ray->side >= 2)
			ray->side = 4;
		else
			ray->side = -1;
		return ;
	}
	if (axis == 0)
	{
		if (ray->ray_dir_x > 0.0f)
			ray->side = 2;
		else
			ray->side = 3;
		return ;
	}
	if (ray->ray_dir_y > 0.0f)
		ray->side = 0;
	else
		ray->side = 1;
}

void	check_hit_wall(t_ray *ray, t_data *data, t_player *player)
{
	ray->map_x = (int)player->x_ply;
	ray->map_y = (int)player->y_ply;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			check_side(ray, 0);
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			check_side(ray, 1);
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

int	check_assets(t_data *data, int fd)
{
	if (data->assets.n_texture.img == NULL
		|| data->assets.s_texture.img == NULL
		|| data->assets.e_texture.img == NULL
		|| data->assets.w_texture.img == NULL)
		return (free_gnl(fd), printf("Error: Incorrect image\n"), 1);
	return (0);
}
