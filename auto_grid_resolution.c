#include "grid.h"
#include "grid_resolution.h"
#include "auto_grid_resolution.h"
#include "misc_functions.h"
#include "main.h"
#include <stdio.h>
#include <unistd.h>

// Vérifie si la ligne respecte les règles

int verify_line(int** grid, int size, int lin)
{
    int zero_amount = 0;
    int one_amount = 0;

    for (int i = 0; i < size; i++)
        if (grid[lin][i] == 1) one_amount++;
        else if (grid[lin][i] == 0) zero_amount++;

    if (zero_amount == (size/2)) {
        printf("Il y a une ligne avec le nombre maximal de 0.\nOn met donc un 1 dans une case libre.\n");
        return 1; // CHIFFRE 1
    }
    else if (one_amount == (size/2)) {
        printf("Il y a une ligne avec le nombre maximal de 1.\nOn met donc un 0 dans une case libre.\n");
        return 0; // CHIFFRE 0
    }
    else return -1; // PAS TROUVE
}
// Vérifie si la colonne respecte les règles

int verify_col(int** grid, int size, int col)
{
    int zero_amount = 0;
    int one_amount = 0;

    for (int i = 0; i < size; i++)
        if (grid[i][col] == 1) one_amount++;
        else if (grid[i][col] == 0) zero_amount++;

    if (zero_amount == (size/2)) { 
        printf("Il y a une colonne avec le nombre maximal de 0.\nOn met donc un 1 dans une case libre.\n");
        return 1; // CHIFFRE 1
    }
    else if (one_amount == (size/2)) {
        printf("Il y a une colonne avec le nombre maximal de 1.\nOn met donc un 0 dans une case libre.\n");
        return 0; // CHIFFRE 0
    }
    else return -1; // PAS TROUVE
}

//Vérifie la suite de 1 et de 0

int suite(int** grid, int size, int lin, int col)
{
    // Vérification à gauche
    if ((col > 1) && ((grid[lin][col-1] == grid[lin][col-2]) && (grid[lin][col-1] != -1))) 
    {
        printf("Il y a une suite de %d %c gauche.\nOn met donc un %d %c droite de la suite.\n", grid[lin][col-1], 133, !grid[lin][col-1], 133);
        return !grid[lin][col-1];
    }
    // Vérification à droite
    else if ((col < size - 2) && ((grid[lin][col+1] == grid[lin][col+2]) && (grid[lin][col+1] != -1))) 
    {
        printf("Il y a une suite de %d %c droite.\nOn met donc un %d %c gauche de la suite.\n", grid[lin][col+1], 133, !grid[lin][col+1], 133);
        return !grid[lin][col+1];
    }
    // Vérification en bas
    else if ((lin < size - 2) && ((grid[lin+1][col] == grid[lin+2][col]) && (grid[lin+1][col] != -1)))
    {
        printf("Il y a une suite de %d en bas.\nOn met donc un %d au dessus de la suite.\n", grid[lin+1][col], !grid[lin+1][col]);
        return !grid[lin+1][col];
    }
    // Vérification en haut
    else if ((lin > 1) && ((grid[lin-1][col] == grid[lin-2][col]) && (grid[lin-1][col] != -1)))
    {
        printf("Il y a une suite de %d au dessus.\nOn met donc un %d en dessous de la suite.\n", grid[lin-1][col], !grid[lin-1][col]);
        return !grid[lin-1][col];
    }
    else return -1; // Aucune suite trouvée
}

// Vérifie les 1 et les 0 autour

int around(int** grid, int size, int lin, int col)
{
    if ((col > 0) && (col < size - 1) && (grid[lin][col-1] == grid[lin][col+1]) && (grid[lin][col+1] != -1)) 
    {
        printf("Il y a deux %d %c l'horizontale.\nOn met donc un %d entre ces deux.\n", grid[lin][col-1], 133, !grid[lin][col-1]);
        return !grid[lin][col-1];
    }
    if ((lin > 0) && (lin < size - 1) && (grid[lin-1][col] == grid[lin+1][col]) && (grid[lin+1][col] != -1))
    {
        printf("Il y a deux %d %c la verticale.\nOn met donc un %d entre ces deux.\n", grid[lin-1][col], 133, !grid[lin-1][col]);
        return !grid[lin-1][col];
    }
    return -1;
}

// Attente de l'entrée de l'utilisateur

int wait_user_input()
{
    sleep(0.5);
    printf("Veuillez appuyer sur une touche pour continuer...");
    getchar();
    return 0;
}

// Vérifie si la case est correcte 

int verify_grid_cell(int** grid, int size, int lin, int col)
{
    clean_console();

    int returned_number;

    // Vérifier si la ligne est remplie de 0 ou de 1
    returned_number = verify_line(grid, size, lin);
    if (returned_number != -1)
    {
        grid[lin][col] = returned_number;
        return 1; // Chiffre trouvé
    }
    // Vérifier si la colonne est remplie de 0 ou de 1
    else 
    {
        returned_number = verify_col(grid, size, col);
        if (returned_number != -1)
        {
            grid[lin][col] = returned_number;
            return 1; // Chiffre trouvé
        }
        else
        {
            // Vérifier la présence de suites autour
            returned_number = suite(grid, size, lin, col);
            if (returned_number != -1)
            {
                grid[lin][col] = returned_number;
                return 1; // Chiffre trouvé
            }
            else
            {
                // Vérifier la présence de chiffres autour
                returned_number = around(grid, size, lin, col);
                if (returned_number != -1)
                {
                    grid[lin][col] = returned_number;
                    return 1; // Chiffre trouvé
                }
            }
        }
    }
    
    return 0; // Aucun chiffre trouvé
}

// résolution de la grille

int auto_grid_resolution()
{
    int size = check_grid_size();

    int** mask = create_grid(size, 0);
    mask_generation(mask, size);

    int** grid = create_grid(size, 0);

    int masked_cells = 0;

    // Créer une grille à partir de la grille masque
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (size == 4)
            {
                if (mask[i][j] == 1) grid[i][j] = grid_4x4[i][j];
                else
                {
                    grid[i][j] = -1; 
                    masked_cells++;
                }
            }
            else
            {
                if (mask[i][j] == 1) grid[i][j] = grid_8x8[i][j];
                else
                {
                    grid[i][j] = -1; 
                    masked_cells++;
                }
            }
        }
    
    clean_console();

    printf("On d%cbute avec la grille suivante:\n", 130);
    print_grid(grid, size);
    getchar();
    wait_user_input();

    do {
        int temp_cells_count = masked_cells;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                if (grid[i][j] == -1) {
                    if (verify_grid_cell(grid, size, i, j)) {
                        print_grid_colored(grid, size, i, j);
                        masked_cells--;
                        wait_user_input();
                        i = j = size;
                    }
                }
            }
        
        // AUCUNE CASE RESOLVABLE: RESOLUTION AUTO DE LA PREMIERE CASE
        int stop = 0;
        if (temp_cells_count == masked_cells != 0)
        {
            for (int i = 0; i < size && !stop; i++)
            for (int j = 0; j < size && !stop; j++)
            {
                if (grid[i][j] == -1) {
                    if (size == 4) grid[i][j] = grid_4x4[i][j];
                    else grid[i][j] = grid_8x8[i][j];
                    print_grid_colored(grid, size, i, j);
                    printf("On ne peut pas r%csoudre sans faire une possible faute.\nOn s'aide donc de la grille correction.\n", 130);
                    masked_cells--;
                    stop = 1;
                    wait_user_input();
                    i = j = size;
                }
            }
        }
            
    } while (masked_cells != 0);
    
    clean_console();

    print_grid(grid, size);

    printf("La grille est maintenant r%csolue.", 130);

    sleep(0.5);

    getchar();

    return 0;
}