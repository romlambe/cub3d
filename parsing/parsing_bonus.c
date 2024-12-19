/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:18:27 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/19 18:45:20 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_color_bonus(t_data *data)
{
	data->assets.f_color[0] = 253;
	data->assets.f_color[1] = 217;
	data->assets.f_color[2] = 235;
	data->assets.c_color[0] = 253;
	data->assets.c_color[1] = 217;
	data->assets.c_color[2] = 235;
}

void	init_texture_bonus(t_data *data)
{
	char	*texture_path;
	
	texture_path = ft_strncpy("./textures/hello_kitty.xpm", 28);
	if (!texture_path)
		return ;
	get_texture(data, texture_path, &(data->assets.n_texture));
	get_texture(data, texture_path, &(data->assets.s_texture));
	get_texture(data, texture_path, &(data->assets.w_texture));
	get_texture(data, texture_path, &(data->assets.e_texture));
	free(texture_path);
}

