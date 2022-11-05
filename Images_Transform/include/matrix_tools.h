#ifndef MATRIX_TOOLS_H
#define MATRIX_TOOLS_H

/*
 * Inverse matrix in place. Max size: 9.
 * Return -1 if matrix can't be inverted.
 */
char inverse_mat(float mat[9][9], unsigned char size);

/*
 * Multiply two matrix and save in result matrix.
 * r1: number of rows in mat1
 * c2: number of columns in mat2
 * r2: number of rows in mat2
 */
void mult_mat(float mat1[9][9], float mat2[9][9], float result[9][9],
                        unsigned char r1, unsigned char c2, unsigned char r2);

#endif