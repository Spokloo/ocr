#include "nn_load_data.h"
#include <dirent.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Check if the path have the correct format: being a folder and contains
 * only 10 folders 0-9.
 */
void verif_format(char *path)
{
    int nb;
    int dirname[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    DIR *dp = NULL;
    struct dirent *ep = NULL;
    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir(dp)) != NULL)
        {
            if (ep->d_name[0] == '.')
                continue;
            else
            {
                nb = atoi(ep->d_name);
                if ((nb == 0 && strcmp(ep->d_name, "0") != 0) || nb < 0 ||
                    nb > 10 || dirname[nb] != -1)
                    errx(1, "Wrong directory format when training the Neural "
                            "Network.");
                dirname[nb] = 0;
            }
        }
        closedir(dp);
        for (unsigned char i = 0; i < NB_TRAINING_SET; ++i)
        {
            if (dirname[i] == -1)
                errx(1, "Wrong directory format when training the Neural "
                        "Network.");
        }
    }
    else
        errx(1,
             "Couldn't open the directory when training the Neural Network.");
}

/*
 * Return the number of files inside a folder.
 */
unsigned int files_nb(char *path)
{
    unsigned int res = 0;
    DIR *dp = NULL;
    struct dirent *ep = NULL;
    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir(dp)) != NULL)
        {
            if(ep->d_name[0] != '.')
                res++;
        }
        closedir(dp);
        return res;
    }
    else
    {
        errx(1,
             "Couldn't open a sub-directory when training the Neural Network.");
        return -1;
    }
}

/*
 * Get the minimum of numbers of files on sub-folders.
 */
unsigned int get_examples_size(char *path)
{
    // Neural Network need the same nb of each image numbers so get the minimum
    // of all sub-folders to train for min images of each numbers
    unsigned int n = strlen(path), nb = 0, min = 65535;
    char subpath[n + 3];
    strncpy(subpath, path, n);
    subpath[n] = '/';
    n++;

    for (char i = 0; i < NB_TRAINING_SET; i++)
    {
        subpath[n] = i + '0';
        nb = files_nb((char *)subpath); // remove . and ..
        if (nb < min)
            min = nb;
    }
    return min;
}

/*
 * Load images matrix and expected results into variables.
 */
void load_data(char *path, NnDatas *data)
{
    unsigned int n = strlen(path), sum = 0;
    unsigned long i_input = 0;
    char subpath[128];
    strncpy(subpath, path, n);
    subpath[n] = '/';
    n++;
    subpath[n + 1] = '/';
    DIR *dp = NULL;
    struct dirent *ep = NULL;

    //fill expected array
    for (unsigned int nb = 0; nb < NB_TRAINING_SET; nb++)
    {
        for (unsigned char i = 0; i < NB_OUTPUT; i++)
        {
            if (i == nb)
                data->expected[nb][i] = 1;
            else
                data->expected[nb][i] = 0;
        }
    }

    //fill input and expected arrays
    for (unsigned int nb = 0; nb < NB_TRAINING_SET; nb++) // each numbers
    {
        sum = 0;
        i_input = 0;
        subpath[n] = nb + '0';
        subpath[n + 2] = '\0';
        dp = opendir(subpath);
        if (dp != NULL)
        {
            while (sum < data->max_ex && (ep = readdir(dp)) != NULL)
            {                             // each files in number folder
                if (ep->d_name[0] != '.') // avoid cached files
                {
                    subpath[n + 2] = '\0';
                    strcat(subpath, ep->d_name);
                    //printf("%s\n", subpath);
                    sum++;
                    data->total++;
                    
                    Image img = load_image(subpath);
                    if (img.width != 28 || img.height != 28)
                        errx(1, "Wrong image format when training the Neural "
                                "Network. Images should be 28*28 pixels.");
                    for (unsigned char j = 0; j < 28; j++)
                    {
                        for (unsigned char k = 0; k < 28; k++, i_input++)
                            data->input[nb][i_input] = img.matrix[k][j].r / 255;
                    }
                    free_image(&img);
                }
            }
            closedir(dp);
        }
        else
        {
            errx(1, "Couldn't open a sub-directory when training the "
                    "Neural Network.");
        }
    }
}

/*
 * Free training data.
 */
void free_data(NnDatas *data)
{
    for (unsigned char i = 0; i < NB_TRAINING_SET; i++)
    {
        free(data->input[i]);
        free(data->expected[i]);
    }
    free(data->input);
    free(data->expected);
}

/*
 * Load all images on a folder and sub-folders of numbers into matrix.
 */
NnDatas load_training_images(char *path)
{
    NnDatas data;
    verif_format(path);
    unsigned int len = get_examples_size(path);
    data.total = 0;
    data.max_ex = len;
    data.input = malloc(NB_TRAINING_SET * sizeof(char *));
    data.expected = malloc(NB_TRAINING_SET * sizeof(char *));
    for (unsigned char i = 0; i < NB_TRAINING_SET; i++)
    {
        data.input[i] = malloc(len * NB_INPUT * sizeof(char));
        data.expected[i] = malloc(NB_OUTPUT * sizeof(char));
    }
    load_data(path, &data);
    /*for (unsigned int i = 0; i < 10; i++)
    {
        for (unsigned int j = 0; j < 10; j++)
        {
            printf("%d  ", data.expected[i][j]);
        }
        printf("\n");
    }*/
    // free_data(input, expected);
    return data;
}