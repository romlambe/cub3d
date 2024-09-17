/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:28:11 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/17 18:14:13 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *dest;

	if (x < 0 || x >= W_S)
		return ;
	if (y < 0 || y >= H_S)
		return ;
	dest = (char *)mlx->image->addr + (y * mlx->image->lenght_line + x * (mlx->image->bit_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	draw_floor(t_mlx *mlx, int ray, int c_pix, int f_pix)
{
	int	i;

	i = f_pix;
	while (i < H_S)
		put_pixel(mlx, ray, i++, 0x000000);
	i = 0;
	while (i < c_pix)
		put_pixel(mlx, ray, i++, 0x0000000);
}

int get_texture(t_mlx *mlx)
{
	if (mlx->ray->wall_flag == 0)
	{
		if (mlx->ray->ray_dir_x > 0)
			return (0xADD8E6);
		else
			return (0x98FB98);
	}
	else
	{
		if (mlx->ray->ray_dir_y > 0)
			return (0x00008B);
		else
			return (0xFFA07A);
	}
}



void	draw_wall(t_mlx *mlx, int ray, int c_pix, int f_pix)
{
	int color;

	color = get_texture(mlx);
	printf("Ray: %d, c_pix: %d, f_pix: %d, Couleur: %06X\n", ray, c_pix, f_pix, color);
	while (c_pix < f_pix)
		put_pixel(mlx, ray, c_pix++, color);
}

void	render_wall(t_mlx *mlx, int ray)
{
	double  wall_h;
	double  f_pix;
	double  c_pix;

	wall_h = (TILE_SIZE / mlx->ray->distance) * ((W_S / 2) / tan(mlx->player->fov_rd / 2));

	f_pix = (H_S / 2) + (wall_h / 2);
	c_pix = (H_S / 2) - (wall_h / 2);
	if (f_pix > H_S)
		f_pix = H_S - 1;
	if (c_pix < 0)
		c_pix = 0;
	draw_floor(mlx, ray, c_pix, f_pix);
	draw_wall(mlx, ray, c_pix, f_pix);
}

