#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    unsigned int row;
    unsigned int col;
    float *data;
} Matrix;

static inline Matrix create_matrix(unsigned rows, unsigned cols)
{
    Matrix matrix;
    matrix.row = rows;
    matrix.col = cols;
    matrix.data = (float*) calloc(rows * cols, sizeof(float));
    if (!matrix.data)
    {
        printf("Failed to create matrix: rows: %i cols: %i", rows, cols);
    }

    return matrix;
}

static inline float *get_mat_element(Matrix *matrix, unsigned int row, unsigned int col)
{
    // To get a value use: float value = *get_mat_element(&mat, ROW, COL);
    // To set a value use: *get_mat_element(&mat, ROW, COL) = float value;

    if (row > matrix->row || col > matrix->col)
    {
        printf("Tried to access element outside matrix\n");
    }

    return matrix->data + row * matrix->col + col;
}

static inline void free_matrix(Matrix *matrix)
{
    if (matrix->data)
    {
        free(matrix->data);
        matrix->data = NULL;
    }
}

static inline Matrix create_identitiy_mat(unsigned int size)
{
    Matrix identity = create_matrix(size, size);

    for (unsigned int i = 0; i < size; i++)
    {
        *get_mat_element(&identity, i, i) = 1.0f;
    }

    return identity;
}

static inline void print_matrix(Matrix *matrix)
{
    for (unsigned int i = 0; i < matrix->row; i++)
    {
        for (unsigned int j = 0; j < matrix->col; j++)
        {
            printf("%f ", *get_mat_element((Matrix*)matrix, i, j));
        }
        printf("\n");
    }
}

static inline int add_matrix(Matrix *result, Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->row != mat_b->row && mat_a->col != mat_b->col)
    {
        printf("Error matrix dimensions do not match for addition!\n");
        return 1;
    }
    else
    {
        for (unsigned int i = 0; i < mat_a->row; i++)
        {
            for (unsigned int j = 0; j < mat_a->col; j++)
            {
                *get_mat_element((Matrix*)result, i, j) = *get_mat_element((Matrix*)mat_a, i, j) + *get_mat_element((Matrix*)mat_b, i, j);
            }
        }
        
        return 0;
    }
}

static inline int sub_matrix(Matrix *result, Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->row != mat_b->row || mat_a->col != mat_b->col)
    {
        printf("Error matrix dimensions do not match for subtraction!\n");
        return 1;
    }
    else
    {
        for (unsigned int i = 0; i < mat_a->row; i++)
        {
            for (unsigned int j = 0; j < mat_a->col; j++)
            {
                *get_mat_element((Matrix*)result, i, j) = *get_mat_element((Matrix*)mat_a, i, j) - *get_mat_element((Matrix*)mat_b, i, j);
            }
        }
    
        return 0;
    }
}

static inline int mult_matrix(Matrix *result, Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->col != mat_b->row)
    {
        printf("Cols != Rows\n");
        return 1;
    }

    for (unsigned int i = 0; i < mat_a->row; i++)
    {
        for (unsigned int j = 0; j < mat_b->col; j++)
        {
            float sum = 0.0f;

            for (unsigned int k = 0; k < mat_a->col; k++)
            {
                sum += *get_mat_element((Matrix*)mat_a, i, k) * *get_mat_element((Matrix*)mat_b, k, j);
            }

            *get_mat_element(result, i, j) = sum;
        }
    }
}

static inline void scale_matrix(Matrix *result, Matrix *mat, float scalar)
{
    for (unsigned int i = 0; i < mat->row; i++)
    {
        for (unsigned int j = 0; j < mat->col; j++)
        {
            *get_mat_element((Matrix*)result, i, j) = *get_mat_element((Matrix*)mat, i, j) * scalar;
        }
    }
}

static inline Matrix create_mat4x4_rot_x(float angle)
{
    Matrix mat = create_matrix(4, 4);

    // Col 1:
    *get_mat_element(&mat, 0, 0) = 1;
    *get_mat_element(&mat, 1, 0) = 0;
    *get_mat_element(&mat, 2, 0) = 0;
    *get_mat_element(&mat, 3, 0) = 0;
    // Col 2:
    *get_mat_element(&mat, 0, 1) = 0;
    *get_mat_element(&mat, 1, 1) = cos(angle);
    *get_mat_element(&mat, 2, 1) = sin(angle);
    *get_mat_element(&mat, 3, 1) = 0;
    // Col 3:
    *get_mat_element(&mat, 0, 2) = 0;
    *get_mat_element(&mat, 1, 2) = -sin(angle);
    *get_mat_element(&mat, 2, 2) = cos(angle);
    *get_mat_element(&mat, 3, 2) = 0;
    // Col 4:
    *get_mat_element(&mat, 0, 3) = 0;
    *get_mat_element(&mat, 1, 3) = 0;
    *get_mat_element(&mat, 2, 3) = 0;
    *get_mat_element(&mat, 3, 3) = 1;

    return mat;
}

static inline Matrix create_mat4x4_rot_y(float angle)
{
    Matrix mat = create_matrix(4, 4);

    // Col 1:
    *get_mat_element(&mat, 0, 0) = cos(angle);
    *get_mat_element(&mat, 1, 0) = 0;
    *get_mat_element(&mat, 2, 0) = -sin(angle);
    *get_mat_element(&mat, 3, 0) = 0;
    // Col 2:
    *get_mat_element(&mat, 0, 1) = 0;
    *get_mat_element(&mat, 1, 1) = 1;
    *get_mat_element(&mat, 2, 1) = 0;
    *get_mat_element(&mat, 3, 1) = 0;
    // Col 3:
    *get_mat_element(&mat, 0, 2) = sin(angle);
    *get_mat_element(&mat, 1, 2) = 0;
    *get_mat_element(&mat, 2, 2) = cos(angle);
    *get_mat_element(&mat, 3, 2) = 0;
    // Col 4:
    *get_mat_element(&mat, 0, 3) = 0;
    *get_mat_element(&mat, 1, 3) = 0;
    *get_mat_element(&mat, 2, 3) = 0;
    *get_mat_element(&mat, 3, 3) = 1;

    return mat;
}

static inline Matrix create_mat4x4_rot_z(float angle)
{
    Matrix mat = create_matrix(4, 4);

    // Col 1:
    *get_mat_element(&mat, 0, 0) = cos(angle);
    *get_mat_element(&mat, 1, 0) = sin(angle);
    *get_mat_element(&mat, 2, 0) = 0;
    *get_mat_element(&mat, 3, 0) = 0;
    // Col 2:
    *get_mat_element(&mat, 0, 1) = -sin(angle);
    *get_mat_element(&mat, 1, 1) = cos(angle);
    *get_mat_element(&mat, 2, 1) = 0;
    *get_mat_element(&mat, 3, 1) = 0;
    // Col 3:
    *get_mat_element(&mat, 0, 2) = 0;
    *get_mat_element(&mat, 1, 2) = 0;
    *get_mat_element(&mat, 2, 2) = 1;
    *get_mat_element(&mat, 3, 2) = 0;
    // Col 4:
    *get_mat_element(&mat, 0, 3) = 0;
    *get_mat_element(&mat, 1, 3) = 0;
    *get_mat_element(&mat, 2, 3) = 0;
    *get_mat_element(&mat, 3, 3) = 1;

    return mat;
}