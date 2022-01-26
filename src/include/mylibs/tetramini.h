/**
 * @file tetramini.h
 * @brief library to handle every kind of tetramino and for calculation of specific variables of the tetramino
 *
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief I code
 * 
 */
#define TETRAMINO_I 0
/**
 * @brief J code
 * 
 */
#define TETRAMINO_J 1
/**
 * @brief L code
 * 
 */
#define TETRAMINO_L 2
/**
 * @brief O code
 * 
 */
#define TETRAMINO_O 3
/**
 * @brief S code
 * 
 */
#define TETRAMINO_S 4
/**
 * @brief Z code
 * 
 */
#define TETRAMINO_Z 5
/**
 * @brief T code
 * 
 */
#define TETRAMINO_T 6

/** @struct Tetramino
 * @brief Structure that rappresents the tetramino model
 *
 * @param code the uniqe code for the type of the tetramino
 * @param matrix matrix rappresenation of the tetramino
 * @param width width of the tetramino
 * @param heigth heigh of tetramino
 * @param offsetX number of empty rows before the start of the tetramino in the matrix
 * @param offsetY number of empty cols before the start of the tetramino in the matrix
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
 * @brief I array that
 * rappresents the "I" piece
 */
int I[] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0};

/**
 * @brief J array that
 * rappresents the "J" piece
 */
int J[] = {
    1, 0, 0,
    1, 1, 1,
    0, 0, 0};

/**
 * @brief L array that
 * rappresents the "L" piece
 */
int L[] = {
    0, 0, 1,
    1, 1, 1,
    0, 0, 0};

/**
 * @brief O array that
 * rappresents the "O" piece
 */
int O[] = {
    1, 1, 0,
    1, 1, 0,
    0, 0, 0};

/**
 * @brief S array that
 * rappresents the "S" piece
 */
int S[] = {
    0, 1, 1,
    1, 1, 0,
    0, 0, 0};

/**
 * @brief Z array that
 * rappresents the "Z" piece
 */
int Z[] = {
    1, 1, 0,
    0, 1, 1,
    0, 0, 0};

/**
 * @brief T array that
 * rappresents the "T" piece
 */
int T[] = {
    0, 1, 0,
    1, 1, 1,
    0, 0, 0};

/**
 * @brief immutable array of tetramini models, that contains all types of the tetramino
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
 * @brief calculate the offset for the X ffset where tetramino starts his first block(full cell) in the x axis
 *
 * @param t tetramino
 * @return the offset calculated
 */
int offsetX(Tetramino *t)
{
    int i = 0, j = 0;
    for (i = 0; i < t->matrix.cols; i++)
    {
        for (j = 0; j < t->matrix.rows; j++)
        {
            if (t->matrix.map[i + j * t->matrix.cols] == 1)
                return i;
        }
    }
    return -1; /* if empty matrix */
}

/**
 * @brief calculate the offset for the Y, offset where tetramino starts his first "full cell" in the x axis
 *
 * @param t tetramino
 * @return the offset calculated
 */
int offsetY(Tetramino *t)
{
    int i = 0, j = 0;
    for (i = 0; i < t->matrix.rows; i++)
    {
        for (j = 0; j < t->matrix.cols; j++)
            if (t->matrix.map[j + i * t->matrix.rows] == 1)
                return i;
    }
    return -1; /* if empty matrix */
}

/**
 * @brief give the corrisponding letter based on the code of the tetramino in input
 *
 * @param type type of tetramino
 * @return the letter of corrisponding tetramino code type
 */
char typeToLetter(int type)
{
    if (type >= 0 && type < 8)
    {
        char *letters = "IJLOSZT";
        return letters[type];
    }
    return ' ';
}