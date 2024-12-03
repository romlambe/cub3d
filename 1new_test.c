/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1new_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:33:42 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/25 12:44:51 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./gnl/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

char **read_file_into_array(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Erreur ouverture fichier");
        return (NULL);
    }
    char **lines = NULL;
    char *line = NULL;
    int line_count = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        char **temp = realloc(lines, (line_count + 1) * sizeof(char *));
        if (!temp)
        {
            perror("Erreur allocation mémoire");
            free(line);
            break;
        }
        lines = temp;
        lines[line_count++] = line;
    }
    char **final = realloc(lines, (line_count + 1) * sizeof(char *));
    if (final)
    {
        lines = final;
        lines[line_count] = NULL;
    }
    close(fd);
    return (lines);
}

int main() {
    char **file_content = read_file_into_array("test.cub");

    if (file_content) {
        for (int i = 0; file_content[i]; i++) {
            printf("%s", file_content[i]); // Les lignes incluent souvent '\n'
            free(file_content[i]);        // Libérer chaque ligne
        }
        free(file_content);               // Libérer le tableau
    }
    return 0;
}
