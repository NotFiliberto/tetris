Tetris **initGame(int numberOfPlayers);
void printGameThingsMultiplayer(Tetris **tetris, int numberOfPlayers, int playerTurn, WINDOW *win);

void switchTetraminoTaskM(Tetris** tetris, WINDOW *win, int incrementType);
void insertTetraminoTaskM(Tetris** tetris, WINDOW *win);
void moveTetraminoTaskM(Tetris** tetris, WINDOW *win, char key);
void rotateTetraminoTaskM(Tetris** tetris, WINDOW *win);

int multiplayer(WINDOW *win)
{
    char key;
    int numberOfPlayers = 1;
    int playerTurn = 0;

    Tetris **tetris = initGame(numberOfPlayers); // array of tetris games
    printGameThingsMultiplayer(tetris, numberOfPlayers, playerTurn, win);

    while (1 && key != ESC)
    {
        key = toupper(getch());
        if (key > -1)
        { // default is -1 if u dont press anything
            if (key == ESC && getch() == '[')
                key = getch(); // prevent exit if user press ARROW KEYS becuase when it happen getch will push 3 values into the buffer (ESC + [ + ARROW_KEY)
            // printw("%c", toupper(key));

            /*             switch (key)
                        {
                        case SWITCH:
                            switchTetraminoTaskM(tetris, win, 1);
                            break;
                        case SELECT:
                            insertTetraminoTaskM(tetris, win);
                            break;

                        case MOVE_LEFT: // left
                            moveTetraminoTaskM(tetris, win, key);
                            break;

                        case MOVE_RIGHT: // right
                            moveTetraminoTaskM(tetris, win, key);
                            break;
                        case MOVE_UP:
                            rotateTetraminoTaskM(tetris, win);
                            break;
                        case '-': // for testing stuffs
                            testing(tetris, win);
                            break;

                        default:
                            break;
                        } */
        }
        refresh();
    }

    for (int i = 0; i < numberOfPlayers; i++)
    {
        deleteTetris(tetris[i]);
    }

    return 0;
}

Tetris **initGame(int numberOfPlayers)
{
    Tetris **tetris;
    tetris = (Tetris **)malloc(sizeof(Tetris *) * numberOfPlayers);

    int i = 0;

    int *availableTetramini = (int *)malloc(sizeof(int) * 7);
    for (i = 0; i < 7; i++)
    {
        availableTetramini[i] = DEFAULT_AVAILABILITY * numberOfPlayers;
    }

    for (i = 0; i < numberOfPlayers; i++)
    {
        tetris[i] = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        tetris[i]->availableTetramini = availableTetramini;
    }

    return tetris;
}

void printGameThingsMultiplayer(Tetris **tetris, int numberOfPlayers, int playerTurn, WINDOW *win)
{
    clear();
    printGameStats(tetris, numberOfPlayers, playerTurn, win);

    printw("\n\n---> Player Turn: ");
    printwc(win, playerColors[playerTurn].textColor, playerColors[playerTurn].backgroudColor, 0, "%d\n\n", playerTurn);

    printTetris(tetris, numberOfPlayers, playerTurn, win);
}

void switchTetraminoTaskM(Tetris **tetris, WINDOW *win, int incrementType)
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
        if (incrementType) // print things only if this taskM is called in the main loop
            printGameThings(tetris, win);
    }
}

void insertTetraminoTaskM(Tetris **tetris, WINDOW *win)
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
                    switchTetraminoTaskM(tetris, win, 0); // check next piece avaible
            }
        }
        printGameThings(tetris, win);
    }
}

void moveTetraminoTaskM(Tetris **tetris, WINDOW *win, char key)
{
    if (!tetris->gameStatus)
    {
        tetris->lastX = tetraminoXMoving(tetris->tetramino, tetris->lastX, key);
        printGameThings(tetris, win);
    }
}

void rotateTetraminoTaskM(Tetris **tetris, WINDOW *win)
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
