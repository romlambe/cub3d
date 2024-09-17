/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:04:49 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/17 18:14:38 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_the_game(t_data *data)
{
	t_mlx	mlx;

	mlx.data = data;
	// mlx.win = NULL;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return;
	mlx.win = mlx_new_window(mlx.mlx, W_S, H_S, "Cube3D");
	if (!mlx.win)
		return ;

	init_player(&mlx);
	mlx.image = ft_calloc(1, sizeof(t_image));
	mlx.image->img = mlx_new_image(mlx.mlx, W_S, H_S);
	if (!mlx.image->img)
		return ;

	mlx.image->addr = mlx_get_data_addr(mlx.image->img, &mlx.image->bit_per_pixel, &mlx.image->lenght_line, &mlx.image->endian);
	// put_pixel(&mlx.image, x, y, color);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.image->img, 0, 0);
	// mlx_destroy_image(mlx.mlx, mlx.image->img);
	// mlx.win = mlx_new_window(mlx.mlx, W_S, H_S, "Cube3D");
	// mlx.img = mlx_new_image(mlx.mlx, W_S, H_S);
	mlx_hook(mlx.win, 3, 1L << 1, &ft_reles, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, &keypress, &mlx);
	mlx_loop_hook(mlx.mlx, &game_loop, &mlx);
	// mlx_key_hook(mlx.win, &mlx_key, &mlx);
	mlx_loop(mlx.mlx);
}

int	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	// mlx_destroy_image(mlx->mlx, mlx->img);
	// mlx->img = mlx_new_image(mlx->mlx, H_S, W_S);
	//ft hook pour la rota du perso i guess
	hook(mlx, 0,0);
	cast_ray(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
	return 0;
}

void	init_player(t_mlx *mlx)
{
	mlx->player->x_ply = mlx->data->p_x * TILE_SIZE + TILE_SIZE / 2;
	mlx->player->y_ply = mlx->data->p_y * TILE_SIZE + TILE_SIZE / 2;
	mlx->player->angle = 3 * M_PI / 2;
	mlx->player->fov_rd = (FOV * M_PI) / 180;

	// Calcul des vecteurs directionnels
	mlx->player->dir_x = cos(mlx->player->angle);
	mlx->player->dir_y = sin(mlx->player->angle);

	// Calcul du plan caméra (ajustez la valeur 0.66 selon votre FOV)
	mlx->player->plane_x = -mlx->player->dir_y * tan(mlx->player->fov_rd / 2);
	mlx->player->plane_y = mlx->player->dir_x * tan(mlx->player->fov_rd / 2);
}

// 2 * MPI = E
// 3 * MPI/2 = N
// MPI = W
// MPI / 2 = S


// si pas de map return une erreur
// faire ft pour recup la map (un peu plus tard la flemme la)
t_data	*init_argument(char **av)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	data->map = malloc(sizeof(char *) * 7);  // 5 lignes + NULL
	data->map[0] = "1111111";
	data->map[1] = "1000001";
	data->map[2] = "1010001";
	data->map[3] = "1000111";
	data->map[4] = "100N001";
	data->map[5] = "1111111";
	data->map[6] = NULL;

	data->w_size = find_max_len(data->map);
	data->h_size = find_map_height(data->map);
	if (av[1])
		data->name = ft_strdup(av[1]);
	return (data);
}
