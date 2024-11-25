/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:26:40 by romlambe          #+#    #+#             */
/*   Updated: 2024/11/19 05:47:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	empty_map(t_data *data, const char *file)
{
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		data->map = NULL;

	}
}
