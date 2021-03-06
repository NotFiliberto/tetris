/**
 * @file gamescreen.h
 * @brief library for the correct visualization of the game in the terminal
 *
 */

/**
 * @brief init screen with ncurses
 * 
 * @return WINDOW* that rappresent the terminal window created 
 */
WINDOW *initScreen()
{
    WINDOW *win;

    /* initialization  */
    win = initscr(); /* new screen will be created */
    nodelay(win, TRUE);
    noecho();

    start_color();
    return win;
}

/**
 * @brief delete screen created with ncurses
 * 
 */
void endScreen()
{
    endwin();
}

/**
 * @brief move the tetramino in the x axis if possible
 *
 * @param t the tetramino to be moved
 * @param x current position of the first cell of the tetramino in the matrix map
 * @param input left/right or switch that automaticly fit the tetramino into the matrix width range
 * @return the current position of the first cell of the tetramino in the matrix map
 */
int tetraminoXMoving(Tetramino *t, int x, char input)
{
    if (input == MOVE_LEFT || input == MOVE_RIGHT)
    {
        int op = (input == MOVE_LEFT) ? -1 : 1;
        if (input == MOVE_LEFT && (x - 1 > -1))
            x += op;
        if (input == MOVE_RIGHT && (x + t->width < DEFAULT_WIDTH))
            x += op;
    }
    if (input == SWITCH)
    {
        if ((x + t->width > DEFAULT_WIDTH))
            x = DEFAULT_WIDTH - t->width;
    }

    return x;
}

/**
 * @brief print matrix in the terminal (tetramino map or tetris matrix map)
 *
 * @param win the current screen used by ncurses
 * @param matrix the matrix that has to be printed
 * @param lastXPos current position (x) of the first cell of the tetramino in the matrix map
 * @param offsetX x offset of the tetramino (considering the tetramino map, not the tetris map)
 * @param offsetY y offset of the tetramino (considering the tetramino map, not the tetris map)
 * @param printWalls flag for printing walls
 * @param tetramino flag to tell the functions if the matrix is a rappresentation of the tetris map or tetramino map (1 if it rappresents a tetramino)
 */
void printMatrixW(WINDOW *win, Matrix *matrix, int lastXPos, int offsetX, int offsetY, int printWalls, int tetramino)
{
    int row = 0, col = 0, i = 0;
    int xScreenStart = getcurx(win), yScreenStart = getcury(win); /* coord cursor of window screen */
    for (row = offsetY; row < matrix->rows; row++)
    {
        for (i = 0; i < lastXPos; i++)
            printw(EMPTY_SPACE); /* space for better visualization */

        if (printWalls && !tetramino)
        {
            if ((col + row * matrix->cols) % matrix->cols == 0)
                printw(WALL);
        }
        else

            printw(EMPTY_SPACE); /* ad left space for correct visualization of the waall */

        for (col = offsetX; col < matrix->cols; col++)
        {
            if (matrix->map[col + row * matrix->cols] == 1)
                printw(PIECE);
            else
                printw(EMPTY_SPACE);
        }

        if (printWalls && !tetramino)
        {
            /* if(row==0) printw("-> col: %d", col); */
            if ((col + row * matrix->cols) % matrix->cols == 0)
                printw(WALL);
        }

        /* NEW_LINE */
        wmove(win, getcury(win) + 1,xScreenStart);
    }

    if (printWalls && !tetramino)
    {
        for (i = 0; i < lastXPos; i++)
            printw(EMPTY_SPACE); /* space for better visualization */

        int j = 0;
        for (j = 0; j < matrix->cols + 2; j++) /* left and right walls */
        {
            printw(WALL);
        }
    }

    /* prevent moving matrix to the bottom while switching/rotating the tetramino */
    if (tetramino)
    {
        /* printw("offsetX: %d, offsetY: %d\n", offsetX, offsetY); */
        int i=0;
        for ( i = 0; i < offsetY; i++)
        {
            /* NEW_LINE */
            wmove(win, getcury(win) + 1,xScreenStart);
        }
        if (matrix->rows == 3)
        {
            /* NEW_LINE  */
            /* add line for every piece exept I */
            wmove(win, getcury(win) + 1,xScreenStart);
        }
    }
}

/**
 * @brief print in the terminal like printf but with colors
 *
 * @param win the current screen used by ncurses
 * @param textColor color of the text
 * @param textBackground color of the backgroud
 * @param pairCodeModifier code used to identify a specif color pairing
 * @param text string to be printed
 * @param ... any other variable specified in the text string
 */
void printwc(WINDOW *win, int textColor, int textBackground, int pairCodeModifier, char *text, ...)
{

    int pairnumber = textColor + textBackground + pairCodeModifier; /* problem with ncurses it saves this number in init_pair so i have to chage it with different colors combinations */
    init_pair(pairnumber, textColor, textBackground);
    attron(COLOR_PAIR(pairnumber));

    va_list args; /* ... params */

    va_start(args, text);
    vwprintw(win, text, args);
    va_end(args);

    attroff(COLOR_PAIR(pairnumber));
}

/**
 * @brief print game stats for every "tetris game session"
 *
 * @param tetris tetris array that contains all the "sessions"
 * @param numberOfPlayers number of players in the current gamemode
 * @param playerTurn current player turn
 * @param win the current screen used by ncurses
 */
void printGameStats(Tetris** tetris, int numberOfPlayers, int playerTurn, WINDOW *win)
{

    int yScreenStart = getcury(win), i;
    /* score */
    for ( i = 0; i < numberOfPlayers; i++)
    {
        wmove(win, yScreenStart, SPACE_BETWEEN_GAMES * i);
        printwc(win, playerColors[i].textColor, playerColors[i].backgroudColor, i, "Score player [%d]: %d", i, tetris[i]->score);
    }
    
    NEW_LINE

    for ( i = 0; i < numberOfPlayers; i++)
    {
        /* check game status */
        if (tetris[i]->tetrisStatus == 1)
        {
            char endGameStr[] = "The game is over!";
            wmove(win, getcury(win)+1, ((SPACE_BETWEEN_GAMES * (numberOfPlayers-1)) + DEFAULT_WIDTH)/2 - (strlen(endGameStr)/2));
            printwc(win, COLOR_WHITE, COLOR_RED, 0, endGameStr);

            /* print winner */
            if(numberOfPlayers > 1){
                int w = getWinner(tetris, numberOfPlayers); 
                char winnerStr[50] = "WINNER: player [%d]";
                if(w == -1)
                    (void)strncpy(winnerStr, "WINNER: None, same score for each player", sizeof(winnerStr));
                wmove(win, getcury(win) + 1, ((SPACE_BETWEEN_GAMES * (numberOfPlayers - 1)) + DEFAULT_WIDTH) / 2 - (strlen(winnerStr) / 2));
                printwc(win, COLOR_GREEN, COLOR_CYAN, 1, winnerStr, w);
            }
        }
    }

    NEW_LINE
    NEW_LINE

    printTetraminiAvailability(tetris[playerTurn], 7); /* the availability and piece selected change based on the player turn */
}

/**
 * @brief print every "tetris session" (current tetramino selected and the tetris map)
 *
 * @param tetris tetris array that contains all the "sessions"
 * @param numberOfPlayers number of players in the current gamemode
 * @param playerTurn current player turn
 * @param win the current screen used by ncurses
 */
void printTetris(Tetris** tetris, int numberOfPlayers, int playerTurn, WINDOW *win)
{
    printw("\n\n");

    int yScreenStart = getcury(win),i;
    for ( i = 0; i < numberOfPlayers; i++)
    {
        wmove(win, yScreenStart, SPACE_BETWEEN_GAMES * i);

        printMatrixW(win, &tetris[i]->tetramino->matrix, tetris[i]->lastX, tetris[i]->tetramino->offsetX, tetris[i]->tetramino->offsetY, SHOW_WALLS, 1);
        printMatrixW(win, tetris[i]->matrix, 0, 0, 0, SHOW_WALLS, 0);
    }

    printw("\n\n");
}