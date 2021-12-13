#include "include/headers.h"

void switchTetraminoTask(Tetris *tetris);
void insertTetraminoTask(Tetris *tetris);
void moveTetraminoTask(Tetris *tetris, char key);
void rotateTetraminoTask(Tetris *tetris);

void testing(Tetris *tetris);

int main(void)
{
    char key;
    WINDOW *win;

    // initialization
    win = initscr(); // new screen will be created
    nodelay(win, TRUE);
    noecho();

    // printw("Press ESC to exit.\n"); // instead of printf

    Tetris *tetris = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    printMatrixW(&tetris->tetramino->matrix, tetris->lastX, tetris->tetramino->offsetX, tetris->tetramino->offsetY);
    printw("\n\n");
    printMatrix(tetris->matrix);

    while (1 && key != ESC)
    {
        key = toupper(getch());
        if (key > -1)
        { // default is -1 if u dont press anything
            if (key == ESC && getch() == '[')
                key = getch(); // prevent exit if user press ARROW KEYS becuase when it happen getch will push 3 values into the buffer (ESC + [ + ARROW_KEY)
            // printw("%c", toupper(key));

            switch (key)
            {
            case '\n':
                switchTetraminoTask(tetris);
                break;
            case ' ':
                insertTetraminoTask(tetris);
                break;

            case 'A': // left
                moveTetraminoTask(tetris, key);
                break;

            case 'D': // right
                moveTetraminoTask(tetris, key);
                break;
            case 'W':
                rotateTetraminoTask(tetris);
                break;
            case '-': // for testing stuffs
                testing(tetris);
                break;

            default:
                break;
            }
        }
    }

    deleteTetris(tetris);

    endwin();
    return 0;
}

void init()
{
}

void switchTetraminoTask(Tetris *tetris)
{
    clear(); // clear screen

    tetris->tetraminoType = tetris->tetramino->code + 1; // next tetramino

    deleteTetramino(tetris->tetramino);                                         // delete old tetramino and all his stuffs
    tetris->tetramino = createTetramino(&tetramini[tetris->tetraminoType % 7]); // create new tetramino

    tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, '\n'); // check x pos for the visualization

    printMatrixW(&tetris->tetramino->matrix, tetris->lastX, tetris->tetramino->offsetX, tetris->tetramino->offsetY);
    printw("\n\n");
    printMatrix(tetris->matrix);
}

void insertTetraminoTask(Tetris *tetris)
{
    clear();
    insertTetramino(tetris->matrix, tetris->tetramino, tetris->lastX, 0, GRAVITY);
    printMatrixW(&tetris->tetramino->matrix, tetris->lastX, tetris->tetramino->offsetX, tetris->tetramino->offsetY);
    printw("\n\n");
    printMatrix(tetris->matrix);
}

void moveTetraminoTask(Tetris *tetris, char key)
{
    clear();
    tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, key);
    printMatrixW(&tetris->tetramino->matrix, tetris->lastX, tetris->tetramino->offsetX, tetris->tetramino->offsetY);
    printw("\n\n");
    printMatrix(tetris->matrix);
}

void rotateTetraminoTask(Tetris *tetris)
{
    clear();

    tetris->tetramino = rotateTetramino(tetris->tetramino);
    tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, '\n'); // fix the position

    printMatrixW(&tetris->tetramino->matrix, tetris->lastX, tetris->tetramino->offsetX, tetris->tetramino->offsetY);
    printw("\n\n");
    printMatrix(tetris->matrix);
}

void testing(Tetris *tetris)
{
    clear(); // clear screen

   
}