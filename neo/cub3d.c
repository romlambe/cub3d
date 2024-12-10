#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2)
		return ((printf("Error: usage ./cub3d <filename.cub>\n")), 1);
	if (available_name(av[1]) == 1)
		return (printf("Error: Invalid file type\n"), 1);
	init_data(&data);
	if (parser(&data, av) == 1 || is_map_closed(&data) == 1)
		return (free_data(&data), 1);
	data.mlx_win = mlx_new_window(data.mlx, data.win_width, data.win_height, \
		"CUB3 PAR ROMAIN, veigar");
	mlx_do_key_autorepeatoff(data.mlx);
	mlx_hook(data.mlx_win, 2, 1L << 0, manage_input_press, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, manage_input_release, &data);
	mlx_loop_hook(data.mlx, render_cube, &data);
	mlx_loop(data.mlx);
	return (0);
}
