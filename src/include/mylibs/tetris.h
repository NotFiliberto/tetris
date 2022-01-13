#include <stdlib.h>
#include <string.h>

typedef struct tetris
{
    Matrix *matrix;       // matrix map
    Tetramino *tetramino; // current tetramino selected, with all of his options
    int tetraminoType;    // type of current tetramino
    int lastX;            // last X position for the last tetramino
    int score;
    int *availableTetramini;
    int gameStatus; // 0 not finished
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

    int i=0;
    for (i = 0; i < t->matrix.cols * t->matrix.rows; i++)
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
    tetris->score = 0;
    tetris->gameStatus = 0; // not finished

    tetris->tetramino = createTetramino(&tetramini[TETRAMINO_I]); // copy tetramino I from the array

    tetris->matrix = createMatrix(cols, rows); // the fuction returns the pointer of the created matrix
    clearMatrix(tetris->matrix);               // set up the effective map to all 0

    // avaible tetramini

    tetris->availableTetramini = (int *)malloc(sizeof(int) * 7);
    
    int i=0;
    for (i = 0; i < 7; i++)
    {
        tetris->availableTetramini[i] = DEFAULT_AVAILABILITY;
    }

    // FOR TESTING THINGS
    //     tetris->matrix = createMatrix(7, 10);
    //   free(tetris->matrix->map);
    //  tetris->matrix->map = testingMap; 
    // FOR TESTING THINGS

    return tetris;
}

void deleteTetris(Tetris *tetris)
{
    deleteMatrix(tetris->matrix);
    free(tetris);
}

// check if 2 matrix are intersected each other
int isIntersected(Matrix *tetrisMatrix, Tetramino *t, int x, int y)
{
    int startXTetramino = offsetX(t);
    int startYTetramino = offsetY(t);

    int i=0, j=0;
    for ( i = 0; i < t->heigth; i++)
    {
        for ( j = 0; j < t->width; j++)
        {
            if (t->matrix.map[(i + startYTetramino) * t->matrix.cols + (j + startXTetramino)] == 1 && tetrisMatrix->map[(y + i) * tetrisMatrix->cols + (x + j)] == 1)
                return 1;
        }
    }

    return 0;
}

// check if the y of the matrix in a specif x is empty or not for the width of the piece
int ySlotStatus(Matrix *tetrisMatrix, Tetramino *t, int x, int y)
{

    int counter = 0, j=0;
    for ( j = 0; j < t->width; j++)
    {
        if (tetrisMatrix->map[tetrisMatrix->cols * y + x + j] == 1)
            counter++;
    }

    return counter;
}

int findY(Matrix *tetrisMatrix, Tetramino *t, int x)
{
    int y, count = 0, flag = -1, k=0, z=0;

    for (y = 0; y < tetrisMatrix->rows - t->heigth + 1; y++)
    {
        // check the last row of tetramino with every row of tetris matrix for a "gravity check"
        for ( k = 0; k < t->heigth; k++)
        {
            for ( z = 0; z < t->width; z++)
            {
                if (t->matrix.map[(t->heigth - 1 + offsetY(t)) * t->matrix.cols + (z + offsetX(t))] == 1 && tetrisMatrix->map[(y + k) * tetrisMatrix->cols + (x + z)] == 1)
                    return y - 1;
            }
        }

        if (ySlotStatus(tetrisMatrix, t, x, y)) // if the row in the matrix is not empty u cant insert the new Tetramino
            return y - 1;

        if (isIntersected(tetrisMatrix, t, x, y))
            return y - 1;

        count++; // else increase counter
    }
    return count - 1;
}

int insertTetramino(Matrix *tetrisMatrix, Tetramino *t, int x, int y, int gravity, int insertFLAG)
{
    if (x > DEFAULT_WIDTH || x < 0 || y < 0)
        return 0; // impossible to insert

    int offX = offsetX(t), offY = offsetY(t);

    // printw("size    W:%d\n\tH: %d\noffset  X: %d\n\tY: %d\n", t->width, t->heigth, offX, offY);

    if (x + t->width <= DEFAULT_WIDTH)
    {
        if (gravity)
        {                                  // if set the tetramine will go to the bottom of the main matrix
            y = findY(tetrisMatrix, t, x); // y will be overwritten
        }
        else
        {
            if (isIntersected(tetrisMatrix, t, x, y))
                return 0;
        }
        // its possible
        if (y < 0)
            return 0;

        int row,col;
        for ( row = offY; row < t->matrix.rows; row++)
        {
            for ( col = offX; col < t->matrix.cols; col++)
            {
                if (t->matrix.map[(col) + row * t->matrix.cols] == 1)
                {
                    if (insertFLAG == 1)
                    {                                                                                    // if flag is true
                        tetrisMatrix->map[(col + x - offX) + (row + y - offY) * tetrisMatrix->cols] = 1; // insert
                    }
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

    int row,col,j;
    for ( row = 0; row < matrix->rows; row++)
        for ( col = 0; col < matrix->cols; col++)
            trasposedMatrix->map[row * trasposedMatrix->cols + col] = matrix->map[col * matrix->rows + row];

    Matrix *rotatedMatrix90Clockwise = createMatrix(trasposedMatrix->rows, trasposedMatrix->cols); // invert for the same reason of before
    // reverse the order of cols
    for ( row = 0; row < matrix->rows; row++)
        for ( col = trasposedMatrix->cols - 1, j = 0; col > -1; col--, j++)
            rotatedMatrix90Clockwise->map[row * rotatedMatrix90Clockwise->cols + j] = trasposedMatrix->map[row * rotatedMatrix90Clockwise->cols + col];

    return rotatedMatrix90Clockwise;
}

Tetramino *rotateTetramino(Tetramino *t)
{
    Matrix *rotated = rotateMatrix90Clockwise(&t->matrix);

    // deleteTetramino(t);
    Tetramino *tr = (Tetramino *)malloc(sizeof(Tetramino));

    tr->code = t->code;
    tr->matrix = *rotated;
    tr->offsetX = offsetX(tr);
    tr->offsetY = offsetY(tr);
    tr->width = t->heigth;
    tr->heigth = t->width;

    return tr;
}

// =====================================
// ======= TETRAMINO AVAIBILITY ========
// =====================================

int tetraminoAvailability(Tetris *tetris, int tetraminoCode)
{
    return tetris->availableTetramini[tetraminoCode];
}

int decrementTetraminoAvailability(Tetris *tetris, int tetraminoCode)
{
    if (tetris->availableTetramini[tetraminoCode] > 0)
        return --tetris->availableTetramini[tetraminoCode]; // decrement
    return -1;
}

void printTetraminiAvailability(Tetris *tetris, int typesPerRow)
{
    init_pair(1, COLOR_WHITE, COLOR_CYAN);
    // printw("[Current Type %c] > %d\n\n", typeToLetter(tetris->tetramino->code), tetris->availableTetramini[tetris->tetramino->code]);
    int i;
    for ( i = 0; i < 7; i++)
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

int totalAvailability(Tetris *tetris)
{
    int tot = 0, i = 0;
    for ( i = 0; i < 7; i++)
    {
        tot += tetris->availableTetramini[i];
    }
    return tot;
}

// usefull when u swap piece or u just insert new one
int nextTetraminoAvailable(Tetris *tetris)
{

    if (totalAvailability > 0)
    {
        int i=0;
        for ( i = 0; i < 7; i++)
        {
            if (tetraminoAvailability(tetris, (tetris->tetraminoType + i) % 7) > 0)
                return (tetris->tetraminoType + i) % 7;
        }
    }
    return -1; // and the game is ended
}

// =====================================
// ======= TETRAMINO AVAIBILITY ========
// =====================================

int gameEnded(Tetris *tetris)
{
    if (totalAvailability(tetris) == 0)
        return 1; // game ended

    // first thing to do, find the first position of empty x
    int pos = -1, i=0;
    for ( i = 0; i < tetris->matrix->cols && pos == -1; i++)
    {
        if (tetris->matrix->map[i] == 0)
            pos = i;
    }
    // continue with the check
    if (pos != -1)
    {
        Tetramino *tetramino;
        int rotation, col, pieceType;
        for (pieceType = 0; pieceType < 7; pieceType++)
        { // for every piece
            if (tetraminoAvailability(tetris, pieceType) > 0)
            { // first check if the piece is avaible
                tetramino = createTetramino(&tetramini[pieceType]);
                for ( rotation = 0; rotation < 4; rotation++)
                { // test every rotation
                    for ( col = 0; col < tetris->matrix->cols; col++)
                    {
                        if (insertTetramino(tetris->matrix, tetramino, col, 0, GRAVITY, 0))
                        { // important to enable gravity

                            // printw("\n\ntype: %d, rotation: %d, x: %d\n\n", pieceType, rotation, col);
                            return 0;
                        }
                    }
                    tetramino = rotateTetramino(tetramino);
                }
                deleteTetramino(tetramino); // free memory
            }
            else
            {
                // otherwhise do nothing, dont check for this type of tetramino
            }
        }
    }
    return 1;
}

void removeRow(Tetris *tetris, int row)
{
    int startIndex = (row * tetris->matrix->cols + tetris->matrix->cols) - 1, i;
    for ( i = startIndex; i > -1; i--)
    {
        if (i >= tetris->matrix->cols)
            tetris->matrix->map[i] = tetris->matrix->map[i - tetris->matrix->cols]; // shift
        else
            tetris->matrix->map[i] = 0; // fill the first row with empty space
    }
}

int *findRowsToRemove(Tetris *tetris, int *size)
{

    (*size) = 0; // default
    int i, j, fullRow = 1;
    int *rowsToDelete = (int *)malloc(tetris->matrix->rows * sizeof(int));

    for (i = 0; i < tetris->matrix->rows; i++)
    {

        for (j = 0; j < tetris->matrix->cols && fullRow; j++)
        {
            if (tetris->matrix->map[i * tetris->matrix->cols + j] == 0)
                fullRow = 0; // not fullRow, so i cant delete it
        }

        if (fullRow)
        {                                // row to delete
            rowsToDelete[(*size)++] = i; // increse size and save row index
            // printw("row do delete added: %d, size [%d]\n", rowsToDelete[(*size)-1], (*size));
        }
        fullRow = 1;
    }

    if ((*size) == 0)
        rowsToDelete[(*size)++] = -1; // init, that means 0 rows found to remove

    return rowsToDelete;
}

int scorePoints(Tetris *tetris)
{
    int size, *rowsToDelete = findRowsToRemove(tetris, &size), points = 0;
    int pointsBoard[] = {0, 1, 3, 6, 12, 20, 30};

    if (rowsToDelete[0] != -1)
    {

        // points to assing based on calculated size
        points = pointsBoard[size];
        int i;

        for ( i = 0; i < size; i++)
        {
            removeRow(tetris, rowsToDelete[i]);
        }

        // rowsToDelete = findRowsToRemove(tetris, &size);
    }

    // printw("\npoints: %d\n", points);

    return points;
}

void invertRow(int* row, int width){
    int i;
    for( i=0; i<width; i++){
        if(row[i] == 0)
            row[i] = 1;
        else
            row[i] = 0;
    }
}

void invertTetrisRows(Tetris* tetris, int nrowsToInvert){
    int i=0;
    for( i = 0;  i < nrowsToInvert; i++){
        invertRow(&tetris->matrix->map[tetris->matrix->cols*(tetris->matrix->rows-i-1)], tetris->matrix->cols);
    }
}

int getWinner(Tetris** tetris, int numberOfPlayers){
    int winner = -1, max=0, posMax=0, i=0; //default none cuz 2 players could have the same score

    for( i=0; i<numberOfPlayers; i++){
        if(i==0){
            max = tetris[i]->score;
        }else{
            if(max < tetris[i]->score){
                max = tetris[i]->score;
                posMax = i;
            }
        }
    }

    if(max != 0)
        winner = posMax;
    
    return winner;
}