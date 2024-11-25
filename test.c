#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_data {
    char **map;
    int h_size;
    int w_size;
} t_data;

// Les fonctions précédentes ici
void skip_info_lines(FILE *file)
{
    char line[1024];
    int count = 0;
    
    while (count < 7 && fgets(line, sizeof(line), file))
        count++;
}

int count_map_lines(FILE *file, long *start_pos)
{
    char line[1024];
    int count = 0;
    
    *start_pos = ftell(file);
    while (fgets(line, sizeof(line), file))
    {
        if (strlen(line) > 1)
            count++;
    }
    fseek(file, *start_pos, SEEK_SET);
    return count;
}

int read_map(FILE *file, t_data *data)
{
    char line[1024];
    long start_pos;
    int i = 0;
    
    skip_info_lines(file);
    
    int map_lines = count_map_lines(file, &start_pos);
    if (map_lines <= 0)
        return 0;
    
    data->map = malloc(sizeof(char *) * (map_lines + 1));
    if (!data->map)
        return 0;
    
    while (fgets(line, sizeof(line), file) && i < map_lines)
    {
        if (strlen(line) <= 1)
            continue;
            
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        
        data->map[i] = strdup(line);
        if (!data->map[i])
        {
            for (int j = 0; j < i; j++)
                free(data->map[j]);
            free(data->map);
            return 0;
        }
        i++;
    }
    
    data->map[i] = NULL;
    data->h_size = i;
    data->w_size = strlen(data->map[0]);
    
    return 1;
}

// Fonction pour libérer la mémoire
void free_map(t_data *data)
{
    if (data->map)
    {
        for (int i = 0; i < data->h_size; i++)
        {
            if (data->map[i])
                free(data->map[i]);
        }
        free(data->map);
        data->map = NULL;
    }
}

// Fonction pour afficher la map
void display_map(t_data *data)
{
    printf("\nMap dimensions: %d x %d\n", data->w_size, data->h_size);
    printf("Map content:\n");
    for (int i = 0; i < data->h_size; i++)
    {
        printf("[%2d] %s\n", i, data->map[i]);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <map_file.cub>\n", argv[0]);
        return 1;
    }

    t_data data = {0};  // Initialize to zero
    FILE *file = fopen(argv[1], "r");
    
    if (!file)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    printf("Reading map from file: %s\n", argv[1]);
    
    if (!read_map(file, &data))
    {
        printf("Error: Failed to read map\n");
        fclose(file);
        return 1;
    }

    // Afficher la map
    display_map(&data);

    // Libérer la mémoire et fermer le fichier
    free_map(&data);
    fclose(file);
    
    printf("\nMap successfully read and displayed!\n");
    return 0;
}