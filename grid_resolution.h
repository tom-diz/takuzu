#ifndef GRID_RESOLUTION_H
#define GRID_RESOLUTION_H

int grid_resolution_menu();
int** mask_input(int** mask, int size);
int** mask_generation(int** mask, int size);
int resolution_grille(int** mask, int size);

#endif