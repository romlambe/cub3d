/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:39:31 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 23:38:54 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	get_nb_parts(char *str, char c)
{
	size_t	nb_parts;
	size_t	i;

	if (str[0] == 0)
		return (0);
	if (ft_strlen(str) == 1)
		return (1);
	i = 1;
	nb_parts = 0;
	while (str[i] != 0)
	{
		if ((str[i] == c && str[i - 1] != c)
			|| (str[i + 1] == 0 && str[i] != c))
		{
			nb_parts++;
		}
		i++;
	}
	return (nb_parts);
}

char	**init_parts(char *str, char c)
{
	char	**parts;
	int		nb_parts;

	nb_parts = get_nb_parts(str, c);
	parts = (char **) ft_calloc(nb_parts + 1, sizeof(char *));
	return (parts);
}

void	fill_part(char *str, char *part, int part_len, int *start)
{
	int	og_pl;

	if (!str[0])
		return ;
	og_pl = part_len;
	while (--part_len >= 0)
		part[part_len] = str[*start + part_len];
	*start += og_pl;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	int		current_part;
	char	**parts;

	i = 0;
	current_part = 0;
	start = 0;
	parts = init_parts((char *) s, c);
	while (parts && current_part < get_nb_parts((char *) s, c))
	{
		if (s[i] == c)
			start++;
		if ((s[i] != c && s[i + 1] == c)
			|| !s[i + 1])
		{
			parts[current_part] = (char *) ft_calloc(i + 1 - start + 1, 1);
			if (!parts[current_part])
				return (free_parts(parts));
			fill_part((char *) s, parts[current_part], i + 1 - start, &start);
			current_part++;
		}
		i++;
	}
	return (parts);
}
