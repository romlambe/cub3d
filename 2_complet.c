#include "cub3d.h"

long long get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void calculate_side_dist(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x_ply - (int)player->x_ply) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (((int)player->x_ply) + 1.0 - player->x_ply) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y_ply - ((int)player->y_ply)) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (((int)player->y_ply) + 1.0 - player->y_ply) * ray->delta_dist_y;
	}
}

void calculate_ray_distance(t_ray *ray, t_player *player, float cameraX)
{
	ray->ray_dir_x = player->dir_x + player->plane_x * -cameraX;
	ray->ray_dir_y = player->dir_y + player->plane_y * -cameraX;

	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 9999.0f;
	else
		ray->delta_dist_x = fabsf(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 9999.0f;
	else
		ray->delta_dist_y = fabsf(1 / ray->ray_dir_y);
	calculate_side_dist(ray, player);
}

void check_side(t_ray *ray, int axis)
{
	if (axis == 3)
	{
		if(ray->side >= 2)
			ray->side = 4;
		else
			ray->side = -1;
		return ;
	}
	if (axis == 0)
	{
		if (ray->ray_dir_x > 0.0f)
			ray->side = 2;
		else
			ray->side = 3;
		return ;
	}
	if (ray->ray_dir_y > 0.0f)
		ray->side = 0;
	else
		ray->side = 1;
}

void check_hit_wall(t_ray *ray, t_data *data, t_player *player)
{
	ray->map_x = (int)player->x_ply;
	ray->map_y = (int)player->y_ply;

	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			check_side(ray, 0);
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			check_side(ray, 1);
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
t_image *choose_texture(t_data *data, int side)
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

void	initialize_sprite_distance(t_data *data, int *sprite_order, float *sprite_distance)
{
	int	i;

	i = 0;
	while (i++ < data->n_sprites)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((data->player.y_ply - data->sprites[i].x)
			*(data->player.y_ply - data->sprites[i].x)
			+ (data->player.x_ply - data->sprites[i].y)
			*(data->player.x_ply - data->sprites[i].y));
	}
}

t_sprite_sort	*create_sprite(int *sprite_order, float *sprite_distance, int n_sprites)
{
	int	i;
	t_sprite_sort *sprites;

	sprites = (t_sprite_sort *)malloc(n_sprites * sizeof(t_sprite_sort));
	if (!sprites)
		return (NULL);
	i = 0;
	while (i < n_sprites)
	{
		sprites[i].dist = sprite_distance[i];
		sprites[i].order = sprite_order[i];
		i++;
	}
	return sprites;
}

void	swap_sprites(t_sprite_sort *a, t_sprite_sort *b)
{
	t_sprite_sort temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_sprite_array(t_sprite_sort *sprites, int n_sprites)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_sprites - 1)
	{
		j = 0;
		while (j < n_sprites - i - 1)
		{
			if (sprites[j].dist < sprites[j + 1].dist)
				swap_sprites(&sprites[i], &sprites[j + 1]);
			j++;
		}
		i++;
	}
}

void	update_array(t_sprite_sort *sprites, int *order_sprite, float *sprite_distance,int n_sprites)
{
	int	i;

	i = 0;
	while (i < n_sprites)
	{
		sprite_distance[i] = sprites[i].dist;
		order_sprite[i] = sprites[i].order;
		i++;
	}
}

void	sort_sprite(int *sprite_order, float *sprite_distance, int n_sprites)
{
	t_sprite_sort	*sprites;

	sprites = create_sprite(sprite_order, sprite_distance,n_sprites);
	if (!sprites)
		return ;
	sort_sprite_array(sprites, n_sprites);
	update_array(sprites, sprite_order, sprite_distance, n_sprites);
	free(sprites);
}

void	sort_sprite_distance(t_data *data, int *sprite_order, float *sprite_distance)
{
	sort_sprite(sprite_order, sprite_distance, data->n_sprites);
}

void	calculate_transform_values(t_data *data, t_sprite_transform *transform, int sprite_order)
{
	transform->sprite_x = data->sprites[sprite_order].x - data->player.y_ply;
	transform->sprite_y = data->sprites[sprite_order].y - data->player.x_ply;
	transform->int_dev = 1.0 / (data->player.plane_y * data->player.dir_x
		- data->player.dir_y * data->player.plane_x);
	transform->transform_x = -transform->int_dev * (data->player.dir_x
		* transform->sprite_x - data->player.dir_y * transform->sprite_y);
	transform->transform_y = transform->int_dev * (-data->player.plane_x
		* transform->sprite_x + data->player.plane_y * transform->sprite_y);
	transform->sprite_screen_x = (int)((data->win_width / 2)
		* (1 + transform->transform_x / transform->transform_y));
}

int	int_abs(int value)
{
	if (value < 0)
		return (-value);
	else
		return (value);
}

void	calculate_draw_dimensions(t_data *data, t_sprite_transform *transform)
{
	transform->v_move_screen = (int)(0.0 / transform->transform_y);
	transform->sprite_height = int_abs((int)(data->win_height / (transform->transform_y))) / 1;
	transform->draw_start_y = -transform->sprite_height + data->win_height / 2 + transform->v_move_screen;
	if (transform->draw_start_y < 0)
		transform->draw_start_y = 0;
	transform->draw_end_y = transform->sprite_height / 2 + data->win_height / 2 + transform->v_move_screen;
	if (transform->draw_end_y >= data->win_height)
		transform->draw_end_y = data->win_height - 1;
	transform->sprite_width = int_abs((int)(data->win_height / (transform->transform_y))) / 1;
	transform->draw_start_x = -transform->sprite_width / 2 + transform->sprite_screen_x;
	if (transform->draw_start_x < 0)
		transform->draw_start_x = 0;
	transform->draw_end_x = transform->sprite_width / 2 + transform->sprite_screen_x;
	if (transform->draw_end_x > data->win_width)
		transform->draw_end_x = data->win_width;
}

void	draw_sprite(t_data *data, t_image *img)
{
	int					i;
	int					*sprite_order;
	float				*sprite_distance;
	t_sprite_transform	transform;

	sprite_order = malloc(sizeof(int) * data->n_sprites);
	sprite_distance = malloc(sizeof(float) * data->n_sprites);
	initialize_sprite_distance(data, sprite_order, sprite_distance);
	sort_sprite_distance(data, sprite_order,sprite_distance);
	i = 0;
	while (i < data->n_sprites)
	{
		calculate_transform_values(data, &transform, sprite_order[i]);
		calculate_draw_dimensions(data, &transform);
		draw_sprite_stripes(data, img, &transform, sprite_order[i]);
		i++;
	}
	free(sprite_order);
	free(sprite_distance);
}

void	calc_perp_wall_dist(t_ray *ray, t_data *data)
{
	ray->perp_wall_dist = (ray->map_x - data->player.x_ply + ray->wall_xoffset
		+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	if (ray->side < 2)
		ray->perp_wall_dist = (ray->map_y - data->player.y_ply + ray->wall_xoffset
			+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

/* Orientations
	0 : N
	1 : S
	2 : E
	3 : W
*/



void	get_texture(t_data *data, char *path, t_image *texture)
{
	printf("%s\n", path);
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &(texture->width), &(texture->height));
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
				get_texture(data, "./textures/north_texture.xpm", &(data->sprites[i].texture));
			else if (data->sprites[i].state == 1)
				get_texture(data, "./textures/south_texture.xpm", &(data->sprites[i].texture));
			else if (data->sprites[i].state == 2)
				get_texture(data, "./textures/east_texture.xpm", &(data->sprites[i].texture));
			else
				get_texture(data, "./textures/west_texture.xpm", &(data->sprites[i].texture));
			if (++data->sprites[i].state > 3)
				data->sprites[i].state = 0;
		}
		data->time = get_time();
	}
}

static void	render_raycast(t_image *img, t_data *data, t_player *player)
{
	int	w;
	int	i;
	t_ray	*ray;

	w = img->data->win_width;
	i = -1;
	while (++i < w)
	{
		ray = ft_calloc(1, sizeof(t_ray));
		calculate_ray_distance(ray, player, 2 * i / ((float) w) - 1);
		check_hit_wall(ray, data, player);
		calc_perp_wall_dist(ray, data);
		draw_floor_ceilling(img, i);
		draw_stripe(ray, img, i, player);
		data->zbuffer[i] = ray->perp_wall_dist;
		free(ray);
	}
	draw_sprite(data, img);
	switch_texture(data);
	data->old_fps = data->fps;
	data->fps = get_time();
	data->deltatime = (data->fps - data->old_fps) / 1000.0;
}

int	render_cube(t_data * data)
{
	t_image main;

	update_loop(data);
	main.data = data;
	main.img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	main.addr = mlx_get_data_addr(main.img, &(main.bpp), &(main.size_line), &(main.endian));
	render_raycast(&main, data, &(data->player));
	mlx_put_image_to_window(data->mlx, data->mlx_win, main.img, 0, 0);
	mlx_destroy_image(data->mlx, main.img);
	return 0;
}

int	copy_color(t_data *data, char **split_color, char *color)
{
	if (color[0] == 'F' && color[1] == '\0')
	{
		data->assets.f_color[0] = ft_atoi(split_color[0]);
		data->assets.f_color[1] = ft_atoi(split_color[1]);
		data->assets.f_color[2] = ft_atoi(split_color[2]);
		printf("%d\n", data->assets.f_color[0]);
		printf("%d\n", data->assets.f_color[1]);
		printf("%d\n", data->assets.f_color[2]);
		if (!data->assets.f_color[0] || !data->assets.f_color[1] || !data->assets.f_color[2])
			return (1);
		if (is_color_is_correct(data->assets.f_color[0],
				data->assets.f_color[1], data->assets.f_color[2]) == 1)
			return(1);
	}
	else if (color[0] == 'C' && color[1] == '\0')
	{
		data->assets.c_color[0] = ft_atoi(split_color[0]);
		data->assets.c_color[1] = ft_atoi(split_color[1]);
		data->assets.c_color[2] = ft_atoi(split_color[2]);
		if (is_color_is_correct(data->assets.f_color[0],
				data->assets.f_color[1], data->assets.f_color[2]) == 1)
			return (printf("Error: Floor color error\n"),1);
	}
	else
		return (1);
	return (0);
}

int	allocate_map(t_data *data, int rows, int columns)
{
	int	i;

	i = 0;
	data->map = malloc(sizeof(char *) * (rows + 1));
	if (!data->map)
		return (printf("Error: memories\n"),1);
	while (i < rows)
	{
		data->map[i] = malloc(sizeof(char) * (columns + 1));
		if (!data->map[i])
			return (printf("Error: memories columns\n"),1);
		// free_tab(data->map);
		i++;
	}
	data->map[rows] = 0;
	return (0);
}

int	copy_map(t_data *data, char *filename)
{
	int		fd;
	char	*line;
	int	i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)))
	{
		if (*line == '0' || *line == '1'){
			data->map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	if (search_player_pos(data) != 0)
		return (printf("Error: player position not found\n"), 1);
	return (0);
}

int	copy_assets(t_data *data, char **split_line)
{
	char *texture_path;

	if (!split_line[1])
		return (1);
	texture_path = ft_strncpy(split_line[1], ft_strchr_i(split_line[1], '\n'));
	if (!texture_path)
		return (printf("Error: Failed to extract texture path\n"), 1);
	if (ft_strcmp(split_line[0], "NO") == 0)
		get_texture(data, texture_path, &(data->assets.n_texture));
	else if (ft_strcmp(split_line[0], "SO") == 0)
		get_texture(data, texture_path, &(data->assets.s_texture));
	else if (ft_strcmp(split_line[0], "WE") == 0)
		get_texture(data, texture_path, &(data->assets.w_texture));
	else if (ft_strcmp(split_line[0], "EA") == 0)
		get_texture(data, texture_path, &(data->assets.e_texture));
	else
		return (free(texture_path), printf("Error: Incorret texture path\n"), 1);
	return (free(texture_path), 0);
}


int	check_assets(t_data *data, int fd)
{
	if (data->assets.n_texture.img == NULL
		|| data->assets.s_texture.img == NULL
		|| data->assets.e_texture.img == NULL
		|| data->assets.w_texture.img == NULL)
		return (free_gnl(fd), printf("Error: Incorrect image\n"), 1);
	return (0);
}

int	skip_line(char *line)
{
	if (line[0] == '\n' && line[1] == '\0')
		return (free(line), 1);
	return (0);
}

int	parsing_map_assets(t_data *data, int fd)
{
	char	*line;
	char	**line_split;
	int		i;

	i = 4;
	while (i)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		if (skip_line(line) == 1)
			continue ;
		line_split = ft_split(line, ' ');

		free (line);
		if (copy_assets(data, line_split) == 1)
			return (free_tab(line_split), free_gnl(fd) ,1);
		free_tab(line_split);
		i--;
	}
	return (check_assets(data, fd));
}

char	**trim_color(char **split_color)
{
	char	*no32str;
	char	**perfect_color;
	int		index;
	int		goat;

	index = -1;
	goat = 0;
	while (split_color[++index])
		goat += ft_strlen(split_color[index]);
	no32str = malloc(goat + 1);
	goat = 0;
	while (*split_color)
	{
		index = -1;
		while ((*split_color)[++index])
		{
			if ((*split_color)[index] != ' ' && (*split_color)[index] != '\n')
				no32str[goat++] = (*split_color)[index];
		}
		split_color++;
	}
	no32str[goat] = 0;
	perfect_color = ft_split(no32str, ',');
	return (free(no32str), perfect_color);
}

int	parsing_map_colors(t_data *data, int fd)
{
	char	*line;
	char	**split_line;
	char	**split_color;
	int		i;

	(void)data;
	i = 2;
	while (i)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (skip_line(line) == 1)
			continue ;
		split_line = ft_split(line, ' ');

		//////////////////////////// DEBUG /////////////////////////////////
		for (int i = 0; split_line[i]; i++) printf("DEBUG: %s\n", split_line[i]);

		split_color = trim_color(split_line + 1);

		//////////////////////////// DEBUG /////////////////////////////////
		for (int i = 0; split_line[i]; i++) printf("DEBUG COLOR: %s\n", split_color[i]);

		free(line);
		split_color = ft_split(split_line[1], ',');
		if (copy_color(data, split_color, split_line[0]) == 1)
			return (1);
		free_tab(split_line);
		free_tab(split_color);
		i--;
	}
	return (0);
}

int	find_max_len(int fd)
{
	int		len;
	int		max_len;
	char	*line;

	max_len = 0;
	while ((line = get_next_line(fd)))
	{
		len = ft_strlen(line);
		if (len > max_len)
			max_len = len;
		free(line);
	}
	return (max_len);
}


int	find_max_height(char *filename)
{
	int	line_count;
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	line_count = 0;
	line = get_next_line(fd);
	if (fd == -1)
		return (-1);
	while((line = get_next_line(fd)))
	{
		if (*line && (*line == '1' || *line == '0' || *line == '\t' || *line == ' '))
			{
				line_count++;
				// printf("%s", line);
			}
		free (line);
	}
	return (close(fd), line_count);
}

int parsing_map(t_data *data, int fd, char *filename)
{
	char	*line;
	int		i;

	i = 0;
	data->map_width = find_max_len(fd);
	data->map_height = find_max_height(filename);
	while(i)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (skip_line(line) == 1)
		{
			if (i == 0)
				continue ;
			else
				return (free_gnl(fd), 1);
		}
		free(line);
		i++;
	}
	allocate_map(data, data->map_width, data->map_height);
	printf("h:%d\n", data->map_height);
	printf("w:%d\n", data->map_width);
	copy_map(data, filename);

	for (int i = 0; i < 10; i++)
		printf("%s", data->map[i]);
	return (0);
}

int	parser(t_data *data, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error: Can't open the map\n"), 1);
	if (parsing_map_assets(data, fd) == 1)
		return (printf("Error: Assets isn't correctly set up\n"), 1);
	if (parsing_map_colors(data, fd) == 1)
		return (printf("Error: Colors isn't correctly set up\n"), 1);
	if (parsing_map(data, fd, av[1]) == 1)
		return (printf("Error: Map isn't correctly set up\n"), 1);
	return (0);
}

int is_wall_or_space(char c) {
	return (c == '1' || c == ' ' || c == '\0');
}

char **copy_map_flood(char **map, int height)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (printf("Can't copy the map"), NULL);
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_map(map, height);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}


int flood_fill(char **map, int x, int y, int max_len, int height)
{
	if (x < 0 || y < 0 || y >= height || x >= max_len || map[y][x] == '\0')
		return (0);
	if (is_wall_or_space(map[y][x]))
		return (1);
	map[y][x] = ' ';
	if (!flood_fill(map, x + 1, y, max_len, height)
		|| !flood_fill(map, x - 1, y, max_len, height)
		|| !flood_fill(map, x, y - 1, max_len, height)
		|| !flood_fill(map, x, y + 1, max_len, height))
		return (0);
	return (1);
}



int	is_map_closed(t_data *data)
{
	char **map_copy;
	int	x;
	int	y;


	map_copy = copy_map_flood(data->map, data->map_height);
	if (!map_copy)
		return (printf("Error copy map"), 0);
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y][x] == '0')
			{
				if (!flood_fill(map_copy, x, y, data->map_width, data->map_height))
					return(printf("Error: Map is not closed\n"),free_map(map_copy, data->map_height), 1);
			}
		}
	}
	return (free_map(map_copy, data->map_height), 0);
}

int available_name(char *name)
{
	int start_pos;
	int size_cub;
	int size_string;

	size_cub = 4;
	size_string = ft_strlen(name);
	start_pos = size_string - size_cub;
	if (start_pos <= 0 || ft_strcmp(name + start_pos, ".cub"))
		return (1);
	return (0);
}