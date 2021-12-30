#include "stdio.h"
#include "stdlib.h"

typedef struct Matrix
{
    int cols;
    int rows;
    int *map;
} Matrix;

Matrix *createMatrix(int cols, int rows)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->cols = cols;
    matrix->rows = rows;

    // matrix->map = (int **)malloc(sizeof(int) * rows);
    //  for (int row = 0; row < rows; row++)
    //      matrix->map[row] = (int *)malloc(sizeof(int) * cols);

    matrix->map = (int *)malloc(sizeof(int) * rows * cols);

    return matrix;
}

void deleteMatrix(Matrix *matrix)
{
/*     for (int i = 0; i < (matrix->rows * matrix->cols); i++)
        free(&matrix->map[i]); */
    free(matrix);
}

void printMatrix(Matrix *matrix)
{
    for (int row = 0; row < matrix->rows; row++)
    {
        for (int col = 0; col < matrix->cols; col++)
        {
            if (matrix->map[col + row * matrix->cols] == 1)
                printw("%c", '@');
            else
                printw("%c", '.');
        }
        printw("\n");
    }
}

void clearMatrix(Matrix *matrix)
{
    for (int row = 0; row < matrix->rows; row++)
    {
        for (int col = 0; col < matrix->cols; col++)
        {
            matrix->map[col + row * matrix->cols] = 0;
        }
    }
}