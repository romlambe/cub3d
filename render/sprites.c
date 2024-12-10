/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:08:25 by romlambe          #+#    #+#             */
/*   Updated: 2024/12/10 23:11:09 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_sprite_sort	*create_sprite(int *sprite_order, float *sprite_distance,
	int n_sprites)
{
	int				i;
	t_sprite_sort	*sprites;

	sprites = (t_sprite_sort *)malloc(n_sprites * sizeof(t_sprite_sort));
	if (!sprites)
		return (NULL);
	i = 0;
	while (i < n_sprites)
	{
		sprites[i].dist = sprite_distance[i];
		sprites[i].order = sprite_order[i];
		i++;
	}
	return (sprites);
}

void	swap_sprites(t_sprite_sort *a, t_sprite_sort *b)
{
	t_sprite_sort	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_sprite_array(t_sprite_sort *sprites, int n_sprites)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_sprites - 1)
	{
		j = 0;
		while (j < n_sprites - i - 1)
		{
			if (sprites[j].dist < sprites[j + 1].dist)
				swap_sprites(&sprites[i], &sprites[j + 1]);
			j++;
		}
		i++;
	}
}

void	update_array(t_sprite_sort *sprites, int *order_sprite,
	float *sprite_distance, int n_sprites)
{
	int	i;

	i = 0;
	while (i < n_sprites)
	{
		sprite_distance[i] = sprites[i].dist;
		order_sprite[i] = sprites[i].order;
		i++;
	}
}
