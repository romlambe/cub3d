/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:28:11 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/15 20:08:18 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0 || x >= W_S)
		return ;
	if (y < 0 || y >= H_S)
		return ;
	mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
}

void	draw_floor(t_mlx *mlx, int ray, int c_pix, int f_pix)
{
	int	i;

	i = f_pix;
	while (i < H_S)
		put_pixel(mlx, ray, i++, 0xB99470FF);
	i = 0;
	while (i < c_pix)
		put_pixel(mlx, ray, i++,  0xB99470FF);
}

int	get_texture(t_mlx *mlx, int flag) //pour le moment je balance que des couleurs
{
	mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl);
	if (flag == 0)
	{
		if (mlx->ray->ray_ngl < (3 * M_PI) / 2 && mlx->ray->ray_ngl > M_PI / 2)
			return (0x00FF00); //rouge
		else
			return (0xFF0001); //vert
	}
	else
	{
		if (mlx->ray->ray_ngl <  M_PI && mlx->ray->ray_ngl > M_PI / 2)
			return (0x0000FF); // bleu
		else
			return (0xFFFF00); // jaune
	}
}

void	draw_wall(t_mlx *mlx, int ray, int c_pix, int f_pix)
{
	int color;

	color = get_texture(mlx, mlx->ray->wall_flag);
	while (c_pix < f_pix)
		put_pixel(mlx, ray, c_pix++, color);
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	f_pix;
	double	c_pix;

	mlx->ray->distance = cos(nor_angle(mlx->ray->ray_ngl - mlx->player->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((W_S / 2) / tan(mlx->player->fov_rd / 2));
	f_pix = (H_S / 2) + (wall_h / 2);
	c_pix = (H_S / 2) - (wall_h / 2);
	if (f_pix > H_S)
		f_pix = H_S;
	if (c_pix < 0)
		c_pix = 0;
	draw_wall(mlx, ray, c_pix, f_pix);
	draw_floor(mlx, ray, c_pix, f_pix);
}
