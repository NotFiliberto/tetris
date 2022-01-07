#include "gamemodes/gamemodes.h"

void printMenu(WINDOW* win, int gamemode);

int main(void)
{

    char key;
    int gamemode = 0;
    int gamemodeSelected = 0;

    WINDOW *win = initScreen();

    do
    {
        clear();
        printMenu(win, gamemode);

        key = toupper(getch());
        if (key > -1)
        { // default is -1 if u dont press anything
            if (key == ESC && getch() == '[')
                key = getch(); 

            switch (key)
            {
            case MOVE_UP:
                gamemode = Mod((gamemode - 1), 3);
                break;

            case MOVE_DOWN: // left
                gamemode = Mod((gamemode + 1), 3);
                break;

            case SELECT:
                gamemodeSelected = 1;
                break;
            }

            // start game if selected
            if (gamemodeSelected)
            {
                switch (gamemode)
                {
                case SINGLE_PLAYER:
                    singlePlayer(win);
                    break;
                case MULTI_PLAYER: 
                    multiplayer(win);
                    break;
                }
            }
            gamemodeSelected = 0; //reset because if player return back to menu after a game
        }
        refresh();

    } while (key != ESC && gamemode != -1);

    endScreen();
    return 0;
}

void printMenu(WINDOW* win, int gamemode){

    printwc(win, COLOR_WHITE, COLOR_BLUE, 0, "SELECT GAMEMODE\n\n", gamemode);

    char* gamemodes[] = {"Single Player", "Multi Player", "VS CPU"};

    for(int i=0; i<3; i++){
        if(i==gamemode) printw("[ ");

        printw("%s", gamemodes[i]);

        if(i==gamemode) printw(" ]");

        NEW_LINE
    }

    printw("\n\nPress ESC to exit...");
}