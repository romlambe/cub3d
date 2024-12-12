/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:17:24 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 23:06:25 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	skip_line(char *line)
{
	if (line[0] == '\n' && line[1] == '\0')
		return (free(line), 1);
	return (0);
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

int	allocate_map(t_data *data, int rows, int columns)
{
	int	i;

	i = 0;
	data->map = malloc(sizeof(char *) * (rows + 1));
	if (!data->map)
		return (printf("Error: memories\n"), 1);
	while (i < rows)
	{
		data->map[i] = malloc(sizeof(char) * (columns + 1));
		if (!data->map[i])
			return (printf("Error: memories columns\n"), 1);
		i++;
	}
	data->map[rows] = 0;
	return (0);
}

int	find_max_len(int fd)
{
	int		len;
	int		max_len;
	char	*line;

	max_len = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > max_len)
			max_len = len;
		free(line);
		line = get_next_line(fd);
	}
	return (max_len);
}

int	find_max_height(char *filename)
{
	int		line_count;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line_count = 0;
	line = get_next_line(fd);
	if (fd == -1)
		return (-1);
	while (line)
	{
		if (*line && (*line == '1' || *line == '0' || *line == '\t'
				|| *line == ' '))
			line_count++;
		free (line);
		line = get_next_line(fd);
	}
	return ((void)close(fd), line_count);
}
