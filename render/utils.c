/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:08:37 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 23:29:48 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	int_abs(int value)
{
	if (value < 0)
		return (-value);
	else
		return (value);
}

int	close_window(t_data *data)
{
	free_data(data);
	// free_tab(data->map);
	return (exit(0), 0);
}
