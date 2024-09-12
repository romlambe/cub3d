/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:15:15 by romlambe          #+#    #+#             */
/*   Updated: 2024/09/12 16:46:08 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// testing char of the map

#include "cub3d.h"

int charset(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
		return (2);
	return (0);
}

int	check_char(t_data *data)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (charset(data->map[i][j]) == 1)
				j++;
			else if (charset(data->map[i][j]) == 2)
			{
				j++;
				count++;
			}
			else
				return (0);

		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int available_name(t_data *data)
{
	int start_pos;
	int size_cub;
	int size_string;

	size_cub = ft_strlen(".cub");
	size_string = ft_strlen(data->name);
	start_pos = size_string - size_cub;
	if (start_pos <= 0 || ft_strcmp(data->name + start_pos, ".cub"))
		return (0);
	return (1);
}
int is_wall_or_space(char c) {
	return (c == '1' || c == ' ' || c == '\0');
}

void free_map(char **map, int height)
{
	int i;

	i = 0;
	while (i < height)
		free(map[i++]);
	free(map);
}

char **copy_map(char **map, int height)
{
	char	**copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (printf("Can't copy the map"), NULL);
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_map(map, height);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

// Fonction de copie de la carte pour éviter de modifier l'originale
// char **copy_map(char **map, int height) {
// 	char **copy = malloc(sizeof(char *) * (height + 1));
// 	if (!copy) {
// 		return NULL;
// 	}
// 	for (int i = 0; i < height; i++) {
// 		copy[i] = strdup(map[i]);
// 		if (!copy[i]) {
// 			// En cas d'erreur, libérer les lignes déjà allouées
// 			for (int j = 0; j < i; j++) {
// 				free(copy[j]);
// 			}
// 			free(copy);
// 			return NULL;
// 		}
// 	}
// 	copy[height] = NULL;
// 	return copy;
// }

// Libérer la copie de la carte

int flood_fill(t_data *data)
{
	if (data->p_x < 0 || )
}



// Vérification récursive pour explorer les cellules traversables et s'assurer qu'elles sont entourées de murs
int flood_fill(char **map, int x, int y, int max_len, int height) {
	// Si on est hors des limites de la carte ou sur une cellule invalide, c'est une erreur
	if (x < 0 || y < 0 || y >= height || x >= max_len || map[y][x] == '\0') {
		return 0;  // La carte n'est pas fermée
	}

	// Si on touche un mur ou un espace, c'est valide (rien à explorer)
	if (is_wall_or_space(map[y][x])) {
		return 1;
	}

	// Marquer la cellule comme visitée en la transformant en espace pour éviter de la revisiter
	map[y][x] = ' ';

	// Vérifier les 4 directions (haut, bas, gauche, droite)
	if (!flood_fill(map, x + 1, y, max_len, height) ||  // Droite
		!flood_fill(map, x - 1, y, max_len, height) ||  // Gauche
		!flood_fill(map, x, y + 1, max_len, height) ||  // Bas
		!flood_fill(map, x, y - 1, max_len, height)) {  // Haut
		return 0;  // Si une direction retourne 0, la carte n'est pas fermée
	}

	return 1;  // Toutes les directions sont valides
}

// Trouver la longueur maximale des lignes
int find_max_len(char **map) {
	int i = 0;
	int max_len = 0;
	while (map[i]) {
		int len = strlen(map[i]);
		if (len > max_len) {
			max_len = len;
		}
		i++;
	}
	return max_len;
}

// Trouver la hauteur de la carte
int find_map_height(char **map) {
	int i = 0;
	while (map[i]) {
		i++;
	}
	return i;
}

// Vérifier si la carte est fermée en appelant flood_fill à partir de chaque cellule traversable
int is_map_closed(char **map) {
	int max_len = find_max_len(map);
	int height = find_map_height(map);

	// Créer une copie de la carte pour le flood fill
	char **map_copy = copy_map(map, height);
	if (!map_copy) {
		printf("Erreur de copie de la carte\n");
		return 0;
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < max_len; x++) {
			if (map[y][x] == '0') {  // Si on trouve une cellule traversable
				if (!flood_fill(map_copy, x, y, max_len, height)) {
					free_map(map_copy, height);
					return 0;  // La carte n'est pas fermée
				}
			}
		}
	}

	free_map(map_copy, height);
	return 1;  // La carte est fermée
}

int main(void) {
	// Exemple de carte irrégulière
	char *map[] = {
		"111  11",
		"1010 11",
		"1011101",
		"1000001",
		"1111111",
		NULL
	};

	// Tester si la carte est fermée
	if (is_map_closed(map)) {
		printf("La carte est fermée.\n");
	} else {
		printf("La carte n'est pas fermée.\n");
	}

	char *map2[] = {
    "1111111111111",
    "1100001000011",
    "1011101011101",
    "1000100001001",
    "1010111010101",
    "1000101010001",
    "1111010101111",
    "1000101010001",
    "1010111010101",
    "1000100001001",
    "1011101011101",
    "1100001000011",
    "1111111111111",
    NULL
	};

	// Tester si la carte est fermée
	if (is_map_closed(map2)) {
		printf("La carte est fermée.\n");
	} else {
		printf("La carte n'est pas fermée.\n");
	}


	return 0;
}


// int main(void) {
//     t_data data;

//     // Exemple de carte non rectangulaire
//     char *map[] = {
//         "1111",
//         "10S1",
//         "1111",
//         "1111",
//         NULL
//     };

//     // Assigner la carte à la structure data
//     data.map = map;

//     // Trouver la longueur de la ligne la plus longue
//     data.max_len = find_max_len(data.map);

//     // Remplir les lignes plus courtes avec des espaces
//     fill_with_spaces(&data);

//     // Tester la fonction is_map_closed
//     if (is_map_closed(&data) == 1) {
//         printf("La carte est fermée.\n");
//     } else {
//         printf("La carte n'est pas fermée.\n");
//     }

//     return 0;
// }

