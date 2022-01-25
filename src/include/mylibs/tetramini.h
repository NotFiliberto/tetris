#include <stdio.h>
#include <stdlib.h>

#define TETRAMINO_I 0
#define TETRAMINO_J 1
#define TETRAMINO_L 2
#define TETRAMINO_O 3
#define TETRAMINO_S 4
#define TETRAMINO_Z 5
#define TETRAMINO_T 6

/** @struct Tetramino
 * @brief Structure that rappresents the tetramino model
 *
 * @var Tetramino::code the uniqe code for the type of the tetramino
 * @var Tetramino::matrix matrix rappresenation of the tetramino
 * @var Tetramino::width width of the tetramino
 * @var Tetramino::heigth heigh of tetramino
 * @var Tetramino::offsetX number of empty rows before the start of the tetramino in the matrix
 * @var Tetramino::offsetY number of empty cols before the start of the tetramino in the matrix
 */
typedef struct tetramino
{
    int code;
    Matrix matrix;
    int width;
    int heigth;
    int offsetX;
    int offsetY;
} Tetramino;

/**
 * @brief I
 * rappresent the "I" piece in the original tetris
 */
int I[] = {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0
    };

/**
 * @brief J
 * rappresent the "J" piece in the original tetris
 */
int J[] = {
    1, 0, 0,
    1, 1, 1,
    0, 0, 0
};

/**
 * @brief L
 * rappresent the "L" piece in the original tetris
 */
int L[] = {
    0, 0, 1,
    1, 1, 1,
    0, 0, 0
};

/**
 * @brief O
 * rappresent the "O" piece in the original tetris
 */
int O[] = {
    1, 1, 0,
    1, 1, 0,
    0, 0, 0
};

/**
 * @brief S
 * rappresent the "S" piece in the original tetris
 */
int S[] = {
    0, 1, 1,
    1, 1, 0,
    0, 0, 0
};

/**
 * @brief Z
 * rappresent the "Z" piece in the original tetris
 */
int Z[] = {
    1, 1, 0,
    0, 1, 1,
    0, 0, 0
};

/**
 * @brief T
 * rappresent the "T" piece in the original tetris
 */
int T[] = {
    0, 1, 0,
    1, 1, 1,
    0, 0, 0
};

/**
 * @brief immutable array of tetramini models
 * Array that contains all types of the tetramino
 */
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

/**
 * @brief calculate the offset for the X
 *
 * offset where tetramino starts his first block(full cell) in the x axis
 *
 * @param t tetramino
 * @return the offset calculated
 */
int offsetX(Tetramino* t){
    int i=0, j=0;
    for(i=0; i<t->matrix.cols;i++){
        for (j = 0; j < t->matrix.rows; j++){
            if(t->matrix.map[i + j*t->matrix.cols] == 1)
                return i;
        }
    }
    return -1; /* if empty matrix */
}

/**
 * @brief calculate the offset for the Y
 *
 * offset where tetramino starts his first "full cell" in the x axis
 *
 * @param t tetramino
 * @return the offset calculated
 */
int offsetY(Tetramino *t)
{
    int i=0, j=0;
    for (i = 0; i < t->matrix.rows; i++)
    {
        for (j = 0; j < t->matrix.cols; j++)
            if(t->matrix.map[j + i*t->matrix.rows] == 1)
                return i; 
    }
    return -1; /* if empty matrix */
}

/**
 * @brief give the corrisponding letter based of the code of the tetramino in input
 * 
 * @param type type of tetramino
 * @return the letter of corrisponding tetramino code type
 */
char typeToLetter(int type){
    if(type >=0 && type < 8){
        char* letters = "IJLOSZT";
        return letters[type];
    }
    return ' ';
}