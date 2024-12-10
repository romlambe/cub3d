/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:04:58 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 15:15:46 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_pixel_color(t_image *texture, int x, int y)
{
	return (((int *)texture->addr)[texture->height * y + x]);
}

void	draw_pixel(t_image *img, int x, int y, int color)
{
	int		pos;
	char	*dest;

	if (x > img->data->win_width || x < 0 || y > img->data->win_height || y < 0)
		return ;
	pos = (y * img->size_line + x * (img->bpp / 8));
	dest = img->addr + pos;
	*((unsigned int *) dest) = color;
}

int	is_color_is_correct(int r, int g, int b)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		return (0);
	return (1);
}

int	rgba(int r, int g, int b, int a)
{
	if (is_color_is_correct(r, g, b) || a < 0 || a > 255)
		return (-1);
	return (a << 24 | r << 16 | g << 8 | b);
}

int	rgb(int r, int g, int b)
{
	return (rgba(r, g, b, 255));
}
