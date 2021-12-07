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
} Tetramino;

int I[] = {
        1, 0, 0, 0,
        1, 0, 0, 0,
        1, 0, 0, 0,
        1, 0, 0, 0
/*     0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 1 */
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
        {TETRAMINO_I, {4, 4, I}, 1, 4},
        {TETRAMINO_J, {3, 3, J}, 3, 2},
        {TETRAMINO_L, {3, 3, L}, 3, 2},
        {TETRAMINO_O, {3, 3, O}, 2, 2},
        {TETRAMINO_S, {3, 3, S}, 3, 2},
        {TETRAMINO_Z, {3, 3, Z}, 3, 2},
        {TETRAMINO_T, {3, 3, T}, 3, 2},
};

//non funziona bene DA SISTEMARE
/* void tetraminoSize(Tetramino* t, int* w, int* h){
    
    int longest=0,length=1;
    for (int i = 1; i < (t->matrix.rows * t->matrix.cols); i++){
        if (t->matrix.map[i] == t->matrix.map[i - 1] && t->matrix.map[i] == 1)
            length++;
        else{
            if(length>longest)
                longest=length;
            length=1;//reset
        }
    }
    if (length > longest)
        longest = length;
    *w = longest;


    longest = 0; length = 1;
    for (int i = 0; i < t->matrix.cols; i++)
    {
        int count=0;
        for(int j=0; j<t->matrix.rows; j++){
            if (t->matrix.map[i + j * t->matrix.rows] == 1)
                count++;
        }

        if(count>longest)
            longest=count;
    }
    *h=longest;
} */

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
        {
            if(t->matrix.map[j + i*t->matrix.rows] == 1)
                return i;
        }
    }

    return -1; // if empty matrix
}