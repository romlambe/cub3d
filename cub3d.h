/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:15:20 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/16 12:48:55 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"

# define H_S 500
# define W_S 1000
# define TILE_SIZE 30
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define FOV 60

typedef struct	s_player
{
	int	x_ply;
	int	y_ply;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}				t_player;

typedef struct	s_ray
{
	double	ray_ngl;
	double	distance;
	int		wall_flag;

}				t_ray;

typedef struct	s_data
{
	char	**map;
	int		p_x;
	int		p_y;
	int		w_size; //longueur map[i][j]
	int		h_size; //largueur map[i]
	char	*name;
	int		max_len;
	int		height;
}t_data;

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		lenght_line;
	int		endian;

}				t_image;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	t_player	*player;
	t_ray		*ray;
	t_data		*data;
	t_image		*image;
}t_mlx;

//Parsing//
int charset(char c);
int	check_char(t_data *data);
int available_name(t_data *data);
int is_wall_or_space(char c);
void free_map(char **map, int height);
char **copy_map(char **map, int height);
int flood_fill(char **map, int x, int y, int max_len, int height);
int	find_max_len(char **map);
int	find_map_height(char **map);
int	is_map_closed(char **map);
int	search_player_pos(t_data *data);



//Initialisation//
void	start_the_game(t_data *data);
int	game_loop(void *ml);
void	init_player(t_mlx *mlx);
t_data	*init_argument(char **av);


//Ray Casting//
void	cast_ray(t_mlx *mlx);
float	nor_angle(float angle);
float	get_vertical_inter(t_mlx *mlx, float angle);
float	get_horizontal_inter(t_mlx *mlx, float angle);
int		wall_hit(float x, float y, t_mlx *mlx);
int		inter_chek(float angle, float *inter, float *step, int is_horizon);
int		unit_circle(float angle, char c);

//Render//
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	draw_floor(t_mlx *mlx, int ray, int c_pix, int f_pix);
int		get_texture(t_mlx *mlx, int flag);
void	draw_wall(t_mlx *mlx, int ray, int f_pix, int c_pix);
void	render_wall(t_mlx *mlx, int ray);

#endif

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/X.h>
# elif __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif


