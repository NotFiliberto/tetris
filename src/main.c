#include "include/headers.h"

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
    }

    deleteTetris(tetris);

    endwin();
    return 0;
}

void init()
{
}

void printGameThings(Tetris *tetris){
    printMatrixW(&tetris->tetramino->matrix, tetris->lastX, tetris->tetramino->offsetX, tetris->tetramino->offsetY);
    printw("\n\n");
    printMatrix(tetris->matrix);

    printw("\n\n");
    
    if(totalAvailability(tetris) > 0)
        printTetraminiAvailability(tetris); // check avaibility
    else
        printw("no avaible pieces");

    // check game status
    if (gameEnded(tetris))
    {
        printw("\n\ngame ended");
    }
}

void switchTetraminoTask(Tetris *tetris, int incrementType)
{
    clear(); // clear screen
    
    if(totalAvailability(tetris) > 0){
        int previusTetraminoType = tetris->tetramino->code;

        if(incrementType) //only in main game loop
            tetris->tetraminoType = tetris->tetramino->code + 1; // next tetramino
        tetris->tetraminoType = nextTetraminoAvailable(tetris); // if avaible return the incremente tetramino in the line before otherwhise it finds automatically the ones avalaible

        if(previusTetraminoType != (tetris->tetraminoType %7)){ // to save current rotation
            deleteTetramino(tetris->tetramino);                                         // delete old tetramino and all his stuffs
            tetris->tetramino = createTetramino(&tetramini[tetris->tetraminoType % 7]); // create new tetramino
        }

        tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, '\n'); // check x pos for the visualization

    }
    if (incrementType) // print things only if this task is called in the main loop
        printGameThings(tetris);
}

void insertTetraminoTask(Tetris *tetris)
{
    clear();
    int points = 0;

    if(tetraminoAvailability(tetris, tetris->tetramino->code) > 0) {
        if (insertTetramino(tetris->matrix, tetris->tetramino, tetris->lastX, 0, GRAVITY, 1)){
            decrementTetraminoAvailability(tetris, tetris->tetramino->code);

            points = scorePoints(tetris);

            if (points)
                printw("\npoints: %d\n", points);
            //TODO: update score on tetris field

            // swap piece automaticly
            switchTetraminoTask(tetris, 0); // check next piece avaible
        } 
    }
    printGameThings(tetris);
}

void moveTetraminoTask(Tetris *tetris, char key)
{
    clear();
    tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, key);
    printGameThings(tetris);
}

void rotateTetraminoTask(Tetris *tetris)
{
    clear();

    tetris->tetramino = rotateTetramino(tetris->tetramino);
    tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, '\n'); // fix the position

    printGameThings(tetris);
}

void testing(Tetris *tetris)
{
    clear(); // clear screen

    scorePoints(tetris);

    printGameThings(tetris);
}