/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:13:52 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/03 17:11:46 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *copy, size_t size)
{
	size_t	i;
	char	*res;

	i = 0;
	res = ft_calloc(size + 1, 1);
	while (i < size && copy[i])
	{
		res[i] = copy[i];
		i++;
	}
	return (res);
}
