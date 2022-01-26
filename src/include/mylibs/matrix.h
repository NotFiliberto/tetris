/**
 * @file matrix.h
 * @brief Useful library for matrix
 *
 */

#include "stdio.h"
#include "stdlib.h"

/** @struct Matrix
 * @brief Matrix rappresentation
 *
 * @param cols columns of the matrix
 * @param rows rows of the matrix
 * @param map array that rappresents evey value of the matrix
 */
typedef struct Matrix
{
    int cols;
    int rows;
    int *map;
} Matrix;

/**
 * @brief Create a Matrix object
 *
 * @param cols matrix's columns
 * @param rows matrix's rows
 * @return the matrix created
 */
Matrix *createMatrix(int cols, int rows)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->cols = cols;
    matrix->rows = rows;
    matrix->map = (int *)malloc(sizeof(int) * rows * cols);
    return matrix;
}

/**
 * @brief delete matrix, free memory space used by the matrix gived in input
 *
 * @param matrix matrix to delete
 */
void deleteMatrix(Matrix *matrix)
{
    free(matrix);
}

/**
 * @brief print the matrix in the terminal screen
 *
 * @param matrix the matrix to be printed
 */
void printMatrix(Matrix *matrix)
{
    int row = 0, col = 0;
    for (row = 0; row < matrix->rows; row++)
    {
        for (col = 0; col < matrix->cols; col++)
        {
            if (matrix->map[col + row * matrix->cols] == 1)
                printw("%c", '@');
            else
                printw("%c", '.');
        }
        printw("\n");
    }
}

/**
 * @brief clear every index of the matrix, repleace every index of the matrix with a 0
 *
 * @param matrix the matrix to be cleared
 */
void clearMatrix(Matrix *matrix)
{
    int row = 0, col = 0;
    for (row = 0; row < matrix->rows; row++)
    {
        for (col = 0; col < matrix->cols; col++)
        {
            matrix->map[col + row * matrix->cols] = 0;
        }
    }
}