/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:21:47 by romlambe          #+#    #+#             */
/*   Updated: 2024/11/19 03:15:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	int		len;
	char	*array;

	i = 0;
	len = ft_strlen_gnl(s2);
	if (!s1)
		return (ft_strndup(s2, len));
	len = len + ft_strlen_gnl(s1);
	array = (char *)malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	len = 0;
	while (s1[i])
		array[len++] = s1[i++];
	i = 0;
	while (s2[i])
		array[len++] = s2[i++];
	array[len] = '\0';
	free(s1);
	return (array);
}

int	ft_strchr_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	if (str[i] == '\n')
		return (1);
	return (0);
}

char	*ft_strndup(char *str, int size)
{
	int		i;
	char	*dest;

	i = 0;
	if (!str || !size)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*to_write(char **stack)
{
	char	*temp;
	char	*dest;
	int		i;

	i = 0;
	if (!*stack)
		return (NULL);
	temp = *stack;
	while (temp[i] != '\n' && temp[i])
		i++;
	if (temp[i] == '\n')
		i++;
	dest = ft_strndup(temp, i);
	*stack = ft_strndup(temp + i, ft_strlen_gnl(temp + i));
	free(temp);
	return (dest);
}
