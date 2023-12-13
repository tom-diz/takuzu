#include "grid.h"
#include <stdio.h>
#include "misc_functions.h"
#include "math.h"
#include "main.h"
#include <unistd.h>
#include <windows.h>

// Création d'un tableau 1D

int* create_array_from_int(int size, int number) {
    int* array = create_array(size, (-1));

    for(int i = 0; number > 0; i++)
    {
        array[size-1-i] = number % 2;
        if (array[size-1-i] < 0) array[size-1-i] = 0;
        number = number / 2;
    }

    for(int i = 0; i < size+1 ; i++)
    {
        if (array[size-1-i] < 0) array[size-1-i] = 0;
    }

    return array;
}

// Print du tableau 1D

void print_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Vérifie si la grille respecte les règles

int check_grid_generation(int** grid, int size) {
    if (!check_line(grid, size, 0)) return 0;
    if (!check_col(grid, size, 0)) return 0;
    //if (!check_equal_lines(grid, size)) return 0;
    return 1;
}

// Génération de la grille alétoire

int grid_generation() {

    int size = check_grid_size();

    int** grid = create_grid(size, -1);
    
    for (int i = 0; i < size; i++) {
        int valid = 0;
        int* array;
        do {
            int random = rand_number(0, pow(2, size)-1);
            array = create_array_from_int(size, random);

            for (int j = 0; j < size; j++) {
                grid[i][j] = array[j];
            }
            
            // Vérifie la validité de la grille
            if (check_grid_generation(grid, size)) valid = 1;
        } while (valid == 0);
    }
    printf("Le programme g%cn%cre une grille al%catoire.\nVeuillez patienter...", 130, 138, 130);

    sleep(1);

    clean_console();
    printf("Voici la grille g%cn%cr%ce :\n", 130, 130, 130);
    print_grid(grid, size);
    printf("Veuillez appuyer sur une touche pour continuer...\n");
    getchar();
    sleep(0.5);
    // printf("Veuillez appuyer sur une touche pour continuer...");
    getchar();

    return 0;
}