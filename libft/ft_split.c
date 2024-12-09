/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:39:31 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/04 12:50:25 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// static int	verif_char(char c, char charset)
// {
// 	if (c == charset || c == 0)
// 		return (1);
// 	return (0);
// }

// static int	count_words(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	words;

// 	i = 0;
// 	words = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 	{
// 		if (verif_char(s[i + 1], c) && !(verif_char(s[i], c) || i == 0))
// 			words++;
// 		i++;
// 	}
// 	return (words);
// }

// static void	write_words(char const *s, char *dest, char c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (!verif_char(s[i], c))
// 	{
// 		dest[i] = s[i];
// 		i++;
// 	}
// 	dest[i] = 0;
// }

// static void	write_string(char **array, char *s, char c)
// {
// 	size_t	i;
// 	size_t	j;
// 	int		string;

// 	i = 0;
// 	string = 0;
// 	while (s[i])
// 	{
// 		if (verif_char(s[i], c))
// 			i++;
// 		else
// 		{
// 			j = 0;
// 			while (!verif_char(s[i], c))
// 			{
// 				j++;
// 				i++;
// 			}
// 			array[string] = (char *)malloc(sizeof(char) * (j + 1));
// 			write_words(s + i - j, array[string], c);
// 			string++;
// 		}
// 	}
// 	array[string] = 0;
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**array;
// 	int		words;

// 	if (!s)
// 		return (NULL);
// 	words = count_words(s, c);
// 	array = (char **)malloc(sizeof(char *) * (words + 1));
// 	if (!array)
// 		return (NULL);
// 	write_string(array, (char *)s, c);
// 	return (array);
// }
/*#include <stdio.h>
#include <stdlib.h>

int main() {
    char const *chaine = "Bonjour,comment,les amis,la famille,les collegues?";
    char c = ',';
	int	i;

	i = 0;
    char **resultat = ft_split(chaine, c);
    if (resultat)
	{
        while (resultat[i] != NULL)
		{
            printf("%s\n", resultat[i]);
            free(resultat[i]);
			i++;
        }
        free(resultat);
    }

    return 0;
}*/

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

static int	get_nb_parts(char *str, char c)
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

static char	**init_parts(char *str, char c)
{
	char	**parts;
	int		nb_parts;

	nb_parts = get_nb_parts(str, c);
	parts = (char **) ft_calloc(nb_parts + 1, sizeof(char *));
	return (parts);
}

static void	fill_part(char *str, char *part, int part_len, int *start)
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
