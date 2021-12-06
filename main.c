#include <stdio.h>
#include <stdlib.h>
#include "variables.h"
#include "utils.h"
#include "matrix.h"
#include "tetramini.h"
#include "tetris.h"

int main(void)
{
    Tetris *tetris = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);

/*     tetris->matrix = &tetramini[0].matrix;
    tetramini[0].matrix.map[5] = 9;
    printMatrix(&tetramini[0].matrix); */

    insertTetramino(tetris->matrix, &tetramini[TETRAMINO_T], 4);

    printMatrix(tetris->matrix);

    return 0;
}