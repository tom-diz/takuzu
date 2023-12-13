#ifndef GRID_H
#define GRID_H

extern int grid_4x4[4][4];
extern int grid_8x8[8][8];

int check_line(int** grid, int size, int msg);
int check_col(int** grid, int size, int msg);


int** create_grid(int size, int value);
int* create_array(int size, int value);
int check_grid_size();
int** get_grid_size(int grid_size);
int print_grid(int** grid, int size);
int modify_grid(int** grille, int col, int lig, int nbr);
int print_grid_with_mask(int** grid, int** mask, int size);
int check_correct(int** grid, int size, int col_joue, int lig_joue, int nbr, int msg);
int check_equal_lines(int** grid, int size);
int check_same_specific(int** grid, int size, int col, int lig, int nbr);
int check_same_overall(int** grid, int size);
int print_grid_colored(int** grid, int size, int col, int lig);

#endif