#include <stdlib.h>
#include <string.h>

typedef struct tetris
{
    Matrix *matrix;
    Tetramino* tetramino; // current tetramino selected, with all of his options
    int tetraminoType;
    int lastX; // last X position for the last tetramino
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

Tetramino *createTetramino(Tetramino *t)
{
    Tetramino *tetramino = (Tetramino *)malloc(sizeof(Tetramino));
    tetramino->code = t->code;
    tetramino->heigth = t->heigth;
    tetramino->width = t->width;
    tetramino->matrix = *createMatrix(t->matrix.cols, t->matrix.rows);

    for (int i = 0; i < t->matrix.cols * t->matrix.rows; i++)
    {
        tetramino->matrix.map[i] = t->matrix.map[i];
    }

    tetramino->offsetX = offsetX(t);
    tetramino->offsetY = offsetY(t);

    return tetramino;
}

void deleteTetramino(Tetramino *t)
{
    free(t);
}

Tetris *
createTetris(int cols, int rows)
{
    Tetris *tetris = (Tetris *)malloc(sizeof(Tetris));
    tetris->tetraminoType = 0;
    tetris->lastX = 0;

    tetris->tetramino = createTetramino(&tetramini[TETRAMINO_I]); // copy tetramino I from the array

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
int isIntersected(Matrix *tetrisMatrix, Tetramino *t, int x, int y)
{
    int startXTetramino = offsetX(t);
    int startYTetramino = offsetY(t);

    // printw("\nh: %d\nw: %d\nstart tetramino x: %d\nstart tetramino y: %d\nconsider this --> \n", t->heigth, t->width, startXTetramino, startYTetramino);

    for (int i = 0; i < t->heigth; i++)
    {
        for (int j = 0; j < t->width; j++)
        {
            // printf("%d ", i * t->matrix.cols + j);
            // printf("%d", t->matrix.map[(i+startYTetramino) * t->matrix.cols + (j + startXTetramino)]);
            // printf("%d", tetrisMatrix->map[(y+i) * tetrisMatrix->cols + (x+j)]);

            if (t->matrix.map[(i + startYTetramino) * t->matrix.cols + (j + startXTetramino)] == 1 && tetrisMatrix->map[(y + i) * tetrisMatrix->cols + (x + j)] == 1)
                return 1;
        }
    }

    return 0;
}

int checkYRowPiece(Matrix *tetrisMatrix, Tetramino *t, int x, int y)
{

    int counter = 0;
    for (int j = 0; j < t->width; j++)
    {
        if (tetrisMatrix->map[tetrisMatrix->cols * y + x + j] == 1)
            counter++;
    }

    return counter;
}

int findY(Matrix *tetrisMatrix, Tetramino *t, int x)
{
    int y, count = 0;

    for (y = 0; y < tetrisMatrix->rows - t->heigth + 1; y++)
    {
        // printw("[%d]\n", y);
        if (checkYRowPiece(tetrisMatrix, t, x, y) > 0) // if the row in the matrix is not empty u cant insert the new Tetramino
            return y - 1;
        if (isIntersected(tetrisMatrix, t, x, y))
            return y - 1;
        count++; // else increase counter
    }
    return count - 1;
}

int insertTetramino(Matrix *tetrisMatrix, Tetramino *t, int x, int y, int gravity)
{
    if (x > DEFAULT_WIDTH || x < 0 || y < 0)
        return 0; // impossible to insert

    int offX = offsetX(t), offY = offsetY(t);

    // printf("size    W:%d\n\tH: %d\noffset  X: %d\n\tY: %d\n", t->width, t->heigth, offX, offY);

    if (x + t->width <= DEFAULT_WIDTH)
    {
        // printf("intersected: %d\n", isIntersected(tetrisMatrix, t, x, 8));
        // printw("\n-->y: %d <--\n", findY(tetrisMatrix, t, x));

        if (gravity)                       // if set the tetramine will go to the bottom of the main matrix
            y = findY(tetrisMatrix, t, x); // y will be overwritten
        else
        {
            if (isIntersected(tetrisMatrix, t, x, y))
                return 0;
        }
        // its possible
        if (y < 0)
            return 0;
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
        return 1; // inserted
    }
    return 0; // not inserted
}

Matrix *rotateMatrix90Clockwise(Matrix *matrix)
{
    Matrix *trasposedMatrix = createMatrix(matrix->rows, matrix->cols); // invert cols with rows for future improvement

    // logic for calculate trasposed matrix
    for (int row = 0; row < matrix->rows; row++)
        for (int col = 0; col < matrix->cols; col++)
            trasposedMatrix->map[row * trasposedMatrix->cols + col] = matrix->map[col * matrix->rows + row];

    Matrix *rotatedMatrix90Clockwise = createMatrix(trasposedMatrix->rows, trasposedMatrix->cols); // invert for the same reason of before
    // reverse the order of cols
    for (int row = 0; row < matrix->rows; row++)
        for (int col = trasposedMatrix->cols - 1, j = 0; col > -1; col--, j++)
            rotatedMatrix90Clockwise->map[row * rotatedMatrix90Clockwise->cols + j] = trasposedMatrix->map[row * rotatedMatrix90Clockwise->cols + col];

    return rotatedMatrix90Clockwise;
}

Tetramino* rotateTetramino(Tetramino* t){
    int tetraminoCode = t->code;
    Matrix *rotated = rotateMatrix90Clockwise(&t->matrix);

    //deleteTetramino(t);
    Tetramino *tr = (Tetramino *)malloc(sizeof(Tetramino));

    tr->matrix = *rotated;
    tr->offsetX = offsetX(tr);
    tr->offsetY = offsetY(tr);
    tr->width = t->heigth;
    tr->heigth = t->width;

    return tr;
}