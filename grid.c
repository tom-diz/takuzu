#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc_functions.h"
#include "grid.h"
#include "main.h"

// Définition des grilles
int grid_4x4[4][4] = {
    {0, 1, 0, 1},
    {0, 1, 1, 0},
    {1, 0, 1, 0},
    {1, 0, 0, 1}
};

int grid_8x8[8][8] = {
    {1, 0, 0, 1, 0, 1, 0, 1},
    {0, 0, 1, 1, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 1, 1},
    {0, 0, 1, 1, 0, 1, 0, 1},
    {1, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 1, 0, 1, 0, 1, 0}
};

// Entrée de la taille de la grille par l'utilisateur
int check_grid_size()
{
    clean_console();
    printf("Veuillez s%clectionner la taille de la grille:\n", 130);
    set_color(CYAN); printf("1");
    set_color(WHITE); printf(" > 4x4\n");
    set_color(CYAN); printf("2");
    set_color(WHITE); printf(" > 8x8\n");
    
    int size = safe_type(2);
    switch (size)
    {
        case 1:
            return 4;
        case 2:
            return 8;
    }
}

// Création d'une grille remplie d'une valeur "value"
int** create_grid(int size, int value)
{
    int **grid = malloc(size*sizeof(int*));
    for(int i = 0; i < size; i++){
        grid[i] = malloc(size*sizeof(int));
        for(int j = 0; j < size; j++) {
            grid[i][j] = value; 
        }
    }
    return grid;
}


int* create_array(int size, int value)
{
    int *array = malloc(size*sizeof(int));
    for(int i = 0; i < size; i++){
        array[i] = value;
    }
    return array;
}

int** get_grid_size(int size)
{
    int** grid = create_grid(size, 0);

    switch (size) {

        // Grille 4x4
        case 4:
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    grid[i][j] = grid_4x4[i][j];
                }
            }
            break;

        // Grille 8x8
        case 8:
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    grid[i][j] = grid_8x8[i][j];
                }
            }
            break;
    }

    return grid;
}

// Print de la Grille
int print_grid(int** grid, int size) {
    char y[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char z[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    
    int i, j;

    printf(" ");
    for (i = 0; i < size ; i++)
    {
        set_color(BLUE); printf("  %c", y[i]);
    }
    printf("\n");

    for(i = 0 ; i < size ; i++)
    {
        set_color(BLUE); printf("%c  ", z[i]);
        for(j = 0 ; j < size ; j++)
        {
            if (grid[i][j] == -1) {set_color(WHITE); printf("X  ");}
            else {set_color(WHITE); printf("%d  ", grid[i][j]);}
        }
        printf("\n");
    }
    printf("\n");
}

// Print de la grille coloré 

int print_grid_colored(int** grid, int size, int col, int lig) {
    char y[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char z[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    
    int i, j;

    printf(" ");
    for (i = 0; i < size ; i++)
    {
        set_color(BLUE); printf("  %c", y[i]);
    }
    printf("\n");

    for(i = 0 ; i < size ; i++)
    {
        {set_color(BLUE); printf("%c  ", z[i]);
        for(j = 0 ; j < size ; j++)
        {
            if ((i == col) && (j == lig))
            {
                if (grid[i][j] == -1) {set_color(RED); printf("X  "); set_color(WHITE); printf("  ");}
                else {set_color(RED); printf("%d", grid[i][j]); set_color(WHITE);printf("  ");}
            }
            else
            {
                if (grid[i][j] == -1) {set_color(WHITE); printf("X  ");}
                else {set_color(WHITE); printf("%d  ", grid[i][j]);}
            }
        }
    }
    printf("\n");
}
}

// ----------------------------------------
// Vérification des grilles
// CODES:
// 0: Non valide
// 1: Valide & Correct
// 2: Valide mais non correct

int check_correct(int** grid, int size, int col_joue, int lig_joue, int nbr, int msg)
{
    if (!check_line(grid, size, msg)) {
        return 0;
    }
    else if (!check_col(grid, size, msg)) {
        return 0;
    }

    // FAIRE VERIF GAUCHE DROITE


    else if (!check_same_specific(grid, size, col_joue, lig_joue, nbr))
    {
        if (msg) { clean_console(); printf("Le chiffre jou%c est valide mais pas correct.\nINDICE: Le coup %c jouer est le chiffre inverse du coup jou%c.\n", 130, 133, 130); };
        return 3;
    }
    
    else if (check_same_overall(grid, size))
    {
        return 2;
    }

    else
    {
        if (msg) clean_console();
        if (msg) printf("Le coup est correct.\n");
        return 1;
    }
}

// Vérification de la règle des lignes 

int check_line(int** grid, int size, int msg)
{
    for (int i = 0 ; i < size ; i++)
    {
        int zero_amount = 0;
        int one_amount = 0;

        int zero_in_row_amount = 0;
        int one_in_row_amount = 0;

        int null_presence = 0;

        for (int j = 0 ; j < size ; j++)
        {
            if (grid[i][j] == 1) 
            {
                one_amount++;
                one_in_row_amount++;
                zero_in_row_amount = 0;
            }
            else if (grid[i][j] == 0) 
            {
                zero_amount++;
                zero_in_row_amount++;
                one_in_row_amount = 0;
            }
            else
            {
                null_presence = 1;
                zero_in_row_amount = 0;
                one_in_row_amount = 0;
            }

            if (zero_in_row_amount > 2)
            {
                if (msg) clean_console();
                if (msg) printf("Il y a plusieurs chiffres '0' %c la suite sur la ligne.\n", 133);
                return 0;
            }
            else if (one_in_row_amount > 2)
            {
                if (msg) clean_console();
                if (msg) printf("Il y a plusieurs chiffres '1' %c la suite sur la ligne.\n", 133);
                return 0;
            }

            if (zero_amount > size/2)
            {
                if (msg) clean_console();
                if (msg) printf("Il y a trop de chiffres '0' sur la ligne.\n");
                return 0;
            }
            else if (one_amount > size/2)
            {
                if (msg) clean_console();
                if (msg) printf("Il y a trop de chiffres '1' sur la ligne.\n");
                return 0;
            }
        }
    }
    return 1;
}

// Vérification de la règle des colonnes

int check_col(int** grid, int size, int msg)
{
    for (int i = 0 ; i < size ; i++)
    {
        int zero_amount = 0;
        int one_amount = 0;

        int zero_in_row_amount = 0;
        int one_in_row_amount = 0;

        int null_presence = 0;

        for (int j = 0 ; j < size ; j++)
        {
            if (grid[j][i] == 1) 
            {
                one_amount++;
                one_in_row_amount++;
                zero_in_row_amount = 0;
            }
            else if (grid[j][i] == 0) 
            {
                zero_amount++;
                zero_in_row_amount++;
                one_in_row_amount = 0;
            }
            else
            {
                null_presence = 1;
                zero_in_row_amount = 0;
                one_in_row_amount = 0;
            }

            if (zero_in_row_amount > 2)
            {
                if (msg) clean_console();
                if (msg) printf("Il y a plusieurs chiffres '0' %c la suite sur la colonne.\n", 133);
                return 0;
            }
            else if (one_in_row_amount > 2)
            {
                if (msg) clean_console();
                if (msg) printf("Il y a plusieurs chiffres '1' %c la suite sur la colonne.\n", 133);
                return 0;
            }

            if (zero_amount > size/2)
            {
                if (msg) clean_console();
                if (msg) printf("Il y a trop de chiffres '0' sur la colonne.\n");
                return 0;
            }
            else if (one_amount > size/2)
            {
                if (msg) clean_console();
                if (msg) printf("Il y a trop de chiffres '1' sur la colonne.\n");
                return 0;
            }
        }
    }
    return 1;
}

/*int check_equal_lines(int** grid, int size) {
    return memcmp(grid[0], grid[1], sizeof(grid[0]));
    
    for (int i = 0; i < size; i++)
    {
        // Copier la ligne de base dans la variable "base_array"
        int* base_array = create_array(size, -1);
        for (int j = 0; j < size; j++) base_array[j] = grid[i][j];

        for (int j = 0; j < size; j++)
        {
            // Ne pas prendre l'index de la base (pour éviter de fausses comparaisons)
            if (i != j) {
                int temp_equal = 1;
                int* compared_array = create_array(size, -1);
                for (int k = 0; k < size; k++) compared_array[k] = grid[j][k];

                // Comparaison des deux lignes (base & compared)
                for (int k = 0; k < size; k++) {
                    // Si ligne contient une valeur nulle : return 1 car les lignes du dessus sont obligatoirement valides
                    if ((base_array[k] == -1) || (compared_array[k] == -1))
                    {
                        return 1;
                    }

                    if (base_array[k] != compared_array[k])
                    {
                        // Ligne non égale
                        temp_equal = 0;
                    }
                }

                if (temp_equal) return 0;
            }
        }
    }
    return 1;
}*/

int check_same_specific(int** grid, int size, int col, int lig, int nbr)
{
    int** grid_corrected = get_grid_size(size);

    if (nbr != grid_corrected[lig-1][col-1]) 
    {
        return 0;
    }

    return 1;
}

// Vérification de la grille correction avec la grille de l'utilisateur


int check_same_overall(int** grid, int size)
{
    int** grid_corrected = get_grid_size(size);
    for (int i = 0; i < size; i++) for (int j = 0; j < size; j++)
        if (grid[i][j] != grid_corrected[i][j]) {
            return 0;
        }
    return 1;
}