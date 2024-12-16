/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:16:55 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/13 16:46:19 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		line_split = ft_split(line, " \t");
		free (line);
		if (copy_assets(data, line_split) == 1)
			return (free_tab(line_split), 1);
		free_tab(line_split);
		i--;
	}
	return (check_assets(data, fd));
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
		split_line = ft_split(line, " \t");
		free(line);
		split_color = trim_color(split_line + 1);
		if (copy_color(data, split_color, split_line[0]) == 1)
			return (free_tab(split_line), free_tab(split_color),
				free_gnl(fd), 1);
		free_tab(split_line);
		free_tab(split_color);
		i--;
	}
	return (0);
}

int	parsing_map(t_data *data, int fd, char *filename)
{
	char	*line;
	int		i;

	i = -1;
	data->map_width = find_max_len(fd);
	data->map_height = find_max_height(filename);
	while (++i)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (skip_line(line) == 1)
		{
			if (i == 0)
				continue ;
			else
				return (free_gnl(fd), 1);
		}
		free(line);
	}
	if (data->map_height < 3 && data->map_width < 3)
		return (1);
	allocate_map(data, data->map_width, data->map_height);
	copy_map(data, filename);
	return (0);
}

int	parser(t_data *data, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return ((void)printf("Error: Can't open the map\n"), 1);
	if (parsing_map_assets(data, fd) == 1)
		return ((void)printf("Error: Assets isn't correctly set up\n"),
			(void)close(fd), 1);
	if (parsing_map_colors(data, fd) == 1)
		return ((void)printf("Error: Colors isn't correctly set up\n"),
			(void)close(fd), 1);
	if (parsing_map(data, fd, av[1]) == 1)
		return ((void)printf("Error: Map isn't correctly set up\n"),
			(void)close(fd), 1);
	close(fd);
	return (0);
}
