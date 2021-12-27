#include <stdio.h>
#include <stdlib.h>

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
    Matrix matrix;
    int width;
    int heigth;
    int offsetX;
    int offsetY;
} Tetramino;

int I[] = {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0
    };

int J[] = {
    1, 0, 0,
    1, 1, 1,
    0, 0, 0
};

int L[] = {
    0, 0, 1,
    1, 1, 1,
    0, 0, 0
};

int O[] = {
    1, 1, 0,
    1, 1, 0,
    0, 0, 0
};

int S[] = {
    0, 1, 1,
    1, 1, 0,
    0, 0, 0
};

int Z[] = {
    1, 1, 0,
    0, 1, 1,
    0, 0, 0
};

int T[] = {
    0, 1, 0,
    1, 1, 1,
    0, 0, 0
};

Tetramino 
    tetramini[] = {
        {TETRAMINO_I, {4, 4, I}, 1, 4, 0, 0},
        {TETRAMINO_J, {3, 3, J}, 3, 2, 0, 0},
        {TETRAMINO_L, {3, 3, L}, 3, 2, 0, 0},
        {TETRAMINO_O, {3, 3, O}, 2, 2, 0, 0},
        {TETRAMINO_S, {3, 3, S}, 3, 2, 0, 0},
        {TETRAMINO_Z, {3, 3, Z}, 3, 2, 0, 0},
        {TETRAMINO_T, {3, 3, T}, 3, 2, 0, 0},
};

/* \brief offset where tetramino start his first block, we have to check vertically every col
 */
int offsetX(Tetramino* t){
    for(int i=0; i<t->matrix.cols;i++){
        for (int j = 0; j < t->matrix.rows; j++){
            if(t->matrix.map[i + j*t->matrix.cols] == 1)
                return i;
        }
    }
    return -1; //if empty matrix
}

int offsetY(Tetramino *t)
{
    for (int i = 0; i < t->matrix.rows; i++)
    {
        for (int j = 0; j < t->matrix.cols; j++)
            if(t->matrix.map[j + i*t->matrix.rows] == 1)
                return i; 
    }
    return -1; // if empty matrix
}

char typeToLetter(int type){
    if(type >=0 && type < 8){
        char* letters = "IJLOSZT";
        return letters[type];
    }
    return ' ';
}