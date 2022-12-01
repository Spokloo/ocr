#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function: convert
 * -----------------
 *
 * Converts and returns the sudoku grid in filename into
 * a more usable format
 *
 * filename: name of the file containing the sudoku grid to
 *           convert
 *
 * returns: | the int[9][9] sudoku grid containing in each
 *          position either the numbers in the grid or 0 if no
 *          number was found
 */
int **load_grid(char *filename)
{

    FILE *fp = fopen(filename, "r");
    char line[12]; // 9 numbers + 2 spaces + final character

    int **grid = malloc(sizeof(int *) * 9);
    for (int j = 0; j < 9; j++)
    {
        grid[j] = malloc(sizeof(int *) * 9);
    }
    int y = 0, x;

    // fgets put one line from filename in line(variable) each time it is called
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (line[0] != 10)
        { // char 10 is End Of Line
            x = 0;
            for (int i = 0; i < 12; i++)
            {
                if (line[i] != 32)
                { // char 32 is Space
                    if (line[i] != 46 && line[i] != 0)
                    {                               // char 46 is .
                        grid[y][x] = line[i] - '0'; // char '0' is 48
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

/*
 * Function check_line
 * -------------------
 *
 * Checks if the line grid[line] is a valid suduko line
 * (if it contains numbers from 1 to 9 only one time)
 *
 * grid: the suduko grid to check
 * line: the line index to check
 *
 * returns: | 1 if grid[line] is a valid sudoku line
 *          | 0 if grid[line] is not a valid sudoku line
 */
int check_line(int **grid, int line)
{

    int check_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int check = 1;

    for (int i = 0; i < 9; i++)
    {
        if (grid[line][i] != 0)
        {
            if (check == 1 && check_array[grid[line][i]] == 1)
            {
                check_array[grid[line][i]] = 0;
            }
            else
            {
                check = 0;
            }
        }
    }

    return check;
}

/*
 * Function check_column
 * -------------------
 *
 * Checks if the column grid[column] is a valid suduko column
 * (if it contains numbers from 1 to 9 only one time)
 *
 * grid: the suduko grid to check
 * column: the column index to check
 *
 * returns: | 1 if grid[column] is a valid sudoku column
 *          | 0 if grid[column] is not a valid sudoku column
 */
int check_column(int **grid, int column)
{

    int check_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int check = 1;

    for (int i = 0; i < 9; i++)
    {
        if (grid[i][column] != 0)
        {
            if (check == 1 && check_array[grid[i][column]] == 1)
            {
                check_array[grid[i][column]] = 0;
            }
            else
            {
                check = 0;
            }
        }
    }

    return check;
}

/*
 * Function check_square
 * -------------------
 *
 * Checks if the square starting at grid[start_x][start_y]
 * is a valid suduko square (if it contains numbers
 * from 1 to 9 only one time)
 *
 * grid: the suduko grid to check
 * start_x: x index if the upper-left cell of the square
 * start_y: y index if the upper-left cell of the square
 *
 * returns: | 1 if grid[start_x][start_y] is a valid sudoku square
 *          | 0 if grid[start_x][start_y] is not a valid sudoku square
 */
int check_square(int **grid, int start_x, int start_y)
{

    int check_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int check = 1;

    for (int i = start_x; i < start_x + 3; i++)
    {
        for (int j = start_y; j < start_y + 3; j++)
        {
            if (grid[i][j] != 0)
            {
                if (check == 1 && check_array[grid[i][j]] == 1)
                {
                    check_array[grid[i][j]] = 0;
                }
                else
                {
                    check = 0;
                }
            }
        }
    }

    return check;
}

/*
 * Function check_grid
 * -------------------
 *
 * Checks if the grid is a valid sudoku grid
 *
 * grid: the suduko grid to check
 *
 * returns: | 1 if grid is a valid sudoku grid
 *          | 0 if grid is not a valid sudoku grid
 */
int check_grid(int **grid)
{

    int check = 1;

    for (int i = 0; i < 9; i++)
    {
        check &= check_line(grid, i) && check_column(grid, i);
    }

    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            check &= check_square(grid, i, j);
        }
    }

    return check;
}

/*
 * Function: is_board_solved
 * -------------------------
 *
 * Checks if grid is a solved sudoku board
 *
 * grid: the grid to check
 *
 * returns : | 1 if grid is solved | 0 if grid is not solved
 */
int is_board_solved(int **grid)
{

    int check = 0;

    if (check_grid(grid))
    {
        check = 1;

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                check &= grid[i][j] != 0;
            }
        }
    }
    return check;
}

/*
 * Function: solve
 * ---------------
 *
 * Solve the sudoku grid using the backtracking method
 *
 * grid: the grid to solve
 *
 * returns: | the solved grid | NULL if the grid is not solvable
 */
int **solve(int **grid)
{

    int **solved_grid = grid;

    if (is_board_solved(grid))
    {
        return grid;
    }

    // Find index of first empty cell
    int row = -1, column = -1;
    for (int i = 0; i < 9; i++)
    {
        if (row == -1)
        {
            for (int j = 0; j < 9; j++)
            {
                if (row == -1)
                {
                    if (grid[i][j] == 0)
                    {
                        row = i;
                        column = j;
                    }
                }
            }
        }
    }

    int **old_grid;

    // Test all numbers
    for (int i = 1; i < 10; i++)
    {
        solved_grid[row][column] = i;

        if (check_grid(solved_grid))
        {
            old_grid = solved_grid;
            solved_grid = solve(solved_grid);

            if (solved_grid == NULL)
            {
                solved_grid = old_grid;
            }
            else
            {
                return solved_grid;
            }
        }
        solved_grid[row][column] = 0;
    }

    return NULL;
}

/*
 * Function: write_grid
 * --------------------
 *
 * Write the solved grid in the filename.result file
 *
 * grid: the solved grid
 * filename: the file where the unsolved grid is
 *
 */
void write_grid(int **grid, char *filename)
{

    char result[strlen(filename) + 6];
    char *extension = ".result";
    strcpy(result, filename);

    FILE *fp = fopen(strcat(result, extension), "w");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j == 3 || j == 6)
            {
                fputc(' ', fp);
            }
            if (grid[i][j] == 0)
                fputc('.', fp);
            else
                fputc(grid[i][j] + '0', fp);
        }
        if (i == 2 || i == 5)
        {
            fputc('\n', fp);
        }
        fputc('\n', fp);
    }

    fclose(fp);
}

/*
 * Function: print_grid
 * --------------------
 *
 * Print the grid in stdout for debugging. The grid
 * is printed in the same style as it is in the file
 *
 * grid: the grid to print
 */
void print_grid(int **grid)
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j == 3 || j == 6)
            {
                printf(" ");
            }
            if (grid[i][j] == 0)
            {
                printf(".");
            }
            else
            {
                printf("%d", grid[i][j]);
            }
        }
        printf("\n");
        if (i == 2 || i == 5)
        {
            printf("\n");
        }
    }
}
