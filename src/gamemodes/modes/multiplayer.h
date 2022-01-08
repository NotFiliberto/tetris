Tetris **initGame(int numberOfPlayers);
void printGameThingsMultiplayer(Game *game);

void switchTetraminoTaskM(Game *game, int incrementType);
void insertTetraminoTaskM(Game *game);
void moveTetraminoTaskM(Game *game);
void rotateTetraminoTaskM(Game *game);

int multiplayer(Game *game)
{

    game->numberOfPlayers = 2;
    game->tetris = initGame(game->numberOfPlayers); // init with same pieces pull and create multiple Tetris obj
    printGameThingsMultiplayer(game);

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
                switchTetraminoTaskM(game, 1);
                break;
            case SELECT:
                insertTetraminoTaskM(game);
                break;

            case MOVE_LEFT: // left
                moveTetraminoTaskM(game);
                break;

            case MOVE_RIGHT: // right
                moveTetraminoTaskM(game);
                break;
            case MOVE_UP:
                rotateTetraminoTaskM(game);
                break;

            default:
                break;
            }
        }
        refresh();
    }

    for (int i = 0; i < game->numberOfPlayers; i++)
    {
        deleteTetris(game->tetris[i]);
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

void printGameThingsMultiplayer(Game *game)
{
    clear();
    printGameStats(game->tetris, game->numberOfPlayers, game->playerTurn, game->win);

    printw("\n\n---> Player Turn: ");
    printwc(game->win, playerColors[game->playerTurn].textColor, playerColors[game->playerTurn].backgroudColor, game->playerTurn, "%d\n\n", game->playerTurn);

    printTetris(game->tetris, game->numberOfPlayers, game->playerTurn, game->win);
}

int nextPlayerTurn(Game *game)
{
    int turn = game->playerTurn;
    return (game->playerTurn + 1) % game->numberOfPlayers;
}

int gameStatus(Game *game)
{
    int gameStatus = 0; // not finished

    if (totalAvailability(game->tetris[0]) <= 0)
        gameStatus = 1;

    for (int i = 0; i < game->numberOfPlayers; i++)
    {
        if (game->tetris[i]->gameStatus == 1)
            gameStatus = 1;
    }
    return gameStatus;
}

void switchTetraminoTaskM(Game *game, int incrementType)
{
    if (!gameStatus(game))
    {
        if (totalAvailability(game->tetris[game->playerTurn]) > 0 && !gameStatus(game))
        {
            int currentTetraminoType = game->tetris[game->playerTurn]->tetramino->code;

            if (incrementType)                                                                                             // only in main game loop
                game->tetris[game->playerTurn]->tetraminoType = (game->tetris[game->playerTurn]->tetramino->code + 1) % 7; // next tetramino

            for (int i = 0; i < game->numberOfPlayers; i++)
            {
                game->tetris[i]->tetraminoType = nextTetraminoAvailable(game->tetris[i]); // if avaible return the incremente tetramino in the line before otherwhise it finds automatically the ones avalaible

                if (currentTetraminoType != (game->tetris[i]->tetraminoType))
                {                                                                                             // to save current rotation
                    deleteTetramino(game->tetris[i]->tetramino);                                              // delete old tetramino and all his stuffs
                    game->tetris[i]->tetramino = createTetramino(&tetramini[game->tetris[i]->tetraminoType]); // create new tetramino
                }

                game->tetris[i]->lastX = tetraminoXMoving(game->tetris[i]->tetramino, game->tetris[i]->lastX, SWITCH); // check x pos for the visualization
            }
        }
        if (incrementType) // print things only if this task is called in the main loop
            printGameThingsMultiplayer(game);
    }
}

void insertTetraminoTaskM(Game *game)
{
    if (!gameStatus(game))
    {
        int points = 0;
        if (tetraminoAvailability(game->tetris[game->playerTurn], game->tetris[game->playerTurn]->tetramino->code) > 0)
        {
            if (insertTetramino(game->tetris[game->playerTurn]->matrix, game->tetris[game->playerTurn]->tetramino, game->tetris[game->playerTurn]->lastX, 0, GRAVITY, 1))
            {
                decrementTetraminoAvailability(game->tetris[game->playerTurn], game->tetris[game->playerTurn]->tetramino->code);

                points = scorePoints(game->tetris[game->playerTurn]);

                if (points)
                {
                    game->tetris[game->playerTurn]->score += points;
                }
                game->tetris[game->playerTurn]->gameStatus = gameEnded(game->tetris[game->playerTurn]);

                if (!game->tetris[game->playerTurn]->gameStatus) // swap piece automaticly if needed
                    switchTetraminoTaskM(game, 0);               // check next piece avaible
                game->playerTurn = nextPlayerTurn(game);
            }
        }
        printGameThingsMultiplayer(game);
    }
}

void moveTetraminoTaskM(Game *game)
{
    if (!gameStatus(game))
    {
        game->tetris[game->playerTurn]->lastX = tetraminoXMoving(game->tetris[game->playerTurn]->tetramino, game->tetris[game->playerTurn]->lastX, game->key);
        printGameThingsMultiplayer(game);
    }
}

void rotateTetraminoTaskM(Game *game)
{
    if (!gameStatus(game))
    {

        game->tetris[game->playerTurn]->tetramino = rotateTetramino(game->tetris[game->playerTurn]->tetramino);
        game->tetris[game->playerTurn]->lastX = tetraminoXMoving(game->tetris[game->playerTurn]->tetramino, game->tetris[game->playerTurn]->lastX, SWITCH); // fix the position

        printGameThingsMultiplayer(game);
    }
}
