/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:15:20 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/12 16:08:16 by romlambe         ###   ########.fr       */
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
	int		w_size; //wight map
	int		h_size; //height map
	char	*name;
	int		max_len;
	int		height;
}t_data;

typedef struct	s_mlx
{
	// mlx_image_t *img;
	// mlx_t		*mlx;
	t_player	*player;
	t_ray		*ray;
	t_data		*data;
}t_mlx;

#endif

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/X.h>
# elif __APPLE__
#  include <ApplicationServices/ApplicationServices.h>
# endif


