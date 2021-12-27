int tetraminoXMoving(Tetramino *t, int x, char input)
{
    if (input == 'A' || input == 'D')
    {
        int op = (input == 'A') ? -1 : 1;
        if (input == 'A' && (x - 1 > -1))
            x += op;
        if (input == 'D' && (x + t->width < DEFAULT_WIDTH))
            x += op;
    }
    if (input == '\n')
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
            printw(" "); // space for better visualization

        if (printWalls && !tetramino)
        {
            if ((col + row * matrix->cols) % matrix->cols == 0)
                printw("#");
        }
        else

            printw(" "); // ad left space for correct visualization of the waall

        for (col = offsetX; col < matrix->cols; col++)
        {
            if (matrix->map[col + row * matrix->cols] == 1)
                printw("%c", '@');
            else
                printw("%c", ' ');
        }

        if (printWalls && !tetramino)
        {
            // if(row==0) printw("-> col: %d", col);
            if ((col + row * matrix->cols) % matrix->cols == 0)
                printw("#");
        }

        printw("\n");
    }

    if (printWalls && !tetramino)
    {
        for (i = 0; i < rspace; i++)
            printw(" "); // space for better visualization

        int j = 0;
        for (j = 0; j < matrix->cols + 2; j++) // left and right walls
        {
            printw("#");
        }
    }

    //prevent moving matrix to the bottom while switching/rotating the tetramino
    if(tetramino){
        //printw("offsetX: %d, offsetY: %d\n", offsetX, offsetY);
        for(int i=0; i<offsetY; i++){
            printw("\n");
        }
        if(matrix->rows == 3) printw("\n"); //add line for every piece exept I
    }
}
