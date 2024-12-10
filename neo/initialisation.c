#include "cub3d.h"

void	init_assets(t_assets *assets)
{
	assets->n_texture.img = NULL;
	assets->s_texture.img = NULL;
	assets->e_texture.img = NULL;
	assets->w_texture.img = NULL;
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		printf("Error: mlx_init\n");
	data->mlx_win = NULL;
	data->win_height = 600;
	data->win_width = 800;
	data->mouse_x = data->win_width / 2;
	init_assets(&(data->assets));
	data->fps = get_time();
	data->time = get_time();
	data->player.x_ply = -1;
	data->n_sprites = 0;
	data->sprites = NULL;
	data->deltatime = 0;
}

void	init_player(t_data *data, char direction, int y, int x)
{
	data->map[y][x] = '0';
	data->player.x_ply = (float)x + 0.5f;
	data->player.y_ply = (float)y + 0.5f;
	data->player.move_x = 0;
	data->player.move_y = 0;
	set_player_direction(&(data->player), direction);
}
