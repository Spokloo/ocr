#include "../include/auto_rotation.h"
#include "../include/houghtransform.h"
#include "../../Tools/image.h"
#include "../../Tools/rotate.h"
#include <stdio.h>
#include <stdlib.h>

int is_in_list(int *arr, unsigned int len, int element) {
    for (unsigned int i = 0; i < len; i++)
        if (arr[i] == element)
            return i;
    return -1;
}

int get_rotated_angle(int **lines, unsigned int len, int theta)
{
    int nb_thetas = len;
    int *total_thetas = malloc(sizeof(int) * nb_thetas);
    for (int i = 0; i < nb_thetas; i++)
        total_thetas[i] = 0;

    int *t_votes = malloc(sizeof(int) * nb_thetas);
    for (int i = 0; i < nb_thetas; i++)
        t_votes[i] = 0;

    for (unsigned int i = 0; i < len; i++)
    {
        int in_list = is_in_list(total_thetas, nb_thetas, lines[i][1]);
        if (in_list == -1)
        {
            total_thetas[i] = lines[i][1];
            t_votes[i] = 1;
        }
        else
        {
            total_thetas[i] = theta;
            t_votes[in_list]++;
        }
    }

    int max = 0;
    for (int i = 0; i < nb_thetas; i++)
    {
        if (t_votes[i] > max)
            max = i;
    }

    int angle = total_thetas[max];

    free(total_thetas);
    free(t_votes);

    if (angle < 10 || abs(angle - 90) < 10 || abs(angle - 180) < 10)
        return 0;

    return angle;
}

void auto_rotation(Image *img, Image *copy_img, unsigned int *lines_len, int ***real_lines, Image ***result_imgs)
{
    // Auto rotating the image
    int theta = 180;
    int angle = get_rotated_angle(*real_lines, *lines_len, theta);
    char *path = "results/step_01b_auto_rotation.jpeg";

    if (angle != 0)
    {
        rotate(copy_img, -angle);

        int **tmp_lines = NULL;
        hough_transform(copy_img, lines_len, &tmp_lines);

        // Copying tmp_lines into real_lines then freeing tmp_lines
        for (unsigned int i = 0; i < *lines_len; i++)
        {
            for (int j = 0; j < 3; j++)
                (*real_lines)[i][j] = tmp_lines[i][j];
        }

        for (unsigned int i = 0; i < *lines_len; i++)
            free(tmp_lines[i]);
        free(tmp_lines);

        copy_image(copy_img, img);

        // Storing image
        (*result_imgs)[1] = copy_img;
        save_image(copy_img, path);
    } else
    {
        remove(path);
        (*result_imgs)[1] = NULL;
    }

    free_image(copy_img);
}

