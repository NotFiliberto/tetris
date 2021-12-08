int manageTetraminoXInput(Tetramino* t, int x, char input)
{
    if(input == 'A' || input == 'D'){
        int op = (input == 'A') ? -1 : 1;
        if (input == 'A' && (x - 1 > -1))
            return x + op;
        if (input == 'D' && (x + t->width < DEFAULT_WIDTH))
            return x + op;
    }

    return x;
}

void printMatrixW(Matrix *matrix, int rspace)
{
    for (int row = 0; row < matrix->rows; row++)
    {
        for (int i = 0; i < rspace; i++) printw(" "); //space for better visualization 
        for (int col = 0; col < matrix->cols; col++)
        {
            printw("%d", matrix->map[col + row * matrix->cols]);
        }
        printw("\n");
    }
}