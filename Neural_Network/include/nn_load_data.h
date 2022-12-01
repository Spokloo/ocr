#ifndef NN_LOAD_DATA_H
#define NN_LOAD_DATA_H

#include "nn.h"
#include "image.h"

/*
 * Free training data. 
 */
void free_data(NnDatas *data);

/*
 * Load all images on a folder and sub-folders of numbers into matrix.
 */
NnDatas load_training_images(char *path);

#endif