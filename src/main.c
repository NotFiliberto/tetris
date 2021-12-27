#include "include/headers.h"

void printGameThings(Tetris *tetris);
void switchTetraminoTask(Tetris *tetris, int incrementType);
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

    start_color();

    Tetris *tetris = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    printGameThings(tetris);

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
                switchTetraminoTask(tetris, 1);
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
        refresh();
    }

    deleteTetris(tetris);

    endwin();
    return 0;
}

void init()
{
}

void printGameThings(Tetris *tetris){
    printMatrixW(&tetris->tetramino->matrix, tetris->lastX, tetris->tetramino->offsetX, tetris->tetramino->offsetY, WALLS, 1);
    printw("\n\n");
    printMatrixW(tetris->matrix, 0, 0, 0, WALLS, 0);

    printw("\n\n");

    //colors =======
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA); // score
    init_pair(3, COLOR_WHITE, COLOR_RED);  // END GAME
    
    // colors =======

    attron(COLOR_PAIR(2));
    printw("Score: %d\n\n", tetris->score);
    attroff(COLOR_PAIR(2));

    if(totalAvailability(tetris) > 0)
        printTetraminiAvailability(tetris); // check avaibility
    else{
        attron(COLOR_PAIR(3));
        printw("no avaible pieces");
        attroff(COLOR_PAIR(3));
    }

    // check game status
    if (tetris->gameStatus == 1)
    {
        attron(COLOR_PAIR(3));
        printw("\n\ngame ended");
        attroff(COLOR_PAIR(3));
    }
}

void switchTetraminoTask(Tetris *tetris, int incrementType)
{
    clear(); // clear screen
    if(totalAvailability(tetris) > 0 && !tetris->gameStatus){
        int currentTetraminoType = tetris->tetramino->code;

        if(incrementType) //only in main game loop
            tetris->tetraminoType = (tetris->tetramino->code + 1) % 7; // next tetramino
        tetris->tetraminoType = nextTetraminoAvailable(tetris); // if avaible return the incremente tetramino in the line before otherwhise it finds automatically the ones avalaible

        if(currentTetraminoType != (tetris->tetraminoType)){ // to save current rotation
            deleteTetramino(tetris->tetramino);                                         // delete old tetramino and all his stuffs
            tetris->tetramino = createTetramino(&tetramini[tetris->tetraminoType]); // create new tetramino
        }

        tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, '\n'); // check x pos for the visualization

    }
    if (incrementType) // print things only if this task is called in the main loop
        printGameThings(tetris);
}

void insertTetraminoTask(Tetris *tetris)
{
    if(!tetris->gameStatus){
        clear();
        int points = 0;
        if(tetraminoAvailability(tetris, tetris->tetramino->code) > 0) {
            if (insertTetramino(tetris->matrix, tetris->tetramino, tetris->lastX, 0, GRAVITY, 1)){
                decrementTetraminoAvailability(tetris, tetris->tetramino->code);

                points = scorePoints(tetris);

                if (points){
                    tetris->score += points;
                }
                tetris->gameStatus = gameEnded(tetris);

                if(!tetris->gameStatus) // swap piece automaticly if needed
                    switchTetraminoTask(tetris, 0); // check next piece avaible
            } 
        }
        printGameThings(tetris);
    }
}

void moveTetraminoTask(Tetris *tetris, char key)
{
    if(!tetris->gameStatus){
        clear();
        tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, key);
        printGameThings(tetris);
    }
}

void rotateTetraminoTask(Tetris *tetris)
{
    if(!tetris->gameStatus){

        clear();

        tetris->tetramino = rotateTetramino(tetris->tetramino);
        tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, '\n'); // fix the position

        printGameThings(tetris);
    }
}

void testing(Tetris *tetris)
{
    clear(); // clear screen

    scorePoints(tetris);

    printGameThings(tetris);
}