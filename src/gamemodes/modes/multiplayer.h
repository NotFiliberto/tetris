void printGameThingsMultiplayer(Tetris *tetris[], int n, int playerTurn, WINDOW *win);

int multiplayer(WINDOW* win)
{
    char key;
    int players = 2;
    int playerTurn = 0;

    Tetris *tetris[2];
    tetris[0] = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    tetris[1] = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    clear();

    //set up same pull for pieces
    int* availableTetramini = (int *)malloc(sizeof(int) * 7);
    for (int i = 0; i < 7; i++)
    {
        availableTetramini[i] = DEFAULT_AVAILABILITY*players;
    }

    tetris[0]->availableTetramini = availableTetramini;
    tetris[1]->availableTetramini = availableTetramini;

    printGameThingsMultiplayer(tetris, players, playerTurn, win);

    while (1 && key != ESC)
    {
        //clear();
        //printw("\n\nPress ESC to exit multiplayer mode\n");

        key = toupper(getch());
        refresh();
    }

    return 0;
}

void printGameThingsMultiplayer(Tetris *tetris[], int n, int playerTurn, WINDOW *win)
{
    clear();
    //printMatrixW(tetris[1]->matrix, 0, 0, 0, SHOW_WALLS, 0);
    printGameStats(tetris, n, playerTurn, win);
    printTetris(tetris, n, playerTurn, win);
}
