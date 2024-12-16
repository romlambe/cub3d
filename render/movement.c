/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:05:01 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/13 16:39:06 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	search_player_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'E' \
				|| data->map[i][j] == 'W' || data->map[i][j] == 'S')
			{
				init_player(data, data->map[i][j], j, i);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
		return (player->dir_x = 0.0f, player->dir_y = -1.0f,
			player->plane_x = -0.66f, player->plane_y = 0.0f, (void)0);
	else if (direction == 'S')
		return (player->dir_x = 0.0f, player->dir_y = 1.0f,
			player->plane_x = 0.66f, player->plane_y = 0.0f, (void)0);
	else if (direction == 'W')
		return (player->dir_x = -1.0f, player->dir_y = 0.0f,
			player->plane_x = 0.0f, player->plane_y = 0.66f, (void)0);
	else if (direction == 'E')
		return (player->dir_x = 1.0f, player->dir_y = 0.0f,
			player->plane_x = 0.0f, player->plane_y = -0.66f, (void)0);
}

int	update_loop(t_data *data)
{
	if (data->player.move_x != 0)
		manage_strafe_movement(
			data->map, &(data->player), data->player.move_x, data->deltatime);
	if (data->player.move_y != 0)
		manage_forward_movement(
			data->map, &(data->player), data->player.move_y, data->deltatime);
	return (0);
}

void	manage_strafe_movement(
	char **map, t_player *player, int move, double dt)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)player->x_ply;
	pos_y = (int)player->y_ply;
	if (move == -1)
	{
		if (map[pos_y][(int)(player->x_ply + player->plane_x \
			* PLAYER_SPEED * dt)] != '1')
			player->x_ply += player->plane_x * PLAYER_SPEED * dt;
		if (map[(int)(player->y_ply + player->plane_y \
			* PLAYER_SPEED * dt)][pos_x] != '1')
			player->y_ply += player->plane_y * PLAYER_SPEED * dt;
	}
	if (move == 1)
	{
		if (map[pos_y][(int)(player->x_ply - player->plane_x \
			* PLAYER_SPEED * dt)] != '1')
			player->x_ply -= player->plane_x * PLAYER_SPEED * dt;
		if (map[(int)(player->y_ply - player->plane_y \
			* PLAYER_SPEED * dt)][pos_x] != '1')
			player->y_ply -= player->plane_y * PLAYER_SPEED * dt;
	}
}

void	manage_forward_movement(
	char **map, t_player *player, int move, double dt)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)player->x_ply;
	pos_y = (int)player->y_ply;
	if (move == 1)
	{
		if (map[pos_y][(int)(player->x_ply + player->dir_x \
			* PLAYER_SPEED * dt)] != '1')
			player->x_ply += player->dir_x * PLAYER_SPEED * dt;
		if (map[(int)(player->y_ply + player->dir_y \
			* PLAYER_SPEED * dt)][pos_x] != '1')
			player->y_ply += player->dir_y * PLAYER_SPEED * dt;
	}
	if (move == -1)
	{
		if (map[pos_y][(int)(player->x_ply - player->plane_x \
			* PLAYER_SPEED * dt)] != '1')
			player->x_ply -= player->dir_x * PLAYER_SPEED * dt;
		if (map[(int)(player->y_ply - player->dir_y \
			* PLAYER_SPEED * dt)][pos_x] != '1')
			player->y_ply -= player->dir_y * PLAYER_SPEED * dt;
	}
}
