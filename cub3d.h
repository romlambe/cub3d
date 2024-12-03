/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:15:20 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/03 15:59:27 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"

// # define H_S 500
// # define W_S 1000
# define TILE_SIZE 30
# define ROTATION_SPEED 3.5
# define PLAYER_SPEED 7.5
# define FOV 60

# define KEY_Z 122
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_A 97
# define LEFT 65361
# define RIGHT 65363

struct s_data;

typedef struct	s_player
{
	float	x_ply;
	float	y_ply;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	int		move_x;
	int		move_y;
	// float	angle;
	// float	fov_rd;
	// int		rot;
	// int		l_r;
	// int		u_d;
}			t_player;

typedef struct s_image
{
    void    *img;           // Pointeur vers l'image MLX
    char    *addr;          // Adresse des données de l'image
    int     bpp;           // Bits par pixel
    int     size_line;     // Taille de la ligne
    int     endian;        // Endianness
    int     width;          // Largeur de la texture
    int     height;         // Hauteur de la texture
	struct s_data *data;
} t_image;


typedef struct s_assets
{
	t_image	n_texture;
	t_image	s_texture;
	t_image	e_texture;
	t_image	w_texture;
	int			f_color[3];
	int			c_color[3];
}	t_assets;


typedef struct sprite
{
	int	state;
	float	x;
	float	y;
	t_image	texture;
}	t_sprite;

typedef struct s_sprite
{
	float dist;
	int order;
}	t_sprite_sort;

typedef struct s_sprite_transform
{
	float	sprite_x;
	float	sprite_y;
	float	int_dev;
	float	transform_x;
	float	transform_y;
	int		sprite_screen_x;
	int		v_move_screen;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
}	t_sprite_transform;

typedef struct	s_data
{
    char **map;
	float	zbuffer[800];
	t_player	player;
	t_assets	assets;
	t_sprite	*sprites;
	void	*mlx;
	void	*mlx_win;
    int		win_width;
    int		win_height;
	int		mouse_x;
	int		n_sprites;
	long long	fps;
	long long	time;
	long long	old_fps;
	double		deltatime;
	char		file_content;


    // int p_x;
    // int p_y;
    // char p_dir;
    // char *north_texture;
    // char *south_texture;
    // char *west_texture;
    // char *east_texture;
    // int floor_color[3];
    // int ceiling_color[3];
}	t_data;


typedef struct s_queue_node
{
	int					value;
	int					x;
	int					y;
	struct s_queue_node	*next;
}t_queue_node;

typedef struct s_queue
{
	t_queue_node	*front;
	t_queue_node	*rear;
}t_queue;

typedef struct s_draw_wall{
	int	line_height;
	int	start_y;
	int	end_y;
	float	h;
	int	color;
	t_image *texture;
	float	wall_x;
	int		tex_x;
	float	step;
	float	tex_pos;
} t_draw_wall;


typedef struct	s_ray
{
	float	ray_dir_x; // Ajouter cette ligne
	float	ray_dir_y; // Ajouter cette ligne
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	float	wall_xoffset;
	float	wall_yoffset;
	int		side;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;

	// float	ray_ngl;
	// float	distance;
}			t_ray;



// typedef struct	s_image
// {
// 	void	*img;
// 	char	*addr;
// 	int		bit_per_pixel;
// 	int		lenght_line;
// 	int		endian;
// }				t_image;

// typedef struct	s_mlx
// {
// 	void		*mlx;
// 	void		*win;
// 	void		*img;
// 	t_player	*player;
// 	t_ray		*ray;
// 	t_data		*data;
// 	t_image		*image;
// 	t_texture	*textures;
// 	t_draw_wall *wall;
// 	t_assets	assets;
// }t_mlx;

//Parsing//
int charset(char c);
int	check_char(t_data *data);
// int available_name(t_data *data);
int is_wall_or_space(char c);
void free_map(char **map, int height);
// char **copy_map(char **map, int height);
int flood_fill(char **map, int x, int y, int max_len, int height);
int	find_max_len(char **map);
int	find_map_height(char **map);
// int	is_map_closed(char **map);
int	search_player_pos(t_data *data);



//Initialisation//
// void	start_the_game(t_data *data);
// int	game_loop(void *ml);
// void	init_player(t_mlx *mlx);
// t_data *init_argument(char *filename);

//Ray Casting//
// void	cast_ray(t_mlx *mlx);
// float	nor_angle(float angle);
// float	get_vertical_inter(t_mlx *mlx, float angle);
// float	get_horizontal_inter(t_mlx *mlx, float angle);
// int		wall_hit(float x, float y, t_mlx *mlx);
// int		inter_chek(float angle, float *inter, float *step, int is_horizon);
// int		unit_circle(float angle, char c);

//Render//
// void	put_pixel(t_mlx *mlx, int x, int y, int color);
// void	draw_floor(t_mlx *mlx, int ray, int c_pix, int f_pix);
// int		get_texture(t_mlx *mlx);
// void	draw_wall(t_mlx *mlx, int ray, int f_pix, int c_pix);
// void	render_wall(t_mlx *mlx, int ray);

//Movement//
// int	ft_reles(int keycode, t_mlx *mlx);
// int	keypress(int keycode, void *ml);
// void	rotation_player(t_mlx *mlx, int i);
// void	move_player(t_mlx *mlx, double move_x, double move_y);
// void	hook(t_mlx *mlx, double move_x, double move_y);


// void            init_textures(t_mlx *mlx);
// void            load_texture(t_mlx *mlx, char *path, t_texture *texture);
// unsigned int    get_pixel_from_texture(t_texture *texture, int x, int y);
// void            draw_textured_wall(t_mlx *mlx, int ray, int start, int end);

#endif

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/X.h>
# elif __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif


