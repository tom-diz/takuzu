#include <stdio.h>
#include "auto_grid_resolution.h"
#include "misc_functions.h"
#include "grid_resolution.h"
#include "grid_generation.h"
#include "main.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>

// Setup pour la couleur

void color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}

// Menu principal

int main_menu()
{
    clean_console();
    printf("\n-----------------------------------------------------------------\nBienvenue dans le jeu du Takuzu.\nDans ce jeu, vous devez remplir une grille avec les\nchiffres 0 et 1 en suivant les r%cgles qui s'y appliquent.\n-----------------------------------------------------------------\n", 138);
        do {
        set_color(BLUE); printf("TAKUZU ");
        set_color(WHITE); printf("- Veuillez s%clectionner un mode :\n", 130);
        set_color(CYAN); printf("1");
        set_color(WHITE); printf(" > R%csoudre une grille\n", 130);
        set_color(CYAN); printf("2");
        set_color(WHITE); printf(" > R%csolution automatique d'une grille\n", 130);
        set_color(CYAN); printf("3");
        set_color(WHITE); printf(" > G%cn%crer une grille\n", 130, 130);
        set_color(CYAN); printf("4");
        set_color(WHITE); printf(" > Quitter le jeu\n");

        
        int choice = safe_type(4);
        switch (choice)
        {
            case 1:
                grid_resolution_menu();
                main_menu();
                break;
            case 2:
                auto_grid_resolution();
                main_menu();
                break;
            case 3:
                grid_generation();
                main_menu();
                break;
            case 4:
                clean_console();
                printf("Merci d'avoir jou%c au jeu de Takuzu.", 130);
                exit(0);
        }
    } while (1);
    return 0;
}

// Nettoyer la console

int clean_console() { for (int i = 0; i < 50; i++) {printf("\n");} return 0;};

// Saisie Sécurisée sans le 0

int safe_type(int max)
{
    do {
        int type;
        printf("Saisie: ");
        if (scanf("%d", &type) == 1) {
            if ((1 <= type) && (type <= max)) return type;
            else printf("Le nombre n'est pas dans la borne autoris%ce ! (Entre 1 et %d)\n", 130, max);
        }
        else printf("La saisie n'est pas un nombre.\n");
        getchar();
    } while (1);
}

// Saisie sécurisée avec le 0

int safe_type_0(int max)
{
    do {
        int type;
        printf("Saisie: ");
        if (scanf("%d", &type) == 1) {
            if ((0 <= type) && (type <= max)) return type;
            else printf("Le nombre n'est pas dans la borne autoris%ce ! (Entre 0 et %d)\n", 130, max);
        }
        else printf("La saisie n'est pas un nombre.\n");
        getchar();
    } while (1);
}

// Générer un nombre random

int rand_number(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}