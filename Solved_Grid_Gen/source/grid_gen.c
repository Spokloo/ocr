#include "grid_gen.h"
#include <string.h>

int is_pixel_same(Pixel *p1, Pixel *p2)
{
    return (p1->r == p2->r && p1->g == p2->g && p1->b == p2->b);
}

void place_img(Image *dest, Pixel *color, int digit, int x, int y)
{
    //char *path = malloc(17 * sizeof(char));
    //sprintf(path, "images/num_%d.png", digit);
    char *path = malloc(34 * sizeof(char));
    sprintf(path, "Solved_Grid_Gen/images/num_%d.png", digit);

    Image digit_img = load_image(path);
    unsigned int width = digit_img.width + x, height = digit_img.height + y;
    Pixel *white = malloc(sizeof(Pixel));
    white->r = white->g = white->b = 255;

    for (unsigned int i = x; i < width; i++)
    {
        for (unsigned int j = y; j < height; j++)
        {
            dest->matrix[i][j] = is_pixel_same(white, &digit_img.matrix[i - x][j - y]) ? *white : *color;
        }
    }

    free_image(&digit_img);
    free(path);
    free(white);
}

void construct_grid(char *grid_path, char *blank_grid_path, char *save_path)
{
    char solved_path[strlen(grid_path) + 8];
    strcpy(solved_path, grid_path);
    strcat(solved_path, ".result");
    int **old_grid = load_grid(grid_path);
    int **solved_grid = load_grid(solved_path);
    Image grid_img = load_image(blank_grid_path);
    int x = 8, y = 8;

    Pixel normal_color = {.r = 0, .g = 0, .b = 0};
    Pixel new_color = {.r = 255, .g = 0, .b = 0};

    for (unsigned int i = 0; i < 9; i++)
    {
        for (unsigned int j = 0; j < 9; j++)
        {
            if (old_grid[i][j] != solved_grid[i][j])
            {
                place_img(&grid_img, &new_color, solved_grid[i][j], x, y);
            }
            else
                place_img(&grid_img, &normal_color, solved_grid[i][j], x, y);

            if (j == 2 || j == 5)
            {
                x += 4;
            }
            x += 104;
        }
        if (i == 2 || i == 5)
        {
            y += 4;
        }
        y += 104;
        x = 8;
    }
    for(int i = 0; i < 9; i++)
    {
        free(old_grid[i]);
        free(solved_grid[i]);
    }
    free(old_grid);
    free(solved_grid);
    save_image(&grid_img, save_path);
    free_image(&grid_img);
}

void printHelp()
{
    printf("Incorrect number of arguments\n");
    printf("Usage: ./grid_gen <old_grid> <solved_grid>\n");
}
