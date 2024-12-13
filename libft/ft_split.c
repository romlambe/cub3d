/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:39:31 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/13 15:18:07 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// static char	*hihi(const char	*str, int start, int end)
// {
// 	int		i;
// 	char	*cp;

// 	i = 0;
// 	cp = (char *) malloc(((end - start) + 1) * sizeof(char));
// 	while (start < end)
// 		cp[i++] = str[start++];
// 	cp[i] = 0;
// 	return (cp);
// }

// static int	ft_count(const char *str, char sep)
// {
// 	int	i;
// 	int	start;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		while (str[i] == sep && str[i])
// 			i++;
// 		start = i;
// 		while (str[i] != sep && str[i])
// 			i++;
// 		if (start != i)
// 			count++;
// 	}
// 	return (count);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**tab;
// 	int		i;
// 	int		start;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tab = (char **) malloc((ft_count(s, c) + 1) * sizeof(char *));
// 	if (!tab)
// 		return (0);
// 	while (s[i])
// 	{
// 		while (s[i] == c && s[i])
// 			i++;
// 		start = i;
// 		while (s[i] != c && s[i])
// 			i++;
// 		if (start != i)
// 			tab[j++] = hihi(s, start, i);
// 	}
// 	tab[j] = 0;
// 	return (tab);
// }

int	is_separator(char c, char *sep)
{
	int	i;

	i = -1;
	while (sep[++i])
		if (c == sep[i])
			return (1);
	return (0);
}

char	*ft_strdup_split(char	*str, int start, int end)
{
	int		i;
	char	*cp;

	i = 0;
	cp = (char *) malloc(((end - start) + 1) * sizeof(char));
	while (start < end)
		cp[i++] = str[start++];
	cp[i] = 0;
	return (cp);
}

int	ft_count(char *str, char *sep)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_separator(str[i], sep) && str[i])
			i++;
		start = i;
		while (!is_separator(str[i], sep) && str[i])
			i++;
		if (start != i)
			count++;
	}
	return (count);
}

char	**ft_split(char *str, char *charset)
{
	char	**tab;
	int		i;
	int		start;
	int		j;

	i = 0;
	j = 0;
	tab = (char **) malloc((ft_count(str, charset) + 1) * sizeof(char *));
	while (str[i])
	{
		while (is_separator(str[i], charset) && str[i])
			i++;
		start = i;
		while (!is_separator(str[i], charset) && str[i])
			i++;
		if (start != i)
			tab[j++] = ft_strdup_split(str, start, i);
	}
	tab[j] = 0;
	return (tab);
}
