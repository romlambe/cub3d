#include "cub3d.h"

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(map[i++]);
	free(map);
}

void	free_assets(t_data *data)
{
	if (data->assets.n_texture.img)
		mlx_destroy_image(data->mlx, data->assets.n_texture.img);
	if (data->assets.s_texture.img)
		mlx_destroy_image(data->mlx, data->assets.s_texture.img);
	if (data->assets.e_texture.img)
		mlx_destroy_image(data->mlx, data->assets.e_texture.img);
	if (data->assets.w_texture.img)
		mlx_destroy_image(data->mlx, data->assets.w_texture.img);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->n_sprites)
		mlx_destroy_image(data->mlx, data->sprites[i].texture.img);
	free_assets(data);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	if (data->sprites)
		free(data->sprites);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i++])
		free(tab[i]);
	free(tab);
}
