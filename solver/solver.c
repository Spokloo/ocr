#include "solver_fun.h"

int main(int argc, char** argv) {

    if (argc == 2) {
        write_grid(solve(convert(argv[1])), argv[1]);
    }

    return 0;
}
