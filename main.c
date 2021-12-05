#include <stdio.h>
#include <stdlib.h>
#include "variables.h"
#include "utils.h"
#include "matrix.h"
#include "tetramini.h"
#include "tetris.h"

int main(void)
{
    Tetris *tetris = createTetris(DEFAULT_ROWS, DEFAULT_COLS);

    printMatrix(tetris->matrix);
    return 0;
}