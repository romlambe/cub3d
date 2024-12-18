/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:02:46 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/18 16:17:26 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_sprite(t_data *data, t_image *img)
{
	int					i;
	int					*sprite_order;
	float				*sprite_distance;
	t_sprite_transform	transform;

	sprite_order = malloc(sizeof(int) * data->n_sprites);
	sprite_distance = malloc(sizeof(float) * data->n_sprites);
	initialize_sprite_distance(data, sprite_order, sprite_distance);
	sort_sprite_distance(data, sprite_order, sprite_distance);
	i = 0;
	while (i < data->n_sprites)
	{
		calculate_transform_values(data, &transform, sprite_order[i]);
		calculate_draw_dimensions(data, &transform);
		draw_sprite_stripes(data, img, &transform, sprite_order[i]);
		i++;
	}
	free(sprite_order);
	free(sprite_distance);
}

void	render_raycast(t_image *img, t_data *data, t_player *player)
{
	int		w;
	int		i;
	t_ray	*ray;

	w = img->data->win_width;
	i = -1;
	while (++i < w)
	{
		ray = ft_calloc(1, sizeof(t_ray));
		calculate_ray_distance(ray, player, 2 * i / ((float) w) - 1);
		check_hit_wall(ray, data, player);
		calc_perp_wall_dist(ray, data);
		draw_floor_ceilling(img, i);
		draw_stripe(ray, img, i, player);
		data->zbuffer[i] = ray->perp_wall_dist;
		free(ray);
	}
	draw_sprite(data, img);
	// switch_texture(data);
	data->old_fps = data->fps;
	data->fps = get_time();
	data->deltatime = (data->fps - data->old_fps) / 1000.0;
}

int	render_cube(t_data *data)
{
	t_image	main;

	update_loop(data);
	main.data = data;
	main.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	main.addr = mlx_get_data_addr(main.img, &(main.bpp),
			&(main.size_line), &(main.endian));
	render_raycast(&main, data, &(data->player));
    int center_x = data->win_width / 2;
    int center_y = data->win_height / 2;
    draw_crosshair(&main, center_x, center_y);
	mlx_put_image_to_window(data->mlx, data->mlx_win, main.img, 0, 0);
	mlx_destroy_image(data->mlx, main.img);
	return (0);
}
