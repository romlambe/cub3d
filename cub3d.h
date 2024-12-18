/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:15:20 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/18 16:17:29 by romlambe         ###   ########.fr       */
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

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/X.h>
# elif __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif

# define TILE_SIZE 30
# define ROTATION_SPEED 30
# define PLAYER_SPEED 5
# define FOV 60

# define CROSSHAIR_SIZE 10

# define KEY_ESC 65307
# define KEY_Z 122
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_A 97
# define LEFT 65361
# define RIGHT 65363

struct	s_data;

typedef struct s_player
{
	float	x_ply;
	float	y_ply;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	int		move_x;
	int		move_y;
}	t_player;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	struct s_data	*data;
}	t_image;

typedef struct s_assets
{
	t_image		n_texture;
	t_image		s_texture;
	t_image		e_texture;
	t_image		w_texture;
	int			f_color[3];
	int			c_color[3];
}	t_assets;

typedef struct sprite
{
	int			state;
	float		x;
	float		y;
	t_image		texture;
}	t_sprite;

typedef struct s_sprite
{
	float		dist;
	int			order;
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

typedef struct s_data
{
	char		**map;
	float		zbuffer[800];
	t_player	player;
	t_assets	assets;
	t_sprite	*sprites;
	void		*mlx;
	void		*mlx_win;
	int			win_width;
	int			win_height;
	int			mouse_x;
	int			n_sprites;
	long long	fps;
	long long	time;
	long long	old_fps;
	double		deltatime;
	char		file_content;
	int			map_height;
	int			map_width;
	unsigned char			*cloud_texture;
}	t_data;

typedef struct s_queue_node
{
	int					value;
	int					x;
	int					y;
	struct s_queue_node	*next;
}	t_queue_node;

typedef struct s_queue
{
	t_queue_node	*front;
	t_queue_node	*rear;
}	t_queue;

typedef struct s_draw_wall
{
	int			line_height;
	int			start_y;
	int			end_y;
	float		h;
	int			color;
	t_image		*texture;
	float		wall_x;
	int			tex_x;
	float		step;
	float		tex_pos;
}	t_draw_wall;

typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
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
}			t_ray;

// COPY MAP //
int				copy_color(t_data *data, char **split_color, char *color);
int				copy_map(t_data *data, char *filename);
int				copy_assets(t_data *data, char **split_line);

// MANAGE MAP //
char			**copy_map_flood(char **map, int height);
int				flood_fill(char **map, int x, int y, t_data *data);
int				is_wall_or_space(char c);
int				is_map_closed(t_data *data);
int				available_name(char *name);

// PARSING MAP //
int				parsing_map_assets(t_data *data, int fd);
int				parsing_map_colors(t_data *data, int fd);
int				parsing_map(t_data *data, int fd, char *filename);
int				parser(t_data *data, char **av);

// UTILS PARSING //
int				skip_line(char *line);
char			**trim_color(char **split_color);
int				allocate_map(t_data *data, int rows, int columns);
int				find_max_len(int fd);
int				find_max_height(char *filename);

// CHECKER //
void			check_side(t_ray *ray, int axis);
void			check_hit_wall(t_ray *ray, t_data *data, t_player *player);
int				check_assets(t_data *data, int fd);

// DRAWER //
void			draw_sprite_stripes(t_data *data, t_image *img,
					t_sprite_transform *transform, int sprite_index);
void			draw_sprite_stripe(t_image *img, t_sprite_transform *transform,
					int sprite_index, int stripe);
void			draw_stripe(t_ray *ray, t_image *image, int x,
					t_player *player);
void			draw_wall_stripe(t_draw_wall *wall, t_image *img, int x);
void			draw_floor_ceilling(t_image *image, int x);

// FRYER //
void			free_map(char **map, int height);
void			free_assets(t_data *data);
void			free_data(t_data *data);
void			free_tab(char **tab);

// INITIALISATION //
void			init_player(t_data *data, char direction, int y, int x);
void			init_assets(t_assets *assets);
void			init_data(t_data *data);

// MANAGER //
int				manage_mouse(int x, int y, t_data *data);
void			manage_right_camera_mov(t_player *player, double dt);
void			manage_left_camera_mov(t_player *player, double dt);
int				manage_input_release(int keycode, t_data *data);
int				manage_input_press(int keycode, t_data *data);

// MLX_UTILS //
void			draw_pixel(t_image *img, int x, int y, int color);
int				get_pixel_color(t_image *texture, int x, int y);
int				is_color_is_correct(int r, int g, int b);
int				rgba(int r, int g, int b, int a);
int				rgb(int r, int g, int b);

// MOVEMENT //
void			manage_forward_movement(char **map, t_player *player, int move,
					double dt);
void			manage_strafe_movement(char **map, t_player *player, int move,
					double dt);
void			set_player_direction(t_player *player, char direction);
int				search_player_pos(t_data *data);
int				update_loop(t_data *data);

// RENDER RAY //
void			calculate_side_dist(t_ray *ray, t_player *player);
void			calculate_ray_distance(t_ray *ray, t_player *player,
					float cameraX);
void			calc_perp_wall_dist(t_ray *ray, t_data *data);

// RENDER //
void			draw_sprite(t_data *data, t_image *img);
void			render_raycast(t_image *img, t_data *data, t_player *player);
int				render_cube(t_data *data);

// SPRITE MANAGER //
void			initialize_sprite_distance(t_data *data, int *sprite_order,
					float *sprite_distance);
void			sort_sprite(int *sprite_order, float *sprite_distance,
					int n_sprites);
void			sort_sprite_distance(t_data *data, int *sprite_order,
					float *sprite_distance);
void			calculate_transform_values(t_data *data,
					t_sprite_transform *transform, int sprite_order);
void			calculate_draw_dimensions(t_data *data,
					t_sprite_transform *transform);

// SPRITES //
t_sprite_sort	*create_sprite(int *sprite_order, float *sprite_distance,
					int n_sprites);
void			swap_sprites(t_sprite_sort *a, t_sprite_sort *b);
void			sort_sprite_array(t_sprite_sort *sprites, int n_sprites);
void			update_array(t_sprite_sort *sprites, int *order_sprite,
					float *sprite_distance, int n_sprites);

// TEXTURE //
t_image			*choose_texture(t_data *data, int side);
void			get_texture(t_data *data, char *path, t_image *texture);
void			switch_texture(t_data *data);

// UTILS //
long long		get_time(void);
int				int_abs(int value);
int				close_window(t_data *data);

void draw_crosshair(t_image *image, int center_x, int center_y);

#endif
