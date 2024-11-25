float	nor_angle(float angle) // aucun appel
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

float get_vertical_inter(t_mlx *mlx, float angle)// aucun appel pour le moment
{
	float v_x, v_y, x_step, y_step;
	int facing_right = angle < M_PI / 2 || angle > 3 * M_PI / 2;

	x_step = TILE_SIZE;
	if (!facing_right)
		x_step *= -1;

	v_x = floor(mlx->player->x_ply / TILE_SIZE) * TILE_SIZE;
	if (facing_right)
		v_x += TILE_SIZE;
	else
		v_x -= 0.0001;

	y_step = TILE_SIZE * tan(angle);
	if ((facing_right && y_step < 0) || (!facing_right && y_step > 0))
		y_step *= -1;

	v_y = mlx->player->y_ply + (v_x - mlx->player->x_ply) * tan(angle);

	while (wall_hit(v_x, v_y, mlx)) {
		v_x += x_step;
		v_y += y_step;
	}

	return (sqrt(pow(v_x - mlx->player->x_ply, 2) + pow(v_y - mlx->player->y_ply, 2)));
}

float get_horizontal_inter(t_mlx *mlx, float angle) // aucun appel
{
	float h_x, h_y, x_step, y_step;
	int facing_down = angle > 0 && angle < M_PI;

	y_step = TILE_SIZE;
	if (!facing_down)
		y_step *= -1;

	h_y = floor(mlx->player->y_ply / TILE_SIZE) * TILE_SIZE;
	if (facing_down)
		h_y += TILE_SIZE;
	else
		h_y -= 0.0001;

	x_step = TILE_SIZE / tan(angle);
	if ((facing_down && x_step < 0) || (!facing_down && x_step > 0))
		x_step *= -1;

	h_x = mlx->player->x_ply + (h_y - mlx->player->y_ply) / tan(angle);

	while (wall_hit(h_x, h_y, mlx)) {
		h_x += x_step;
		h_y += y_step;
	}

	return sqrt(pow(h_x - mlx->player->x_ply, 2) + pow(h_y - mlx->player->y_ply, 2));
}

int	inter_chek(float angle, float *inter, float *step, int is_horizon) // aucun appel
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > (M_PI / 2) && angle < (3 * M_PI) / 2))
		{
			*inter *= TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	unit_circle(float angle, char c) // aucun appel
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
		else
			return (0);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
		else
			return (0);
	}
	return (0);
}

int available_name(t_data *data) // pour le moment aucun appel
{
	int start_pos;
	int size_cub;
	int size_string;

	size_cub = ft_strlen(".cub");
	size_string = ft_strlen(data->name);
	start_pos = size_string - size_cub;
	if (start_pos <= 0 || ft_strcmp(data->name + start_pos, ".cub"))
		return (0);
	return (1);
}