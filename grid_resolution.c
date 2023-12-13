#include <stdio.h>
#include "grid.h"
#include "misc_functions.h"
#include "grid_resolution.h"
#include "main.h"
#include <unistd.h>
#include <windows.h>

// Insérer un masque 

int** mask_input(int** mask, int size) {
    int col = 1, lig, nbr, mask_valid = 0;
    while (!mask_valid)
    {
        while (1) {
            clean_console();
            print_grid(mask, size);
            printf("> Veuillez saisir le num%cro de colonne. (Saisir 0 pour terminer)\n", 130);
            printf("(Vous devez saisir au moins une valeur qui sera affich%ce)\n", 130);
            col = safe_type_0(size);
            if (!col) break;
            printf("> Veuillez saisir le num%cro de ligne.\n", 130);
            lig = safe_type(size);
            printf("> Veuillez saisir le nombre voulu (0 ou 1).\n");
            nbr = safe_type_0(1);
            mask[lig-1][col-1] = nbr;
        }

        // Vérifie si le masque est vide
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (mask[i][j] == 1) mask_valid = 1;
    }
    return mask;
}

int grid_resolution_menu()
{
    int size = check_grid_size();

    // CONFIG DU MASQUE

    int** mask = create_grid(size, 0);

    clean_console();

    set_color(WHITE); printf("Veuillez s%clectionner une option:\n", 130);
    set_color(CYAN); printf("1");
    set_color(WHITE); printf(" > Saisir un masque\n");
    set_color(CYAN); printf("2");
    set_color(WHITE); printf(" > Commencer la partie (G%cn%cration auto.)\n", 130, 130);
    set_color(CYAN); printf("3");
    set_color(WHITE); printf(" > Retour\n");

    while (1)
    {
        switch (safe_type(3))
        {
            case 1: // Saisie du masque
                mask_input(mask, size);
                resolution_grille(mask, size);
                return 0;
            case 2: // Génération du masque & Jouer directement
                mask_generation(mask, size);
                resolution_grille(mask, size);
                return 0;
            case 3: // Menu principal
                main_menu();
                return 0;
        }
    }

    main_menu();
}
// Générateur de masques aléatoire

int** mask_generation(int** mask, int size)
{
    clean_console();
    int amount;
    printf("Veuillez choisir une difficult%c:\n", 130);
    set_color(CYAN); printf("1");
    set_color(WHITE); printf(" > Facile\n");
    set_color(CYAN); printf("2");
    set_color(WHITE); printf(" > Normal\n");
    set_color(CYAN); printf("3");
    set_color(WHITE); printf(" > Difficile\n");
    


    switch (safe_type(3))
    {
        case 1:
            amount = (size*size)/2;
            break;
        case 2:
            amount = (size*size)/3;
            break;
        case 3:
            amount = (size*size)/4;
            break;
    }
    
    while (amount != 0)
    {
        int rand_1 = rand_number(0, size-1);
        int rand_2 = rand_number(0, size-1);

        if (mask[rand_1][rand_2] == 0)
        {
            mask[rand_1][rand_2] = 1;
            amount--;
        }
    }

    return mask;
}
// Résolution de la Grille

int resolution_grille(int** mask, int size)
{
    clean_console();
    // Créer une grille à partir de la grille masque
    int** grid = get_grid_size(size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (mask[i][j] == 1)
            {
                if (size == 4)
                {
                    grid[i][j] = grid_4x4[i][j];
                }
                else
                {
                    grid[i][j] = grid_8x8[i][j];
                }
            }
            else grid[i][j] = -1;
        }
        
    // Système de vie

    int health = 3;
    do {
        print_grid(grid, size);
        printf("Veuillez saisir le num%cro de colonne.\n", 130);
        int col = safe_type(size);
        printf("Veuillez saisir un num%cro de ligne.\n", 130);
        int lig = safe_type(size);
        printf("Veuillez saisir le nombre voulu (0 ou 1).\n");
        int nbr = safe_type_0(1);

        grid[lig-1][col-1] = nbr;

        int check = check_correct(grid, size, col, lig, nbr, 1);
        
        if (check == 0)
        {
            health--;
            grid[lig-1][col-1] = -1;
            if (health != 0) printf("Il vous reste %d vie(s).\n", health);
            else printf("Vous avez %cchou%c dans la r%csolution de la grille.", 130, 130, 130);
        }

        if (check == 3)
        {
            grid[lig-1][col-1] = -1;
        }

        else if (check == 2)
        {
            printf("\nVous avez gagn%c la partie !\nVeuillez appuyer sur une touche pour continuer...", 130);
            getchar();
            sleep(0.5);
            getchar();
            return 1;
        }
        
    } while (health > 0);
}