#include <stdlib.h>
#include <string.h>

typedef struct tetris
{
    Matrix *matrix;
    // score
    // gamemode
    // ecc...
} Tetris;

int testingMap[] = { // 10x7
    1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1};

Tetris *createTetris(int rows, int cols)
{
    Tetris *tetris = (Tetris *)malloc(sizeof(Tetris));
    //tetris->matrix = createMatrix(rows, cols); // the fuction returns the pointer of the created matrix
    //clearMatrix(tetris->matrix);               // set up the effective map to all 0

    //FOR TESTING THINGS
    tetris->matrix = createMatrix(7, 10);
    free(tetris->matrix->map);
    tetris->matrix->map = testingMap;
    //FOR TESTING THINGS

    return tetris;
}

void deleteTetris(Tetris *tetris)
{
    deleteMatrix(tetris->matrix);
    free(tetris);
}
