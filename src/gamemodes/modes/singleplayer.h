void printGameThings(Game* game);
void switchTetraminoTask(Game* game, int incrementType);
void insertTetraminoTask(Game* game);
void moveTetraminoTask(Game* game);
void rotateTetraminoTask(Game* game);

void testing(Game* game);

int singlePlayer(Game* game)
{
    game->numberOfPlayers = 1;
    game->tetris = (Tetris **)malloc(sizeof(Tetris *) * 1);
    game->tetris[0] = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    printGameThings(game);

    while (1 && game->key != ESC)
    {
        game->key = toupper(getch());
        if (game->key > -1)
        { // default is -1 if u dont press anything
            if (game->key == ESC && getch() == '[')
                game->key = getch(); // prevent exit if user press ARROW KEYS becuase when it happen getch will push 3 values into the buffer (ESC + [ + ARROW_KEY)
            // printw("%c", toupper(game->key));

            switch (game->key)
            {
            case SWITCH:
                switchTetraminoTask(game, 1);
                break;
            case SELECT:
                insertTetraminoTask(game);
                break;

            case MOVE_LEFT: // left
                moveTetraminoTask(game);
                break;

            case MOVE_RIGHT: // right
                moveTetraminoTask(game);
                break;
            case MOVE_UP:
                rotateTetraminoTask(game);
                break;
            case '-': // for testing stuffs
                testing(game);
                break;

            default:
                break;
            }
        }
        refresh();
    }

    deleteTetris(game->tetris[0]);
    return 0;
}

void printGameThings(Game *game)
{
    clear();
    printwc(game->win, COLOR_WHITE, COLOR_MAGENTA, 0, "Score: %d\n\n", game->tetris[0]->score);

    if (totalAvailability(game->tetris[0]) > 0)
        printTetraminiAvailability(game->tetris[0], 2); // check avaibility
    else
    {
        printwc(game->win, COLOR_WHITE, COLOR_RED, 0, "\nno avaible pieces");
    }

    // check game status
    if (game->tetris[0]->gameStatus == 1)
    {
        printwc(game->win, COLOR_WHITE, COLOR_RED, 0, "\nGAME OVER");
    }

    printw("\n\n");
    printMatrixW(game->win, &game->tetris[0]->tetramino->matrix, game->tetris[0]->lastX, game->tetris[0]->tetramino->offsetX, game->tetris[0]->tetramino->offsetY, SHOW_WALLS, 1);
    printMatrixW(game->win, game->tetris[0]->matrix, 0, 0, 0, SHOW_WALLS, 0);
    printw("\n\n");
}

void switchTetraminoTask(Game* game, int incrementType)
{
    if (!game->tetris[0]->gameStatus)
    {
        if (totalAvailability(game->tetris[0]) > 0 && !game->tetris[0]->gameStatus)
        {
            int currentTetraminoType = game->tetris[0]->tetramino->code;

            if (incrementType)                                             // only in main game loop
                game->tetris[0]->tetraminoType = (game->tetris[0]->tetramino->code + 1) % 7; // next tetramino
            game->tetris[0]->tetraminoType = nextTetraminoAvailable(game->tetris[0]);        // if avaible return the incremente tetramino in the line before otherwhise it finds automatically the ones avalaible

            if (currentTetraminoType != (game->tetris[0]->tetraminoType))
            {                                                                           // to save current rotation
                deleteTetramino(game->tetris[0]->tetramino);                                     // delete old tetramino and all his stuffs
                game->tetris[0]->tetramino = createTetramino(&tetramini[game->tetris[0]->tetraminoType]); // create new tetramino
            }

            game->tetris[0]->lastX = tetraminoXMoving(game->tetris[0]->tetramino, game->tetris[0]->lastX, SWITCH); // check x pos for the visualization
        }
        if (incrementType) // print things only if this task is called in the main loop
            printGameThings(game);
    }
}

void insertTetraminoTask(Game* game)
{
    if (!game->tetris[0]->gameStatus)
    {
        int points = 0;
        if (tetraminoAvailability(game->tetris[0], game->tetris[0]->tetramino->code) > 0)
        {
            if (insertTetramino(game->tetris[0]->matrix, game->tetris[0]->tetramino, game->tetris[0]->lastX, 0, GRAVITY, 1))
            {
                decrementTetraminoAvailability(game->tetris[0], game->tetris[0]->tetramino->code);

                points = scorePoints(game->tetris[0]);

                if (points)
                {
                    game->tetris[0]->score += points;
                }
                game->tetris[0]->gameStatus = gameEnded(game->tetris[0]);

                if (!game->tetris[0]->gameStatus)                 // swap piece automaticly if needed
                    switchTetraminoTask(game, 0); // check next piece avaible
            }
        }
        printGameThings(game);
    }
}

void moveTetraminoTask(Game* game)
{
    if (!game->tetris[0]->gameStatus)
    {
        game->tetris[0]->lastX = tetraminoXMoving(game->tetris[0]->tetramino, game->tetris[0]->lastX, game->key);
        printGameThings(game);
    }
}

void rotateTetraminoTask(Game* game)
{
    if (!game->tetris[0]->gameStatus)
    {

        game->tetris[0]->tetramino = rotateTetramino(game->tetris[0]->tetramino);
        game->tetris[0]->lastX = tetraminoXMoving(game->tetris[0]->tetramino, game->tetris[0]->lastX, SWITCH); // fix the position

        printGameThings(game);
    }
}

void testing(Game* game)
{
    invertTetrisRows(game->tetris[0], 3);
    printGameThings(game);
    printw("--> testing");
}