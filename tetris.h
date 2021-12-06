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
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0};

Tetris *createTetris(int cols, int rows)
{
    Tetris *tetris = (Tetris *)malloc(sizeof(Tetris));
    // tetris->matrix = createMatrix(rows, cols); // the fuction returns the pointer of the created matrix
    // clearMatrix(tetris->matrix);               // set up the effective map to all 0

    // FOR TESTING THINGS
    tetris->matrix = createMatrix(7, 10);
    free(tetris->matrix->map);
    tetris->matrix->map = testingMap;
    // FOR TESTING THINGS

    return tetris;
}

void deleteTetris(Tetris *tetris)
{
    deleteMatrix(tetris->matrix);
    free(tetris);
}

void insertTetramino(Matrix *tetrisMatrix, Tetramino *t, int x)
{
    if (x > DEFAULT_WIDTH)
        EXIT_FAILURE; // impossible to insert over the width

    int h, w, offX = offsetX(t), offY=offsetY(t);
    tetraminoSize(t, &w, &h);

    printf("offset  X: %d\n\tY: %d\n", offX, offY);

    if (x + w <= DEFAULT_WIDTH)
    {
        // its possible
        for (int row = offY; row < t->matrix.rows; row++)
        {
            for (int col = offX; col < t->matrix.cols; col++)
            {
                if (t->matrix.map[(col) + row * t->matrix.cols] == 1){
                    tetrisMatrix->map[(col + x - offX) + (row - offY) * tetrisMatrix->cols] = 1;
                }
            }

        }
    }
}
