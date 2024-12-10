/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:33:19 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 23:37:41 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	get_parts_size(char **parts)
{
	int	i;

	if (!parts || !*parts)
		return (0);
	i = 0;
	while (parts[i])
		i++;
	return (i);
}

void	print_parts(char **parts)
{
	int	i;

	i = -1;
	if (!parts)
		return ;
	while (parts[++i])
		printf("%s\n", parts[i]);
}

char	**free_parts(char **parts)
{
	size_t	i;

	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
	parts = 0;
	return (0);
}
