#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define TETRAMINO_I 0
#define TETRAMINO_J 1
#define TETRAMINO_L 2
#define TETRAMINO_O 3
#define TETRAMINO_S 4
#define TETRAMINO_Z 5
#define TETRAMINO_T 6

typedef struct tetramino
{
    int code;
    int *map;
} Tetramino;

Tetramino Tetramini[] = {
    {
        TETRAMINO_I,
        {
            1, 0, 0, 0,
            1, 0, 0, 0,
            1, 0, 0, 0,
            1, 0, 0, 0
        }
    },
    {
        TETRAMINO_J,
        {
            1, 0, 0,
            1, 1, 1,
            0, 0, 0
        }
    },
    {
        TETRAMINO_L,
        {
            0, 0, 1,
            1, 1, 1,
            0, 0, 0
        }
    },
    {
        TETRAMINO_O,
        {
            1, 1, 0,
            1, 1, 0,
            0, 0, 0
        }
    },
    {
        TETRAMINO_S,
        {
            0, 1, 1,
            1, 1, 0,
            0, 0, 0
        }
    },
    {
        TETRAMINO_Z,
        {
            1, 1, 0,
            0, 1, 1,
            0, 0, 0
        }
    },
    {   TETRAMINO_T,
        {
            0, 1, 0,
            1, 1, 1,
            0, 0, 0
        }
    }
};