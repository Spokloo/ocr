#include "matrix_tools.h"
#include <math.h>

/*For calculating determinant of the matrix */
float determinant(float a[9][9], unsigned char k)
{
    float s = 1, det = 0, b[9][9];
    int i, j, m, n, c;
    if (k == 1)
        return (a[0][0]);
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }

    return det;
}

/*Finding transpose of matrix*/
void transpose(float num[9][9], float fac[9][9], float r)
{
    int i, j;
    float b[9][9], d;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
            b[i][j] = fac[j][i];
    }
    d = determinant(num, r);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
            num[i][j] = b[i][j] / d;
    }
}

void cofactor(float num[9][9], float f)
{
    float b[9][9], fac[9][9];
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++)
    {
        for (p = 0; p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++)
            {
                for (j = 0; j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);
}

/*
 * Inverse matrix in place. Max size: 9.
 * Return -1 if matrix can't be inverted.
 */
char inverse_mat(float mat[9][9], unsigned char size)
{
    float d = determinant(mat, size);
    if (d == 0) // impossible to inverse matrix
        return -1;
    else
        cofactor(mat, size);
    return 0;
}

/*
 * Multiply two matrix and save in result matrix.
 * r1: number of rows in mat1
 * c2: number of columns in mat2
 * r2: number of rows in mat2
 */
void mult_mat(float mat1[9][9], float mat2[9][9], float result[9][9],
              unsigned char r1, unsigned char c2, unsigned char r2)
{
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < r2; k++)
                result[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}