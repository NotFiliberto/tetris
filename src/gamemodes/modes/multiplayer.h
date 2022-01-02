
int multiplayer(void)
{
    char key;

    while (1 && key != ESC)
    {
        clear();
        printw("Press ESC to exit multiplayer mode\n");
        key = toupper(getch());
        refresh();
    }

    return 0;
}

