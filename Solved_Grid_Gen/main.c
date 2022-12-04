#include "grid_gen.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printHelp();
        return 1;
    }

    construct_grid(argv[1], "images/blank_grid.png", "res.png");

    return 0;
}
