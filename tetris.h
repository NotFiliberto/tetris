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

/* 
    \brief check if 2 matrix are intersected each other
 */
int isIntersected(Matrix* tetrisMatrix, Tetramino *t, int x, int y){
    int startXTetramino = offsetX(t);
    int startYTetramino = offsetY(t);

    //printf("\nh: %d\nw: %d\nstart tetramino x: %d\nstart tetramino y: %d\nconsider this --> \n", t->heigth, t->width, startXTetramino, startYTetramino);

    for (int i = 0; i < t->heigth; i++)
    {
        for (int j = 0; j < t->width; j++)
        {
            //printf("%d ", i * t->matrix.cols + j);
            //printf("%d", t->matrix.map[(i+startYTetramino) * t->matrix.cols + (j + startXTetramino)]);
            //printf("%d", tetrisMatrix->map[(y+i) * tetrisMatrix->cols + (x+j)]);

            if (t->matrix.map[(i + startYTetramino) * t->matrix.cols + (j + startXTetramino)] == 1 && tetrisMatrix->map[(y + i) * tetrisMatrix->cols + (x + j)] == 1)
                return 1;
        }
    }

    return 0;
}

int findY(Matrix *tetrisMatrix, Tetramino *t, int x){
    int y, count=0;

    for(y=0; y<tetrisMatrix->rows-t->heigth+1; y++){
        //printf("[%d]\n", y);
        if(isIntersected(tetrisMatrix, t, x, y)){
            return y-1;
        } else  
            count++;
    }
    return count-1;
}

void insertTetramino(Matrix *tetrisMatrix, Tetramino *t, int x){
    if (x > DEFAULT_WIDTH)
        EXIT_FAILURE; // impossible to insert over the width

    int offX = offsetX(t), offY = offsetY(t), y=0;

    printf("size    W:%d\n\tH: %d\noffset  X: %d\n\tY: %d\n", t->width,t->heigth,offX, offY);

    if (x + t->width <= DEFAULT_WIDTH)
    {
        //printf("intersected: %d\n", isIntersected(tetrisMatrix, t, x, 8));
        //printf("\n-->y: %d <--\n", findY(tetrisMatrix, t, x));

        y = findY(tetrisMatrix, t, x);
            // its possible
            for (int row = offY; row < t->matrix.rows; row++)
        {
            for (int col = offX; col < t->matrix.cols; col++)
            {
                if (t->matrix.map[(col) + row * t->matrix.cols] == 1)
                {
                    tetrisMatrix->map[(col + x - offX) + (row + y - offY) * tetrisMatrix->cols] = 1;
                }
            }
        }
    }
}