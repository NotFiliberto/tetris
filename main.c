#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h> // to implement cross platform non blocking terminal keyboard input
#include "variables.h"
#include "utils.h"
#include "matrix.h"
#include "tetramini.h"
#include "tetris.h"

int main(void)
{
    char key;
    int tetraminoSwitchType = 0;
    WINDOW *win;

    // initialization
    win = initscr(); // new screen will be created
    nodelay(win, TRUE);
    noecho();

    printw("Press ESC to exit.\n"); // instead of printf

    Tetris *tetris = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    printMatrix(&tetramini[tetraminoSwitchType % 6].matrix); //print first tetramino

    while(1 && key != ESC){
        key = getch();
        if(key > -1){ //default is -1 if u dont press anything
            if(key == ESC && getch() == '[') key=getch(); //prevent exit if user press ARROW KEYS becuase when it happen getch will push 3 values into the buffer (ESC + [ + ARROW_KEY)
            //printw("%c", toupper(key));


            switch (toupper(key))
            {
            case '\n':
                clear(); //clear screen
                tetraminoSwitchType++;
                printMatrix(&tetramini[tetraminoSwitchType%6].matrix);
                printw("\n\n");
                printMatrix(tetris->matrix);
                break;
            case ' ':
                clear();
                if (insertTetramino(tetris->matrix, &tetramini[tetraminoSwitchType % 6], 3, 0, 0)){ // no gravity
                    printw("\ninsert\n\n");
                } else
                    printw("\nnot inserted\n\n");

                printMatrix(&tetramini[tetraminoSwitchType % 6].matrix);
                printw("\n\n");
                printMatrix(tetris->matrix);
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