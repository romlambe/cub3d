/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:26:01 by romlambe          #+#    #+#             */
/*   Updated: 2024/03/11 18:37:40 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *str);
char	*ft_strndup(char *str, int size);
char	*to_write(char **stack);
char	*get_next_line(int fd);

#endif
