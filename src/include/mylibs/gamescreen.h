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
    if(input == '\n'){
        if ((x + t->width > DEFAULT_WIDTH))
            x = DEFAULT_WIDTH-t->width;
    }

    return x;
}

void printMatrixW(Matrix *matrix, int rspace, int offsetX, int offsetY)
{
    for (int row = offsetY; row < matrix->rows; row++)
    {
        for (int i = 0; i < rspace; i++)
            printw(" "); // space for better visualization
        for (int col = offsetX; col < matrix->cols; col++)
        {
            printw("%d", matrix->map[col + row * matrix->cols]);
        }
        printw("\n");
    }
}