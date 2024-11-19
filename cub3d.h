/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:15:20 by romlambe          #+#    #+#             */
/*   Updated: 2024/11/19 05:47:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"

# define H_S 500
# define W_S 1000
# define TILE_SIZE 30
# define ROTATION_SPEED 0.02
# define PLAYER_SPEED 0.5
# define FOV 90

# define KEY_Z 122
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_A 97
# define LEFT 65361
# define RIGHT 65363

typedef struct s_texture {
    void    *img;           // Pointeur vers l'image MLX
    char    *addr;          // Adresse des données de l'image
    int     width;          // Largeur de la texture
    int     height;         // Hauteur de la texture
    int     bpp;           // Bits par pixel
    int     size_line;     // Taille de la ligne
    int     endian;        // Endianness
} t_texture;

typedef struct	s_player
{
	double	x_ply;
	double	y_ply;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	double	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}			t_player;

typedef struct	s_ray
{
	double	ray_ngl;
	double	distance;
	int		wall_flag;
	double	ray_dir_x; // Ajouter cette ligne
	double	ray_dir_y; // Ajouter cette ligne
}			t_ray;

typedef struct	s_data
{
    char **map;
    int w_size;
    int h_size;
    int p_x;
    int p_y;
    char p_dir;
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int floor_color[3];
    int ceiling_color[3];
}	t_data;

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
	t_texture	*textures;
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
t_data *init_argument(char *filename);

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
int		get_texture(t_mlx *mlx);
void	draw_wall(t_mlx *mlx, int ray, int f_pix, int c_pix);
void	render_wall(t_mlx *mlx, int ray);

//Movement//
int	ft_reles(int keycode, t_mlx *mlx);
int	keypress(int keycode, void *ml);
void	rotation_player(t_mlx *mlx, int i);
void	move_player(t_mlx *mlx, double move_x, double move_y);
void	hook(t_mlx *mlx, double move_x, double move_y);


void            init_textures(t_mlx *mlx);
void            load_texture(t_mlx *mlx, char *path, t_texture *texture);
unsigned int    get_pixel_from_texture(t_texture *texture, int x, int y);
void            draw_textured_wall(t_mlx *mlx, int ray, int start, int end);

#endif

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/X.h>
# elif __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif


