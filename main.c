#include "misc_functions.h"
#include <time.h>
#include <stdlib.h>
#include "main.h"

HANDLE hConsole;

int color_init()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

int set_color(int k)
{
    SetConsoleTextAttribute(hConsole, k);
}

int main() {
    color_init();

    srand(time(NULL));
    main_menu();
}