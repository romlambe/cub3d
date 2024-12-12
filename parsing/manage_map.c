/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:22:13 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/12 14:23:30 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// char	**copy_map_flood(char **copy, t_data *data)
// {
// 	int		i;

// 	i = 0;
// 	while (i < data->map_height)
// 	{
// 		copy[i] = ft_strncpy(data->map[i], ft_strlen(data->map[i]));
// 		if (!copy[i])
// 			return (free_tab(copy), NULL);
// 		printf("%s\n", copy[i]);
// 		i++;
// 	}
// 	return (copy);
// }

// char	**copy_map_flood(char **map, int height)
// {
// 	char	**copy;
// 	int		i;

// 	i = 0;
// 	copy = malloc(sizeof(char *) * (height + 1));
// 	if (!copy)
// 		return (printf("Can't copy the map"), NULL);
// 	while (i < height)
// 	{
// 		copy[i] = ft_strncpy(map[i], ft_strlen());
// 		if (!copy[i])
// 		{
// 			free_tab(copy);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	copy[height] = NULL;
// 	return (copy);
// }

int	flood_fill(char **map, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || y >= data->map_height || x >= data->map_width || data->map[y][x] == '\0')
		return (0);
	if (is_wall_or_space(map[y][x]))
		return (1);
	map[y][x] = ' ';
	if (!flood_fill(map, x + 1, y, data)
		|| !flood_fill(map, x - 1, y, data)
		|| !flood_fill(map, x, y - 1, data)
		|| !flood_fill(map, x, y + 1, data))
		return (0);
	return (1);
}

int	is_wall_or_space(char c)
{
	return (c == '1' || c == ' ' || c == '\0');
}

char	**allocate_map_flood(t_data *data)
{
	int		i;
	char	**copy;

	i = 0;
	copy = malloc(sizeof(char *) * (data->map_height + 1));
	if (!copy)
		return NULL;

	while (i < data->map_height)
	{
		copy[i] = malloc(sizeof(char) * (ft_strlen(data->map[i]) + 1));
		if (!copy[i])
		{
			while(i-- >0)
				free(copy[i]);
			return (free(copy), NULL);
		}
		copy[i] = ft_strncpy(data->map[i], ft_strlen(data->map[i]));
		i++;
	}
	copy[data->map_height] = 0;
	return copy;
}

int	is_map_closed(t_data *data)
{
	char	**map_copy;
	size_t	x;
	int		y;


	map_copy = allocate_map_flood(data);
	if (!map_copy)
		return (printf("Error copy map"), 0);
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < ft_strlen(data->map[y]))
		{
			if (data->map[y][x] == '0')
			{
				if (!flood_fill(map_copy, x, y, data))
					return (printf("Error: Map is not closed\n"),
						free_map(map_copy, data->map_height), 1);
			}
		}
	}
	return (free_tab(map_copy), 0);
}

int	available_name(char *name)
{
	int	start_pos;
	int	size_cub;
	int	size_string;

	size_cub = 4;
	size_string = ft_strlen(name);
	start_pos = size_string - size_cub;
	if (start_pos <= 0 || ft_strcmp(name + start_pos, ".cub"))
		return (1);
	return (0);
}
