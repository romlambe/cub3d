/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:15:17 by romlamb           #+#    #+#             */
/*   Updated: 2024/12/03 13:22:04 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *big, int c)
{
	while (*big && *big != (char)c)
	{
		big++;
	}
	if (*big == (char)c)
		return ((char *)big);
	else
		return (NULL);
}

int	ft_strchr_i(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i++])
		if (str[i] == c)
			return(i);
	return (i);
}

/*#include <stdio.h>

int main()
{
	char *str = "tripouille";
	printf("%d\n", printf("%s\n", ft_strchr(str, 't' + 256)));
	printf("%d\n", printf("%s\n", strchr(str, 't' + 256)));
	return 0;
}*/
