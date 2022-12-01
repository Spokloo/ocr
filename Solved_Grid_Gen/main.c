#include "grid_gen.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printHelp();
        return 1;
    }

    construct_grid(argv[1], argv[2]);

    return 0;
}
