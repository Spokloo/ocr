#include "solver_fun.h"

int main(int argc, char **argv)
{

    if (argc == 2)
    {

        // Converts the grid from the argv[1] file
        // Then solves it
        // And finally write it in the argv[1].result file
        write_grid(solve(convert(argv[1])), argv[1]);

        return 0;
    }

    return 1;
}
