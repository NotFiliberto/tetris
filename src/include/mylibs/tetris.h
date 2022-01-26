/**
 * @file tetris.h
 * @brief Library for tetris game logic
 */

#include <stdlib.h>
#include <string.h>

/** @struct Tetris
 * @brief tetris object session
 * rappresent a single tetris game session with all of his game stuffs (map, score, ext...)
 * @param matrix the matrix of the session
 * @param tetramino current tetramino selected, with all of his settings (offset, widht, height, ext...)
 * @param tetraminoType current type of tetramino selected by the player
 * @param lastX the position based on the "x axis" of the tetramino moved by the user
 * @param availableTetramini array that contains the avaibility for every piece
 * @param tetrisStatus status of the current tetris "session"
 */
typedef struct tetris
{
    Matrix *matrix;
    Tetramino *tetramino;
    int tetraminoType;
    int lastX;
    int score;
    int *availableTetramini;
    int tetrisStatus;
} Tetris;

/**
 * @brief testing map, useful testing map for testing things and new features
 */
int testingMap[] = {/* 10x7 */
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

/**
 * @brief Create a Tetramino object
 *
 * @param t the model of the tetramino
 * @return Tetramino object
 */
Tetramino *createTetramino(Tetramino *t)
{
    Tetramino *tetramino = (Tetramino *)malloc(sizeof(Tetramino));
    tetramino->code = t->code;
    tetramino->heigth = t->heigth;
    tetramino->width = t->width;
    tetramino->matrix = *createMatrix(t->matrix.cols, t->matrix.rows);

    int i = 0;
    for (i = 0; i < t->matrix.cols * t->matrix.rows; i++)
    {
        tetramino->matrix.map[i] = t->matrix.map[i];
    }

    tetramino->offsetX = offsetX(t);
    tetramino->offsetY = offsetY(t);

    return tetramino;
}

/**
 * @brief free memory used for a tetramino, delete and free the memory used by the tetramino in input
 *
 * @param t tetramino
 */
void deleteTetramino(Tetramino *t)
{
    free(t);
}

/**
 * @brief Create a Tetris object
 *
 * @param cols number of columns
 * @param rows number of rows
 * @return Tetris* object
 */
Tetris *
createTetris(int cols, int rows)
{
    Tetris *tetris = (Tetris *)malloc(sizeof(Tetris));
    tetris->tetraminoType = 0;
    tetris->lastX = 0;
    tetris->score = 0;
    tetris->tetrisStatus = 0; /* not finished */

    tetris->tetramino = createTetramino(&tetramini[TETRAMINO_I]); /* copy tetramino I from the array */

    tetris->matrix = createMatrix(cols, rows); /* the fuction returns the pointer of the created matrix */
    clearMatrix(tetris->matrix);               /* set up the effective map to all 0 */

    tetris->availableTetramini = (int *)malloc(sizeof(int) * 7); /* avaible tetramini */

    int i = 0;
    for (i = 0; i < 7; i++)
    {
        tetris->availableTetramini[i] = DEFAULT_AVAILABILITY;
    }

    return tetris;
}

/**
 * @brief free memory used for the tetris session, delete and free the memory used by the tetris session in input
 *
 * @param tetris tetris session
 *
 */
void deleteTetris(Tetris *tetris)
{
    deleteMatrix(tetris->matrix);
    free(tetris);
}

/**
 * @brief check if 2 matrix intersect each other, check if the tetramino collide with any point in the tetris map
 *
 * @param tetrisMatrix matrix of the tetris session
 * @param t tetramino that has to be checked
 * @param x x position in the tetris matrix session
 * @param y y position in the tetris matrix session
 * @return 1 if the two matrix have some common point otherwhise 0
 */
int isIntersected(Matrix *tetrisMatrix, Tetramino *t, int x, int y)
{
    int startXTetramino = offsetX(t);
    int startYTetramino = offsetY(t);

    int i = 0, j = 0;
    for (i = 0; i < t->heigth; i++)
    {
        for (j = 0; j < t->width; j++)
        {
            if (t->matrix.map[(i + startYTetramino) * t->matrix.cols + (j + startXTetramino)] == 1 && tetrisMatrix->map[(y + i) * tetrisMatrix->cols + (x + j)] == 1)
                return 1;
        }
    }

    return 0;
}

/**
 * @brief check if the y of the matrix for the width of the tetramino in a specif x is empty or not
 *
 * @param tetrisMatrix matrix of the tetris session
 * @param t tetramino in input
 * @param x position in the tetris matrix session
 * @param y y position in the tetris matrix session
 * @return a positive number > 0 if the y considered is full, so the tetramino cant be added in that coords
 */
int ySlotStatus(Matrix *tetrisMatrix, Tetramino *t, int x, int y)
{

    int counter = 0, j = 0;
    for (j = 0; j < t->width; j++)
    {
        if (tetrisMatrix->map[tetrisMatrix->cols * y + x + j] == 1)
            counter++;
    }

    return counter;
}

/**
 * @brief find (if possible) the current y for the tetramino that has to be inserted into tetris matrix map
 *
 * @param tetrisMatrix tetris matrix map
 * @param t tetramino to be inserted
 * @param x position in the tetris matrix map
 * @return the position (y) to insert the tetramino if possible, otherwhise -1
 */
int findY(Matrix *tetrisMatrix, Tetramino *t, int x)
{
    int y, count = 0, flag = -1, k = 0, z = 0;

    for (y = 0; y < tetrisMatrix->rows - t->heigth + 1; y++)
    {
        /* check the last row of tetramino with every row of tetris matrix for a "gravity check" */
        for (k = 0; k < t->heigth; k++)
        {
            for (z = 0; z < t->width; z++)
            {
                if (t->matrix.map[(t->heigth - 1 + offsetY(t)) * t->matrix.cols + (z + offsetX(t))] == 1 && tetrisMatrix->map[(y + k) * tetrisMatrix->cols + (x + z)] == 1)
                    return y - 1;
            }
        }

        if (ySlotStatus(tetrisMatrix, t, x, y)) /* if the row in the matrix is not empty u cant insert the new Tetramino */
            return y - 1;

        if (isIntersected(tetrisMatrix, t, x, y))
            return y - 1;

        count++; /* else increase counter */
    }
    return count - 1;
}

/**
 * @brief insert the tetramino into the tetris matrix map
 *
 * @param tetrisMatrix tetris matrix map
 * @param t tetramino to insert
 * @param x position
 * @param y position
 * @param gravity 1 if enabled
 * @param insertFLAG 1 if the fuction has to insert for real the tetramino
 * @return 1 if the tetramino is inserted in the tetris matrix map, otherwhise 0
 */
int insertTetramino(Matrix *tetrisMatrix, Tetramino *t, int x, int y, int gravity, int insertFLAG)
{
    if (x > DEFAULT_WIDTH || x < 0 || y < 0)
        return 0; /* impossible to insert */

    int offX = offsetX(t), offY = offsetY(t);

    if (x + t->width <= DEFAULT_WIDTH)
    {
        if (gravity)
        {                                  /* if set the tetramine will go to the bottom of the main matrix */
            y = findY(tetrisMatrix, t, x); /* y will be overwritten */
        }
        else
        {
            if (isIntersected(tetrisMatrix, t, x, y))
                return 0;
        }
        /* its possible */
        if (y < 0)
            return 0;

        int row, col;
        for (row = offY; row < t->matrix.rows; row++)
        {
            for (col = offX; col < t->matrix.cols; col++)
            {
                if (t->matrix.map[(col) + row * t->matrix.cols] == 1)
                {
                    if (insertFLAG == 1)
                    {                                                                                    /* if flag is true */
                        tetrisMatrix->map[(col + x - offX) + (row + y - offY) * tetrisMatrix->cols] = 1; /* insert */
                    }
                }
            }
        }
        return 1; /* inserted */
    }
    return 0; /* not inserted */
}

/**
 * @brief rotate square matrix 90° clockwhise
 *
 * @param matrix the matrix that has to be rotated
 * @return the matrix rotated
 */
Matrix *rotateMatrix90Clockwise(Matrix *matrix)
{
    Matrix *trasposedMatrix = createMatrix(matrix->rows, matrix->cols); /* invert cols with rows for future improvement */

    /* logic for calculate trasposed matrix */

    int row, col, j;
    for (row = 0; row < matrix->rows; row++)
        for (col = 0; col < matrix->cols; col++)
            trasposedMatrix->map[row * trasposedMatrix->cols + col] = matrix->map[col * matrix->rows + row];

    Matrix *rotatedMatrix90Clockwise = createMatrix(trasposedMatrix->rows, trasposedMatrix->cols); /* invert for the same reason of before */
    /* reverse the order of cols */
    for (row = 0; row < matrix->rows; row++)
        for (col = trasposedMatrix->cols - 1, j = 0; col > -1; col--, j++)
            rotatedMatrix90Clockwise->map[row * rotatedMatrix90Clockwise->cols + j] = trasposedMatrix->map[row * rotatedMatrix90Clockwise->cols + col];

    return rotatedMatrix90Clockwise;
}

/**
 * @brief rotate tetramino and update its related stuffs (offset, width, ecc...)
 *
 * @param t tetramino to rotate
 * @return tetramino rotated
 */
Tetramino *rotateTetramino(Tetramino *t)
{
    Matrix *rotated = rotateMatrix90Clockwise(&t->matrix);

    /* deleteTetramino(t); */
    Tetramino *tr = (Tetramino *)malloc(sizeof(Tetramino));

    tr->code = t->code;
    tr->matrix = *rotated;
    tr->offsetX = offsetX(tr);
    tr->offsetY = offsetY(tr);
    tr->width = t->heigth;
    tr->heigth = t->width;

    return tr;
}

/* =====================================
   ======= TETRAMINO AVAIBILITY ========
   ===================================== */

/**
 * @brief get the tetramino availabitlity for a specific tetramino
 *
 * @param tetris single tetris session
 * @param tetraminoCode the code of the tetramino
 * @return the current avaiability for the tetramino in input
 */
int tetraminoAvailability(Tetris *tetris, int tetraminoCode)
{
    return tetris->availableTetramini[tetraminoCode];
}

/**
 * @brief decrement the tetramino availabitliy for a specific tetramino
 *
 * @param tetris single tetris session
 * @param tetraminoCode the code of the tetramino
 * @return availabitliy of the tetramino in input if > 0, otherwhise -1
 */
int decrementTetraminoAvailability(Tetris *tetris, int tetraminoCode)
{
    if (tetris->availableTetramini[tetraminoCode] > 0)
        return --tetris->availableTetramini[tetraminoCode]; /* decrement  */
    return -1;
}

/**
 * @brief print the availabitliy of every type of tetramino in the screen
 *
 * @param tetris single tetris session
 * @param typesPerRow types of tetramino printed per row
 */
void printTetraminiAvailability(Tetris *tetris, int typesPerRow)
{
    init_pair(1, COLOR_WHITE, COLOR_CYAN);
    /* printw("[Current Type %c] > %d\n\n", typeToLetter(tetris->tetramino->code), tetris->availableTetramini[tetris->tetramino->code]);  */
    int i;
    for (i = 0; i < 7; i++)
    {
        if (i > 1 && i % (typesPerRow) == 0)
            printw("\n");
        if (i == tetris->tetramino->code)
        {
            init_color(COLOR_CYAN, 175, 238, 238);
            attron(COLOR_PAIR(1));
        }
        printw("[%c] > %d ", typeToLetter(i), tetris->availableTetramini[i]);
        if (i == tetris->tetramino->code)
            attroff(COLOR_PAIR(1));
    }
}

/**
 * @brief get the total availability for a specific game session
 *
 * @param tetris single game session
 * @return total availability for the specified game session
 */
int totalAvailability(Tetris *tetris)
{
    int tot = 0, i = 0;
    for (i = 0; i < 7; i++)
    {
        tot += tetris->availableTetramini[i];
    }
    return tot;
}

/**
 * @brief get the code of the next tetramino available based on the state of the provided tetris session, useful when u swap piece or u just insert new one
 *
 * @param tetris single tetris session
 * @return the code of the next tetramino available
 */
int nextTetraminoAvailable(Tetris *tetris)
{

    if (totalAvailability > 0)
    {
        int i = 0;
        for (i = 0; i < 7; i++)
        {
            if (tetraminoAvailability(tetris, (tetris->tetraminoType + i) % 7) > 0)
                return (tetris->tetraminoType + i) % 7;
        }
    }
    return -1; /* and the game is Over */
}

/**
 * @brief check if the tetris game session is over
 *
 * @param tetris single tetris session
 * @return 1 if the game is over otherwhise 0
 */
int gameOver(Tetris *tetris)
{
    if (totalAvailability(tetris) == 0)
        return 1; /* tetris game Over */

    /* first thing to do, find the first position of empty x */
    int pos = -1, i = 0;
    for (i = 0; i < tetris->matrix->cols && pos == -1; i++)
    {
        if (tetris->matrix->map[i] == 0)
            pos = i;
    }
    /* continue with the check */
    if (pos != -1)
    {
        Tetramino *tetramino;
        int rotation, col, pieceType;
        for (pieceType = 0; pieceType < 7; pieceType++)
        { /* for every piece */
            if (tetraminoAvailability(tetris, pieceType) > 0)
            { /* first check if the piece is avaible */
                tetramino = createTetramino(&tetramini[pieceType]);
                for (rotation = 0; rotation < 4; rotation++)
                { /* test every rotation */
                    for (col = 0; col < tetris->matrix->cols; col++)
                    {
                        if (insertTetramino(tetris->matrix, tetramino, col, 0, GRAVITY, 0))
                        { /* important to enable gravity */

                            /* printw("\n\ntype: %d, rotation: %d, x: %d\n\n", pieceType, rotation, col); */
                            return 0;
                        }
                    }
                    tetramino = rotateTetramino(tetramino);
                }
                deleteTetramino(tetramino); /* free memory */
            }
            else
            {
                /* otherwhise do nothing, dont check for this type of tetramino */
            }
        }
    }
    return 1;
}

/**
 * @brief remove row from tetris map
 *
 * @param tetris single tetris session
 * @param row index of row to remove from the map
 */
void removeRow(Tetris *tetris, int row)
{
    int startIndex = (row * tetris->matrix->cols + tetris->matrix->cols) - 1, i;
    for (i = startIndex; i > -1; i--)
    {
        if (i >= tetris->matrix->cols)
            tetris->matrix->map[i] = tetris->matrix->map[i - tetris->matrix->cols]; /* shift */
        else
            tetris->matrix->map[i] = 0; /* fill the first row with empty space */
    }
}

/**
 * @brief find rows that must be removed
 *
 * @param tetris single tetris session
 * @param size output param for the output array
 * @return return an array that cointans the index of the rows to remove
 */
int *findRowsToRemove(Tetris *tetris, int *size)
{

    (*size) = 0; /* default */
    int i, j, fullRow = 1;
    int *rowsToDelete = (int *)malloc(tetris->matrix->rows * sizeof(int));

    for (i = 0; i < tetris->matrix->rows; i++)
    {

        for (j = 0; j < tetris->matrix->cols && fullRow; j++)
        {
            if (tetris->matrix->map[i * tetris->matrix->cols + j] == 0)
                fullRow = 0; /* not fullRow, so i cant delete it */
        }

        if (fullRow)
        {                                /* row to delete */
            rowsToDelete[(*size)++] = i; /* increse size and save row index */
            /* printw("row do delete added: %d, size [%d]\n", rowsToDelete[(*size)-1], (*size)); */
        }
        fullRow = 1;
    }

    if ((*size) == 0)
        rowsToDelete[(*size)++] = -1; /* init, that means 0 rows found to remove */

    return rowsToDelete;
}

/**
 * @brief delete full rows and update game score
 *
 * @param tetris single tetris game session
 * @return points scored
 */
int scorePoints(Tetris *tetris)
{
    int size, *rowsToDelete = findRowsToRemove(tetris, &size), points = 0;
    int pointsBoard[] = {0, 1, 3, 6, 12, 20, 30};

    if (rowsToDelete[0] != -1)
    {

        /* points to assing based on calculated size */
        points = pointsBoard[size];
        int i;

        for (i = 0; i < size; i++)
        {
            removeRow(tetris, rowsToDelete[i]);
        }

        /* rowsToDelete = findRowsToRemove(tetris, &size); */
    }

    /* printw("\npoints: %d\n", points); */

    return points;
}

/**
 * @brief invert value of rows, if the cell contains 0 change it with 1
 *
 * @param row the row to invert
 * @param width size of the row
 */
void invertRow(int *row, int width)
{
    int i;
    for (i = 0; i < width; i++)
    {
        if (row[i] == 0)
            row[i] = 1;
        else
            row[i] = 0;
    }
}

/**
 * @brief invert values of tetris rows
 *
 * @param tetris single tetris game session
 * @param nrowsToInvert number of rows to invert
 */
void invertTetrisRows(Tetris *tetris, int nrowsToInvert)
{
    int i = 0;
    for (i = 0; i < nrowsToInvert; i++)
    {
        invertRow(&tetris->matrix->map[tetris->matrix->cols * (tetris->matrix->rows - i - 1)], tetris->matrix->cols);
    }
}

/**
 * @brief check if the game has a winner or not
 *
 * @param tetris tetris array
 * @param numberOfPlayers number of players
 * @return return -1 if the two players have the same score otherwhise return the index of the winner based on the position of his tetris game session
 */
int getWinner(Tetris **tetris, int numberOfPlayers)
{
    int winner = -1, max = 0, posMax = 0, i = 0; /* default none cuz 2 players could have the same score */

    for (i = 0; i < numberOfPlayers; i++)
    {
        if (i == 0)
        {
            max = tetris[i]->score;
        }
        else
        {
            if (max < tetris[i]->score)
            {
                max = tetris[i]->score;
                posMax = i;
            }
        }
    }

    if (max != 0)
        winner = posMax;

    return winner;
}