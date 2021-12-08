#include "include/headers.h"

int main(void)
{
    char key;
    int tetraminoSwitchType = 0, x=0;
    WINDOW *win;

    // initialization
    win = initscr(); // new screen will be created
    nodelay(win, TRUE);
    noecho();

    //printw("Press ESC to exit.\n"); // instead of printf

    Tetris *tetris = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    printMatrix(&tetramini[tetraminoSwitchType % 6].matrix); // print first tetramino
    printw("\n\n");
    printMatrix(tetris->matrix);

    while(1 && key != ESC){
        key = toupper(getch());
        if(key > -1){ //default is -1 if u dont press anything
            if(key == ESC && getch() == '[') key=getch(); //prevent exit if user press ARROW KEYS becuase when it happen getch will push 3 values into the buffer (ESC + [ + ARROW_KEY)
            //printw("%c", toupper(key));

            switch (key)
            {
            case '\n':
                clear(); //clear screen
                tetraminoSwitchType++;
                x=0;
                printMatrixW(&tetramini[tetraminoSwitchType%6].matrix,x);
                printw("\n\n");
                printMatrix(tetris->matrix);
                break;
            case ' ':
                clear();
                insertTetramino(tetris->matrix, &tetramini[tetraminoSwitchType % 6], x, 0, GRAVITY);

                printMatrixW(&tetramini[tetraminoSwitchType % 6].matrix, x);
                printw("\n\n");
                printMatrix(tetris->matrix);
                break;

            case 'A': //LEFT
                clear();
                x = manageTetraminoXInput(&tetramini[tetraminoSwitchType % 6] , x, key);
                printMatrixW(&tetramini[tetraminoSwitchType % 6].matrix, x);
                printw("\n\n");
                printMatrixW(tetris->matrix, 0);
                break;

            case 'D': //RIGHT
                clear();
                x = manageTetraminoXInput(&tetramini[tetraminoSwitchType % 6],x, key);
                printMatrixW(&tetramini[tetraminoSwitchType % 6].matrix, x);
                printw("\n\n");
                printMatrixW(tetris->matrix, 0);
                break;

            default:
                break;
            }
        }
    }

/*     tetris->matrix = &tetramini[0].matrix;
    tetramini[0].matrix.map[5] = 9;
    printMatrix(&tetramini[0].matrix); */

/*     insertTetramino(tetris->matrix, &tetramini[TETRAMINO_I], 3);
    insertTetramino(tetris->matrix, &tetramini[TETRAMINO_Z], 3);

    insertTetramino(tetris->matrix, &tetramini[TETRAMINO_I], 6);

    printMatrix(tetris->matrix); */

    deleteTetris(tetris);

    endwin();
    return 0;
}