/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:05:03 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/13 14:54:41 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_image	*choose_texture(t_data *data, int side)
{
	if (side == 0)
		return (&(data->assets.n_texture));
	else if (side == 1)
		return (&(data->assets.s_texture));
	else if (side == 2)
		return (&(data->assets.e_texture));
	else
		return (&(data->assets.w_texture));
}

void	get_texture(t_data *data, char *path, t_image *texture)
{
	texture->img = mlx_xpm_file_to_image(data->mlx, path,
			&(texture->width), &(texture->height));
	if (!texture->img)
		return ;
	texture->addr = mlx_get_data_addr(texture->img, &(texture->bpp),
			&(texture->size_line), &(texture->endian));
}

void	switch_texture(t_data *data)
{
	int	i;

	i = -1;
	if (get_time() - data->time >= 1666)
	{
		while (++i < data->n_sprites)
		{
			mlx_destroy_image(data->mlx, data->sprites[i].texture.img);
			if (data->sprites[i].state == 0)
				get_texture(data, "./textures/north_texture.xpm",
					&(data->sprites[i].texture));
			else if (data->sprites[i].state == 1)
				get_texture(data, "./textures/south_texture.xpm",
					&(data->sprites[i].texture));
			else if (data->sprites[i].state == 2)
				get_texture(data, "./textures/east_texture.xpm",
					&(data->sprites[i].texture));
			else
				get_texture(data, "./textures/west_texture.xpm",
					&(data->sprites[i].texture));
			if (++data->sprites[i].state > 3)
				data->sprites[i].state = 0;
		}
		data->time = get_time();
	}
}
