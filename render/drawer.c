/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:04:50 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/18 12:15:47 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_floor_ceilling(t_image *image, int x)
{
	int	y;
	int	f_color;
	int	c_color;

	c_color = rgb(image->data->assets.c_color[0],
			image->data->assets.c_color[1],
			image->data->assets.c_color[2]);
	f_color = rgb(image->data->assets.f_color[0],
			image->data->assets.f_color[1],
			image->data->assets.f_color[2]);
	y = -1;
	while (++y < image->data->win_height / 2)
		draw_pixel(image, x, y, c_color);
	while (++y < image->data->win_height - 1)
		draw_pixel(image, x, y, f_color);
}


void	draw_wall_stripe(t_draw_wall *wall, t_image *img, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = wall->start_y - 1;
	while (++y < wall->end_y)
	{
		tex_y = (int)(wall->tex_pos) & (wall->texture->width - 1);
		wall->tex_pos += wall->step;
		color = get_pixel_color(wall->texture, wall->tex_x, tex_y);
		draw_pixel(img, x, y, color);
	}
}

void	draw_stripe(t_ray *ray, t_image *image, int x, t_player *player)
{
	t_draw_wall	stripe;

	stripe.h = image->data->win_height;
	stripe.texture = choose_texture(image->data, ray->side);
	stripe.line_height = (int)(stripe.h / ray->perp_wall_dist);
	stripe.start_y = -stripe.line_height / 2 + stripe.h / 2;
	stripe.end_y = stripe.line_height / 2 + stripe.h / 2;
	if (stripe.start_y < 0)
		stripe.start_y = 0;
	if (stripe.end_y >= stripe.h)
		stripe.end_y = stripe.h - 1;
	if (ray->side >= 2)
		stripe.wall_x = player->y_ply + ray->perp_wall_dist * ray->ray_dir_y;
	else
		stripe.wall_x = player->x_ply + ray->perp_wall_dist * ray->ray_dir_x;
	stripe.wall_x -= floorf(stripe.wall_x);
	stripe.tex_x = (int)(stripe.wall_x * stripe.texture->width);
	if (ray->side >= 2 && ray->ray_dir_x > 0)
		stripe.tex_x = stripe.texture->height - stripe.tex_x - 1;
	if (ray->side <= 1 && ray->ray_dir_y != 0)
		stripe.tex_x = stripe.texture->height - stripe.tex_x - 1;
	stripe.step = 1.0 * stripe.texture->height / stripe.line_height;
	stripe.tex_pos = (stripe.start_y - stripe.h / 2 + stripe.line_height / 2)
		* stripe.step;
	draw_wall_stripe(&stripe, image, x);
}

void	draw_sprite_stripe(
	t_image *img, t_sprite_transform *transform, int sprite_index, int stripe)
{
	int	tex_x;
	int	y;
	int	d;
	int	tex_y;
	int	color;

	tex_x = (int)(256 * (stripe - 
		(-transform->sprite_width / 2 + transform->sprite_screen_x)) * 64
			/ transform->sprite_width) / 256;
	if (transform->transform_y > 0
		&& transform->transform_y < img->data->zbuffer[stripe])
	{
		y = transform->draw_start_y;
		while (y < transform->draw_end_y)
		{
			d = (y - transform->v_move_screen) * 256 - img->data->win_height 
				* 128 + transform->sprite_height * 128;
			tex_y = ((d * 64) / transform->sprite_height) / 256;
			color = get_pixel_color(&img->data->sprites[sprite_index].texture,
					tex_x, tex_y);
			if (color)
				draw_pixel(img, stripe, y, color);
			y++;
		}
	}
}

void	draw_sprite_stripes(
	t_data *data, t_image *img, t_sprite_transform *transform, int sprite_index)
{
	int	stripe;

	(void) data;
	stripe = transform->draw_start_x;
	while (stripe < transform->draw_end_x)
	{
		draw_sprite_stripe(img, transform, sprite_index, stripe);
		stripe++;
	}
}
