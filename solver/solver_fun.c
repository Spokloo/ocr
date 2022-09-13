#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** convert(char * filename) {
    
    FILE * fp = fopen(filename, "r");
    char line[12];

    int **grid = malloc(sizeof(int*) *9);
    for (int j = 0; j < 9; j++) {
        grid[j] = malloc(sizeof(int*) *9);
    }
    int y = 0;
    int x;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (line[0] != 10) {
            x = 0;
            for (int i = 0; i < 12; i++) {
                if (line[i] != 32) {
                    if (line[i] != 46 && line[i] != 0) {
                        grid[y][x] = line[i] - '0';
                    }
                    x++;
                }
            }
            y++;
        }
    }

    fclose(fp);
    return grid;
}



int check_line(int** grid, int line) {

    int check_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int check = 1;
    
    for (int i = 0; i < 9; i++) {
        if (grid[line][i] != 0) {
            if (check == 1 && check_array[grid[line][i]] == 1) {
                check_array[grid[line][i]] = 0;
            } else {
                check = 0;
            }
        }
    }

    return check;
}

int check_column(int** grid, int column) {

    int check_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int check = 1;
    
    for (int i = 0; i < 9; i++) {
        if (grid[i][column] != 0) {
            if (check == 1 && check_array[grid[i][column]] == 1) {
                check_array[grid[i][column]] = 0;
            } else {
                check = 0;
            }
        }
    }

    return check;
}

int check_square(int** grid, int start_x, int start_y) {
    
    int check_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int check = 1;

    for (int i = start_x; i < start_x + 3; i++) {
        for (int j = start_y; j < start_y + 3; j++) {
            if (grid[i][j] != 0) {
                if (check == 1 && check_array[grid[i][j]] == 1) {
                    check_array[grid[i][j]] = 0;
                } else {
                    check = 0;
                }
            }
        }
    }

    return check;
}

int check_grid(int** grid) {

    int check = 1;

    for (int i = 0; i < 9; i++) {
        check &= check_line(grid, i) && check_column(grid, i);
    }

    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            check &= check_square(grid, i, j);
        }
    }

    return check;
}

int is_board_solved(int** grid) {

    int check = 0;
    
    if (check_grid(grid)) {
        check = 1;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                check &= grid[i][j] != 0;
            }
        }
    }
    return check;
}

int** solve(int** grid) {

    int **solved_grid = grid; 

    if (is_board_solved(grid)) {
        return grid;
    }
    
    // Find index of first empty cell
    int row = -1, column = -1;
    for (int i = 0; i < 9; i++) {
        if (row == -1) {
            for (int j = 0; j < 9; j++) {
                if (row == -1) {
                    if (grid[i][j] == 0) {
                        row = i;
                        column = j;
                    }
                }
            }
        }
    }

    int** old_grid;
    
    // Test all numbers
    for (int i = 1; i < 10; i++) {
        solved_grid[row][column] = i;

        if (check_grid(solved_grid)) {
            old_grid = solved_grid;
            solved_grid = solve(solved_grid);

            if (solved_grid == NULL) {
                solved_grid = old_grid;
            } else {
                return solved_grid;
            }
        }
        solved_grid[row][column] = 0;

    }

    return NULL;
}

void write_grid(int** grid, char * filename) {

    char result[strlen(filename) + 6];
    char * extension = ".result";
    strcpy(result, filename);

    FILE * fp = fopen(strcat(result, extension), "w");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) {
                fputc(' ', fp);
            }
            fputc(grid[i][j] + '0', fp);
        }
        if (i == 2 || i == 5) {
            fputc('\n', fp);
        }
        fputc('\n', fp);
    }

    fclose(fp);
}

void print_grid(int** grid) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) {
                printf(" ");
            }
            if (grid[i][j] == 0) {
                printf(".");
            } else {
                printf("%d", grid[i][j]);
            }
        }
        printf("\n");
        if (i == 2 || i == 5) {
            printf("\n");
        }
    }
}
