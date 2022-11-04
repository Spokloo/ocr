#include "../tools/image.h"
#include "matrix_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

/*
 * Fill mat with the homography matrix.
 * src : array of 4 points which are edge of detected grid
 * dst : array of 4 points which are edge of new square
 */
void get_homography_mat(float mat[9][9], int src[8], int dst[8])
{
    float P[9][9] = {
        {-src[0], -src[1], -1, 0, 0, 0, src[0]*dst[0], src[1]*dst[0], dst[0]},
        {0, 0, 0, -src[0], -src[1], -1, src[0]*dst[1], src[1]*dst[1], dst[1]},
        {-src[2], -src[3], -1, 0, 0, 0, src[2]*dst[2], src[3]*dst[2], dst[2]},
        {0, 0, 0, -src[2], -src[3], -1, src[2]*dst[3], src[3]*dst[3], dst[3]},
        {-src[4], -src[5], -1, 0, 0, 0, src[4]*dst[4], src[5]*dst[4], dst[4]},
        {0, 0, 0, -src[4], -src[5], -1, src[4]*dst[5], src[5]*dst[5], dst[5]},
        {-src[6], -src[7], -1, 0, 0, 0, src[6]*dst[6], src[7]*dst[6], dst[6]},
        {0, 0, 0, -src[6], -src[7], -1, src[6]*dst[7], src[7]*dst[7], dst[7]},
        {0, 0, 0, 0, 0, 0, 0, 0, 1}};
    float R[9][9] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {1}};
    //invert P
    if(inverse_mat(P, 9) == -1)
        errx(1, "Error when inversing matrix for perspective correction.");
    // multiply P^-1 and R
    float H[9][9];
    mult_mat(P, R, H, 9, 1, 9);
    // convert H in 3*3 matrix
    unsigned char h_index = 0;
    for (unsigned char i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat[i][j] = H[h_index][0];
            h_index++;
        }
    }
    if(inverse_mat(mat, 3) == -1)
        errx(1, "Error when inversing matrix for perspective correction.");
}

/*
 * Correct perspective on image depending on grid position in src.
 */
void correct_perspective(Image *img, int src[8])
{
    //Compute length between each points
    unsigned int top_length = sqrt(pow(src[0] - src[2], 2)
                                                    + pow(src[1] - src[3], 2));
    unsigned int right_length = sqrt(pow(src[2] - src[4], 2)
                                                    + pow(src[3] - src[5], 2));
    unsigned int bottom_length = sqrt(pow(src[4] - src[6], 2)
                                                    + pow(src[5] - src[7], 2));
    unsigned int left_length = sqrt(pow(src[6] - src[0], 2)
                                                    + pow(src[7] - src[1], 2));
    
    //new image will be a square
    //get max length which represent the length of the sides of our new grid
    int max_length = fmax(fmax(top_length, bottom_length), 
                                            fmax(right_length, left_length));
    int dst[8] = 
                {0, 0, max_length, 0, max_length, max_length, 0, max_length};

    float H[9][9];
    get_homography_mat(H, src, dst);

    //create new image size
    Image original_img;
    copy_image(img, &original_img);
    free_image(img);
    img->height = max_length;
    img->width = max_length;
    img->matrix = malloc(img->width * sizeof(Pixel*));
    if(img->matrix == NULL)
        errx(1, "Error during allocation of pixels' matrix in perspective correction.");

    int new_x, new_y;
    float res[9][9];
    float org[9][9] = {{0}, {0}, {1}};
    for (unsigned int x = 0; x < img->width; x++)
    {
        img->matrix[x] = malloc(img->height * sizeof(Pixel));
        if(img->matrix[x] == NULL)
            errx(1, "Error during allocation of pixels' matrix in perspective correction.");

        for (unsigned int y = 0; y < img->height; y++)
        {
            org[0][0] = x;
            org[1][0] = y;
            mult_mat(H, org, res, 3, 1, 3);
            new_x = res[0][0] / res[2][0];
            new_y = res[1][0] / res[2][0];
            img->matrix[x][y] = original_img.matrix[new_x][new_y];
        }
    }
    free_image(&original_img);
}