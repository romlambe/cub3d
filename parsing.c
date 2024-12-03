/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:15:15 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/03 14:46:04 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// testing char of the map

#include "cub3d.h"

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

int available_name(t_data *data)
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



int	is_map_closed(char **map)
{
	int	max_len;
	int	height;
	char **map_copy;
	int	x;
	int	y;

	max_len = find_max_len(map);
	height = find_map_height(map);
	map_copy = copy_map(map, height);
	if (!map_copy)
		return (printf("Error copy map"), 0);
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < max_len)
		{
			if (map[y][x] == '0')
			{
				if (!flood_fill(map_copy, x, y, max_len, height))
					return(free_map(map_copy, height), 0);
			}
		}
	}
	return (free_map(map_copy, height), 1);
}

int	search_player_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == 'E' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'N' || data->map[i][j] == 'W')
			{
			data->p_x = j;
			data->p_y = i;
			return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int main(int ac, char **av) {

	t_data *data;

	(void)ac;
	data = init_argument(av);
	if (search_player_pos(data) == 1)
		return 1;
	for (int i = 0; i < data->h_size; i++)
		printf("%s\n", data->map[i]);
	printf("p_x: %d\np_y: %d\nname: %s\n", data->p_x, data->p_y, data->name);

	if (check_char(data) == 0)
		printf("pb\n");

	// // Tester si la carte est fermée
	if (is_map_closed(data->map)) {
		printf("La carte est fermée.\n");
	} else {
		printf("La carte n'est pas fermée.\n");
		return 0;
	}
	start_the_game(data);


	return 0;
}

