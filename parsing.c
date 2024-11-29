/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:33:42 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/29 16:36:24 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void read_file(const char *filename, t_data *data)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur ouverture fichier");
		return (NULL);
	}
	char **lines = NULL;
	char *line = NULL;
	int line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		char **temp = realloc(lines, (line_count + 1) * sizeof(char *));
		if (!temp)
		{
			perror("Erreur allocation mémoire");
			free(line);
			break;
		}
		lines = temp;
		lines[line_count++] = line;
	}
	char **final = realloc(lines, (line_count + 1) * sizeof(char *));
	if (final)
	{
		lines = final;
		lines[line_count] = NULL;
	}
	close(fd);
	data->file_content = lines;
}

void read_textures(char **file_content, t_data *data)
{
	if (!file_content || !data)
		return;
	if (file_content[0])
		data->north_texture = strdup(file_content[0] + 3);
	if (file_content[1])
		data->south_texture = strdup(file_content[1] + 3);
	if (file_content[2])
		data->west_texture = strdup(file_content[2] + 3);
	if (file_content[3])
		data->east_texture = strdup(file_content[3] + 3);
	if (!data->north_texture || !data->south_texture ||
		!data->west_texture || !data->east_texture)
	{
		perror("Erreur allocation mémoire pour une ou plusieurs textures");
		free(data->north_texture);
		free(data->south_texture);
		free(data->west_texture);
		free(data->east_texture);
		return;
	}
}

void parse_color(const char *line, int *color)
{
	int i = 0, j = 0;
	char buffer[4];
	while (*line && i < 3)
	{
		j = 0;
		while (*line && *line != ',' && j < 3)
		{
			buffer[j++] = *line++;
		}
		buffer[j] = '\0';
		color[i++] = atoi(buffer);
		if (*line == ',')
			line++;
	}
}

void read_color_fc(char **file_content, t_data *data)
{
	if (file_content[4])
	{
		parse_color(file_content[4] + 2, data->floor_color);
	}

	if (file_content[5])
	{
		parse_color(file_content[5] + 2, data->ceiling_color);
	}
}

void read_map(char **file_content, t_data *data)
{
	int i = 7;
	int map_lines = 0;
	while (file_content[i])
	{
		map_lines++;
		i++;
	}
	data->h_size = map_lines;
	data->map = (char **)malloc((map_lines + 1) * sizeof(char *));
	if (!data->map)
		return;
	i = 7;
	int j = 0;
	while (file_content[i])
	{
		data->map[j] = strdup(file_content[i]);
		i++;
		j++;
	}
	data->map[j] = NULL;
}

void width_map(char **map, t_data *data)
{
	int i;
	int len;
	int max;

	i = 0;
	len = 0;
	max = 0;
	while (map[i])
	{
		len = strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	data->w_size = max;
}

void init_map(const char *filename, t_data *data)
{
	if (!filename || !data)
		return;
	read_file(filename, data);
	if (!data->file_content)
	{
		perror("Erreur lors de la lecture du fichier");
		return;
	}
	read_textures(data->file_content, data);
	read_color_fc(data->file_content, data);
	read_map(data->file_content, data);
	width_map(data->map, data);
}
