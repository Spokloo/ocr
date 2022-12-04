#include "solver_fun.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 2)
    {

        // Converts the grid from the argv[1] file
        // Then solves it
        // And finally write it in the argv[1].result file
        char result[strlen(argv[1]) + 6];
        char *extension = ".result";
        strcpy(result, argv[1]);
        int **grid = load_grid(argv[1]);
        write_grid(solve(grid), strcat(result, extension));
        for(int i = 0; i < 9; i++)
            free(grid[i]);
        free(grid);
        return 0;
    }

    return 1;
}
