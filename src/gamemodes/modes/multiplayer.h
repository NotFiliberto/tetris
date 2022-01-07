void printGameThingsMultiplayer(Tetris *tetris[], int n, WINDOW *win);

int multiplayer(WINDOW* win)
{
    char key;

    Tetris *tetris[2];
    tetris[0] = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    tetris[1] = createTetris(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    clear();

    //set up same pull for pieces
    int* availableTetramini = (int *)malloc(sizeof(int) * 7);
    for (int i = 0; i < 7; i++)
    {
        availableTetramini[i] = DEFAULT_AVAILABILITY*2;
    }

    tetris[0]->availableTetramini = availableTetramini;
    tetris[1]->availableTetramini = availableTetramini;


    
    tetris[0]->matrix->map[0] = 1;
    tetris[1]->matrix->map[17] = 1;
    printGameThingsMultiplayer(tetris, 2, win);

    while (1 && key != ESC)
    {
        //clear();
        //printw("\n\nPress ESC to exit multiplayer mode\n");

        key = toupper(getch());
        refresh();
    }

    return 0;
}

void printGameThingsMultiplayer(Tetris *tetris[], int n, WINDOW *win)
{

    //printMatrixW(tetris[1]->matrix, 0, 0, 0, SHOW_WALLS, 0);
    printGameStats(tetris, n, win);
}
