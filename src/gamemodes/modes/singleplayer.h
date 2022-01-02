void printGameThings(Tetris *tetris, WINDOW *win);
void switchTetraminoTask(Tetris *tetris, WINDOW *win, int incrementType);
void insertTetraminoTask(Tetris *tetris, WINDOW *win);
void moveTetraminoTask(Tetris *tetris, WINDOW *win, char key);
void rotateTetraminoTask(Tetris *tetris, WINDOW *win);

void testing(Tetris *tetris, WINDOW *win);

int singlePlayer(void)
{
    char key;
    WINDOW *win = initScreen(); // screen, ecc...

    Tetris *tetris = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    printGameThings(tetris, win);

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
            case SWITCH:
                switchTetraminoTask(tetris, win, 1);
                break;
            case SELECT:
                insertTetraminoTask(tetris, win);
                break;

            case MOVE_LEFT: // left
                moveTetraminoTask(tetris, win, key);
                break;

            case MOVE_RIGHT: // right
                moveTetraminoTask(tetris, win, key);
                break;
            case MOVE_UP:
                rotateTetraminoTask(tetris, win);
                break;
            case '-': // for testing stuffs
                testing(tetris, win);
                break;

            default:
                break;
            }
        }
        refresh();
    }

    deleteTetris(tetris);
    endScreen();
    return 0;
}

void printGameThings(Tetris *tetris, WINDOW *win)
{
    clear();
    printwc(win, COLOR_WHITE, COLOR_MAGENTA, "Score: %d\n\n", tetris->score);

    if (totalAvailability(tetris) > 0)
        printTetraminiAvailability(tetris); // check avaibility
    else
    {
        printwc(win, COLOR_WHITE, COLOR_RED, "\nno avaible pieces");
    }

    // check game status
    if (tetris->gameStatus == 1)
    {
        printwc(win, COLOR_WHITE, COLOR_RED, "\nGAME ENDED");
    }

    printw("\n\n");
    printMatrixW(&tetris->tetramino->matrix, tetris->lastX, tetris->tetramino->offsetX, tetris->tetramino->offsetY, SHOW_WALLS, 1);
    printMatrixW(tetris->matrix, 0, 0, 0, SHOW_WALLS, 0);
    printw("\n\n");
}

void switchTetraminoTask(Tetris *tetris, WINDOW *win, int incrementType)
{
    if (!tetris->gameStatus)
    {
        if (totalAvailability(tetris) > 0 && !tetris->gameStatus)
        {
            int currentTetraminoType = tetris->tetramino->code;

            if (incrementType)                                             // only in main game loop
                tetris->tetraminoType = (tetris->tetramino->code + 1) % 7; // next tetramino
            tetris->tetraminoType = nextTetraminoAvailable(tetris);        // if avaible return the incremente tetramino in the line before otherwhise it finds automatically the ones avalaible

            if (currentTetraminoType != (tetris->tetraminoType))
            {                                                                           // to save current rotation
                deleteTetramino(tetris->tetramino);                                     // delete old tetramino and all his stuffs
                tetris->tetramino = createTetramino(&tetramini[tetris->tetraminoType]); // create new tetramino
            }

            tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, SWITCH); // check x pos for the visualization
        }
        if (incrementType) // print things only if this task is called in the main loop
            printGameThings(tetris, win);
    }
}

void insertTetraminoTask(Tetris *tetris, WINDOW *win)
{
    if (!tetris->gameStatus)
    {
        int points = 0;
        if (tetraminoAvailability(tetris, tetris->tetramino->code) > 0)
        {
            if (insertTetramino(tetris->matrix, tetris->tetramino, tetris->lastX, 0, GRAVITY, 1))
            {
                decrementTetraminoAvailability(tetris, tetris->tetramino->code);

                points = scorePoints(tetris);

                if (points)
                {
                    tetris->score += points;
                }
                tetris->gameStatus = gameEnded(tetris);

                if (!tetris->gameStatus)                 // swap piece automaticly if needed
                    switchTetraminoTask(tetris, win, 0); // check next piece avaible
            }
        }
        printGameThings(tetris, win);
    }
}

void moveTetraminoTask(Tetris *tetris, WINDOW *win, char key)
{
    if (!tetris->gameStatus)
    {
        tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, key);
        printGameThings(tetris, win);
    }
}

void rotateTetraminoTask(Tetris *tetris, WINDOW *win)
{
    if (!tetris->gameStatus)
    {

        tetris->tetramino = rotateTetramino(tetris->tetramino);
        tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, SWITCH); // fix the position

        printGameThings(tetris, win);
    }
}

void testing(Tetris *tetris, WINDOW *win)
{
    printGameThings(tetris, win);
    printw("--> testing");
}