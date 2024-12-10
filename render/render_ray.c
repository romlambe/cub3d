/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:06:01 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 23:31:31 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_side_dist(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x_ply - (int)player->x_ply)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (((int)player->x_ply) + 1.0 - player->x_ply)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y_ply - ((int)player->y_ply))
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (((int)player->y_ply) + 1.0 - player->y_ply)
			* ray->delta_dist_y;
	}
}

void	calculate_ray_distance(t_ray *ray, t_player *player, float cameraX)
{
	ray->ray_dir_x = player->dir_x + player->plane_x * -cameraX;
	ray->ray_dir_y = player->dir_y + player->plane_y * -cameraX;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 9999.0f;
	else
		ray->delta_dist_x = fabsf(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 9999.0f;
	else
		ray->delta_dist_y = fabsf(1 / ray->ray_dir_y);
	calculate_side_dist(ray, player);
}

void	calc_perp_wall_dist(t_ray *ray, t_data *data)
{
	ray->perp_wall_dist = (ray->map_x - data->player.x_ply + ray->wall_xoffset
			+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	if (ray->side < 2)
		ray->perp_wall_dist = (ray->map_y - data->player.y_ply
				+ ray->wall_xoffset + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}
