#ifndef GRID_GENERATION_H
#define GRID_GENERATION_H

int* create_array_from_int(int size, int number);
void print_array(int* array, int size);
int check_grid_generation(int** grid, int size);
int** generate(int** grid, int size);
int grid_generation();

#endif