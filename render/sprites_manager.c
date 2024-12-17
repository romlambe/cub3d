/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:08:59 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 23:13:27 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_sprite_distance(t_data *data, int *sprite_order,
	float *sprite_distance)
{
	int	i;

	i = 0;
	while (i < data->n_sprites)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((data->player.y_ply - data->sprites[i].x)
				*(data->player.y_ply - data->sprites[i].x)
				+ (data->player.x_ply - data->sprites[i].y)
				*(data->player.x_ply - data->sprites[i].y));
		i++;
	}
}

void	sort_sprite(int *sprite_order, float *sprite_distance, int n_sprites)
{
	t_sprite_sort	*sprites;

	sprites = create_sprite(sprite_order, sprite_distance, n_sprites);
	if (!sprites)
		return ;
	sort_sprite_array(sprites, n_sprites);
	update_array(sprites, sprite_order, sprite_distance, n_sprites);
	free(sprites);
}

void	sort_sprite_distance(t_data *data, int *sprite_order,
	float *sprite_distance)
{
	sort_sprite(sprite_order, sprite_distance, data->n_sprites);
}

void	calculate_transform_values(t_data *data, t_sprite_transform *transform,
	int sprite_order)
{
	transform->sprite_x = data->sprites[sprite_order].x - data->player.y_ply;
	transform->sprite_y = data->sprites[sprite_order].y - data->player.x_ply;
	transform->int_dev = 1.0 / (data->player.plane_y * data->player.dir_x
			- data->player.dir_y * data->player.plane_x);
	transform->transform_x = -transform->int_dev * (data->player.dir_x
			* transform->sprite_x - data->player.dir_y * transform->sprite_y);
	transform->transform_y = transform->int_dev * (-data->player.plane_x
			* transform->sprite_x + data->player.plane_y * transform->sprite_y);
	transform->sprite_screen_x = (int)((data->win_width / 2)
			* (1 + transform->transform_x / transform->transform_y));
}

void	calculate_draw_dimensions(t_data *data, t_sprite_transform *transform)
{
	transform->v_move_screen = (int)(0.0 / transform->transform_y);
	transform->sprite_height = int_abs((int)(data->win_height
				/ (transform->transform_y))) / 1;
	transform->draw_start_y = -transform->sprite_height + data->win_height
		/ 2 + transform->v_move_screen;
	if (transform->draw_start_y < 0)
		transform->draw_start_y = 0;
	transform->draw_end_y = transform->sprite_height / 2
		+ data->win_height / 2 + transform->v_move_screen;
	if (transform->draw_end_y >= data->win_height)
		transform->draw_end_y = data->win_height - 1;
	transform->sprite_width = int_abs((int)(data->win_height
				/ (transform->transform_y))) / 1;
	transform->draw_start_x = -transform->sprite_width / 2
		+ transform->sprite_screen_x;
	if (transform->draw_start_x < 0)
		transform->draw_start_x = 0;
	transform->draw_end_x = transform->sprite_width / 2
		+ transform->sprite_screen_x;
	if (transform->draw_end_x > data->win_width)
		transform->draw_end_x = data->win_width;
}
