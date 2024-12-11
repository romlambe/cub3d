/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:04:56 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/11 09:39:58 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	manage_left_camera_mov(t_player *player, double dt)
{
	float	old_dir_x;
	float	old_plane_x;
	double	rot_speed;

	rot_speed = ROTATION_SPEED * dt;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y
		* sin(-rot_speed);
	player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y
		* cos(-rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y
		* sin(-rot_speed);
	player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y
		* cos(-rot_speed);
}

void	manage_right_camera_mov(t_player *player, double dt)
{
	float	old_dir_x;
	float	old_plane_x;
	double	rot_speed;

	rot_speed = ROTATION_SPEED * dt;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y
		* sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y
		* cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y
		* sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y
		* cos(rot_speed);
}

int	manage_input_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	if (keycode == KEY_W)
		data->player.move_y = 1;
	if (keycode == KEY_S)
		data->player.move_y = -1;
	if (keycode == KEY_A)
		data->player.move_x = -1;
	if (keycode == KEY_D)
		data->player.move_x = 1;
	if (keycode == LEFT)
		manage_left_camera_mov(&(data->player), data->deltatime);
	if (keycode == RIGHT)
		manage_right_camera_mov(&(data->player), data->deltatime);
	return (0);
}

int	manage_input_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->player.move_y = 0;
	if (keycode == KEY_S)
		data->player.move_y = 0;
	if (keycode == KEY_A)
		data->player.move_x = 0;
	if (keycode == KEY_D)
		data->player.move_x = 0;
	return (0);
}
