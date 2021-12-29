WINDOW* initScreen()
{
    WINDOW *win;

    // initialization
    win = initscr(); // new screen will be created
    nodelay(win, TRUE);
    noecho();

    start_color();
    return win;
}

void endScreen()
{
    endwin();
}

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

void printMatrixW(Matrix *matrix, int rspace, int offsetX, int offsetY, int printWalls, int tetramino)
{
    int row = 0, col = 0, i = 0;
    for (row = offsetY; row < matrix->rows; row++)
    {
        for (i = 0; i < rspace; i++)
            printw(EMPTY_SPACE); // space for better visualization

        if (printWalls && !tetramino)
        {
            if ((col + row * matrix->cols) % matrix->cols == 0)
                printw(WALL);
        }
        else

            printw(EMPTY_SPACE); // ad left space for correct visualization of the waall

        for (col = offsetX; col < matrix->cols; col++)
        {
            if (matrix->map[col + row * matrix->cols] == 1)
                printw(PIECE);
            else
                printw(EMPTY_SPACE);
        }

        if (printWalls && !tetramino)
        {
            // if(row==0) printw("-> col: %d", col);
            if ((col + row * matrix->cols) % matrix->cols == 0)
                printw(WALL);
        }

        NEW_LINE
    }

    if (printWalls && !tetramino)
    {
        for (i = 0; i < rspace; i++)
            printw(EMPTY_SPACE); // space for better visualization

        int j = 0;
        for (j = 0; j < matrix->cols + 2; j++) // left and right walls
        {
            printw(WALL);
        }
    }

    //prevent moving matrix to the bottom while switching/rotating the tetramino
    if(tetramino){
        //printw("offsetX: %d, offsetY: %d\n", offsetX, offsetY);
        for(int i=0; i<offsetY; i++){
            NEW_LINE
        }
        if(matrix->rows == 3) NEW_LINE //add line for every piece exept I
    }
}

//printc with colors
void printwc(WINDOW* win, int textColor, int textBackground, char* text, ...)
{
    int pairnumber = textColor + textBackground; //problem with ncurses it saves this number in init_pair so i have to chage it with different colors combinations
    init_pair(pairnumber, textColor, textBackground);
    attron(COLOR_PAIR(pairnumber));

    va_list args;

    va_start(args, text);
    vwprintw(win, text, args);
    va_end(args);

    attroff(COLOR_PAIR(pairnumber));
}