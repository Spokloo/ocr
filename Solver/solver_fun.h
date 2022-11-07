#ifndef SOLVER_FUN_H
#define SOLVER_FUN_H

int** convert(char * filename);
int check_line(int** grid, int line);
int check_column(int** grid, int column);
int check_square(int** grid, int start_x, int start_y);
int check_grid(int** grid);
int is_board_solved(int** grid);
int** solve(int** grid);
void write_grid(int** grid, char * filename);
void print_grid(int** grid);

#endif
