#include "cub3d.h"

void	start_the_game(t_data *data)
{
	t_mlx	mlx;

	mlx.data = data;
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

	init_textures(&mlx);  // Initialisation des textures ici

	mlx.image->addr = mlx_get_data_addr(mlx.image->img,
		&mlx.image->bit_per_pixel, &mlx.image->lenght_line, &mlx.image->endian);
	mlx_hook(mlx.win, 3, 1L << 1, &ft_reles, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, &keypress, &mlx);
	mlx_loop_hook(mlx.mlx, &game_loop, &mlx);
	mlx_loop(mlx.mlx);
}

int	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	// mlx_destroy_image(mlx->mlx, mlx->img);
	// mlx->img = mlx_new_image(mlx->mlx, H_S, W_S);
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

int	ft_reles(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_A)
		mlx->player->l_r = 0;
	else if (keycode == KEY_D)
		mlx->player->l_r = 0;
	else if (keycode == KEY_W)
		mlx->player->u_d = 0;
	else if (keycode == KEY_S)
		mlx->player->u_d = 0;
	else if (keycode == LEFT)
		mlx->player->rot = 0;
	else if (keycode == RIGHT)
		mlx->player->rot = 0;
	return (0);
}

int	keypress(int keycode, void *ml)
{
	t_mlx *mlx = ml;

	if (keycode == KEY_A)
		mlx->player->l_r = -1;
	else if (keycode == KEY_D)
		mlx->player->l_r = 1;
	else if (keycode == KEY_W)
		mlx->player->u_d = 1;
	else if (keycode == KEY_S)
		mlx->player->u_d = -1;
	else if (keycode == LEFT)
		mlx->player->rot = -1;
	else if (keycode == RIGHT)
		mlx->player->rot = 1;
	// ft_reles(keycode, mlx);
	return (0);
}

void    update_player_direction(t_player *player)
{
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * tan(player->fov_rd / 2);
	player->plane_y = player->dir_x * tan(player->fov_rd / 2);
}


void    rotation_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
	update_player_direction(mlx->player);
}

void    move_player(t_mlx *mlx, double move_x, double move_y)
{
	double  new_x;
	double  new_y;
	int     map_grid_x;
	int     map_grid_y;
	double  margin = 5.0; // Ajustez la marge selon vos besoins

	new_x = mlx->player->x_ply + move_x;
	new_y = mlx->player->y_ply + move_y;

	// Vérifier la collision pour la nouvelle position X
	map_grid_x = (int)((new_x + margin * (move_x > 0 ? 1 : -1)) / TILE_SIZE);
	map_grid_y = (int)(mlx->player->y_ply / TILE_SIZE);
	if (mlx->data->map[map_grid_y][map_grid_x] != '1')
		mlx->player->x_ply = new_x;

	// Vérifier la collision pour la nouvelle position Y
	map_grid_x = (int)(mlx->player->x_ply / TILE_SIZE);
	map_grid_y = (int)((new_y + margin * (move_y > 0 ? 1 : -1)) / TILE_SIZE);
	if (mlx->data->map[map_grid_y][map_grid_x] != '1')
		mlx->player->y_ply = new_y;
}


void    hook(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->player->rot == 1) // rotate right
		rotation_player(mlx, 1);
	if (mlx->player->rot == -1) // rotate left
		rotation_player(mlx, 0);

	double move_speed = PLAYER_SPEED;
	move_x = 0;
	move_y = 0;

	if (mlx->player->u_d == 1) // move forward
	{
		move_x += mlx->player->dir_x * move_speed;
		move_y += mlx->player->dir_y * move_speed;
	}
	if (mlx->player->u_d == -1) // move backward
	{
		move_x -= mlx->player->dir_x * move_speed;
		move_y -= mlx->player->dir_y * move_speed;
	}
	if (mlx->player->l_r == 1) // move right (strafe)
	{
		move_x += mlx->player->plane_x * move_speed;
		move_y += mlx->player->plane_y * move_speed;
	}
	if (mlx->player->l_r == -1) // move left (strafe)
	{
		move_x -= mlx->player->plane_x * move_speed;
		move_y -= mlx->player->plane_y * move_speed;
	}
	move_player(mlx, move_x, move_y);
}

int charset(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
		return (2);
	return (0);
}

int	check_char(t_data *data)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (charset(data->map[i][j]) == 1)
				;
			else if (charset(data->map[i][j]) == 2)
				count++;
			else
				return (0);
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int is_wall_or_space(char c) {
	return (c == '1' || c == ' ' || c == '\0');
}

void free_map(char **map, int height)
{
	int i;

	i = 0;
	while (i < height)
		free(map[i++]);
	free(map);
}

char **copy_map(char **map, int height)
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


int	find_max_len(char **map)
{
	int	i;
	int	max_len;
	int	len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}


int	find_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if (y_m >= mlx->data->h_size || x_m >= (int)ft_strlen(mlx->data->map[y_m]))
	return (0);
	if (mlx->data->map[y_m] && x_m <= (int)ft_strlen(mlx->data->map[y_m]))
		if (mlx->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

void	cast_ray(t_mlx *mlx)
{
	int	ray;

	ray = 0;
	while (ray < W_S)
	{
		double camera_x = 2 * ray / (double)W_S - 1;
		double ray_dir_x = mlx->player->dir_x + mlx->player->plane_x * camera_x;
		double ray_dir_y = mlx->player->dir_y + mlx->player->plane_y * camera_x;

		mlx->ray->wall_flag = 0;

		int map_x = (int)(mlx->player->x_ply / TILE_SIZE);
		int map_y = (int)(mlx->player->y_ply / TILE_SIZE);

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		int step_x, step_y;
		double side_dist_x, side_dist_y;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (mlx->player->x_ply / TILE_SIZE - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - mlx->player->x_ply / TILE_SIZE) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (mlx->player->y_ply / TILE_SIZE - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - mlx->player->y_ply / TILE_SIZE) * delta_dist_y;
		}

		mlx->ray->ray_dir_x = ray_dir_x;
		mlx->ray->ray_dir_y = ray_dir_y;
		int hit = 0;
		int side;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (mlx->data->map[map_y][map_x] == '1')
				hit = 1;
		}

		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - mlx->player->x_ply / TILE_SIZE + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - mlx->player->y_ply / TILE_SIZE + (1 - step_y) / 2) / ray_dir_y;

		mlx->ray->distance = perp_wall_dist * TILE_SIZE;
		mlx->ray->wall_flag = side;

		// Rendre le mur
		render_wall(mlx, ray);

		ray++;
	}
}

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
	// printf("Ray: %d, c_pix: %d, f_pix: %d, Couleur: %06X\n", ray, c_pix, f_pix, color);
	while (c_pix < f_pix)
		put_pixel(mlx, ray, c_pix++, color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int get_pixel_from_texture(t_texture *texture, int x, int y)
{
	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	
	char *pixel = texture->addr + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

void init_textures(t_mlx *mlx)
{
	mlx->textures = malloc(sizeof(t_texture) * 4);
	if (!mlx->textures)
		return;
	
	load_texture(mlx, mlx->data->north_texture, &mlx->textures[0]);
	load_texture(mlx, mlx->data->south_texture, &mlx->textures[1]);
	load_texture(mlx, mlx->data->west_texture, &mlx->textures[2]);
	load_texture(mlx, mlx->data->east_texture, &mlx->textures[3]);
}

void draw_textured_wall(t_mlx *mlx, int ray, int start, int end)
{
	int line_height = end - start;

	double wall_x;
	if (mlx->ray->wall_flag == 0)
		wall_x = mlx->player->y_ply + mlx->ray->distance * mlx->ray->ray_dir_y;
	else
		wall_x = mlx->player->x_ply + mlx->ray->distance * mlx->ray->ray_dir_x;
	wall_x = fmod(wall_x, TILE_SIZE);
	
	t_texture *current_texture;
	if (mlx->ray->wall_flag == 0)
	{
		if (mlx->ray->ray_dir_x > 0)
			current_texture = &mlx->textures[3];
		else
			current_texture = &mlx->textures[2];
	}
	else
	{
		if (mlx->ray->ray_dir_y > 0)
			current_texture = &mlx->textures[1];
		else
			current_texture = &mlx->textures[0];
	}
	
	int tex_x = (int)(wall_x * current_texture->width / TILE_SIZE);
	if ((mlx->ray->wall_flag == 0 && mlx->ray->ray_dir_x < 0) ||
		(mlx->ray->wall_flag == 1 && mlx->ray->ray_dir_y < 0))
		tex_x = current_texture->width - tex_x - 1;
	
	double step = (double)current_texture->height / line_height;
	double tex_pos = (start - H_S / 2 + line_height / 2) * step;

	int y = start;
	while (y < end)
	{
		int tex_y = (int)tex_pos & (current_texture->height - 1);
		tex_pos += step;
		unsigned int color = get_pixel_from_texture(current_texture, tex_x, tex_y);
		put_pixel(mlx, ray, y, color);
		y++;
	}
}

void render_wall(t_mlx *mlx, int ray)
{
	double wall_h = (TILE_SIZE / mlx->ray->distance) * ((W_S / 2) / tan(mlx->player->fov_rd / 2));
	
	int start = (H_S / 2) - (wall_h / 2);
	int end = (H_S / 2) + (wall_h / 2);
	
	if (end > H_S)
		end = H_S - 1;
	if (start < 0)
		start = 0;
	
	draw_floor(mlx, ray, start, end);
	
	draw_textured_wall(mlx, ray, start, end);
}


void load_texture(t_mlx *mlx, char *path, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(mlx->mlx, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error loading texture: %s\n", path);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}

int find_player_position(t_data *data)
{
    int i = 0;
    while (i < data->h_size)
	{
        int j = 0;
        while (j < data->w_size)
		{
            char c = data->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
                data->p_x = j;
                data->p_y = i;
                data->p_dir = c;
                data->map[i][j] = '0';
                return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

int check_map_closed(t_data *data)
{
    int i = 0;

    while (i < data->w_size)
	{
        if (data->map[0][i] != '1' || data->map[data->h_size - 1][i] != '1')
		{
            return 1;
        }
        i++;
    }

    i = 0;

    while (i < data->h_size)
	{
        if (data->map[i][0] != '1' || data->map[i][data->w_size - 1] != '1')
		{
            return 1;
        }
        i++;
    }

    return 0;
}



t_data *init_argument(char *filename)
{
	t_data *data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Erreur d'allocation mémoire pour data");
		return NULL;
	}
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		free(data);
		return NULL;
	}
	char **map = NULL;
	int map_size = 0;
	char *line;
	while ((line = get_next_line(fd)))
	{
		map = realloc(map, sizeof(char *) * (map_size + 1));
		if (!map)
		{
			perror("Erreur d'allocation mémoire pour la map");
			free(data);
			close(fd);
			return NULL;
		}
		map[map_size++] = line;
	}
	close(fd);
	map = realloc(map, sizeof(char *) * (map_size + 1));
	map[map_size] = NULL;
	data->map = map;
	data->w_size = find_max_len(map);
	data->h_size = map_size;

	return data;
}

void skip_empty_lines(FILE *file)
{
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), file))
	{
		if (buffer[0] != '\n')
		{
			fseek(file, -strlen(buffer), SEEK_CUR);
			break;
		}
	}
}

int read_color(char *line, int *color)
{
	char *ptr = strchr(line, ' ');
	if (ptr == NULL) return 0;
	ptr++;
	sscanf(ptr, "%d,%d,%d", &color[0], &color[1], &color[2]);
	return 1;
}

int read_texture(char *line, char **texture_path)
{
	char *ptr = strchr(line, ' ');
	if (ptr == NULL) return 0;
	
	while (*ptr == ' ') ptr++;
	
	char *newline = strchr(ptr, '\n');
	if (newline) *newline = '\0';
	
	char *end = ptr + strlen(ptr) - 1;
	while (end > ptr && (*end == ' ' || *end == '\n' || *end == '\r'))
		*end-- = '\0';
	
	*texture_path = strdup(ptr);
	return 1;
}

int read_scene_elements(FILE *file, t_data *data)
{
	char line[1024];
	skip_empty_lines(file);
	
	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == '\0' || line[0] == '\n')
			continue;

		if (strncmp(line, "NO", 2) == 0)
			read_texture(line, &data->north_texture);
		else if (strncmp(line, "SO", 2) == 0)
			read_texture(line, &data->south_texture);
		else if (strncmp(line, "WE", 2) == 0)
			read_texture(line, &data->west_texture);
		else if (strncmp(line, "EA", 2) == 0)
			read_texture(line, &data->east_texture);
		else if (strncmp(line, "F", 1) == 0)
			read_color(line, data->floor_color);
		else if (strncmp(line, "C", 1) == 0)
			read_color(line, data->ceiling_color);
		else
			break;
	}

	return 1;
}

int read_map(FILE *file, t_data *data)
{
	char line[1024];
	char **map = NULL;
	int map_size = 0;

	skip_empty_lines(file);

	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == '\0' || line[0] == '\n')
			continue;
		
		map = realloc(map, sizeof(char *) * (map_size + 1));
		if (!map) return 0;
		map[map_size++] = strdup(line);
	}
	
	map = realloc(map, sizeof(char *) * (map_size + 1));
	map[map_size] = NULL;

	data->map = map;
	data->h_size = map_size;
	data->w_size = strlen(map[0]);

	return 1;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <fichier.cub>\n", argv[0]);
		return 1;
	}

	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		perror("Erreur d'ouverture du fichier");
		return 1;
	}

	t_data data = {0};

	if (!read_scene_elements(file, &data))
	{
		printf("Erreur dans la lecture des éléments de la scène\n");
		fclose(file);
		return 1;
	}

	if (!read_map(file, &data))
	{
		printf("Erreur dans la lecture de la carte\n");
		fclose(file);
		return 1;
	}

	if (!check_map_closed(&data))
	{
		printf("La carte n'est pas fermée\n");
		fclose(file);
		return 1;
	}

	if (!find_player_position(&data))
	{
		printf("Position du joueur introuvable\n");
		fclose(file);
		return 1;
	}

	printf("Carte valide ! Position du joueur : (%d, %d), orientation : %c\n", data.p_x, data.p_y, data.p_dir);

	start_the_game(&data);

	fclose(file);
	return 0;
}
