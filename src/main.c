#include "gamemodes/gamemodes.h"

void printMenu(Game* game);

int main(void)
{
    srand(time(NULL));
    Game* game = createGame();
    int gamemodeSelectedFlag = 0;

    do
    {
        clear();
        printMenu(game);

        game->key = toupper(getch());
        if (game->key > -1)
        { // default is -1 if u dont press anything
            if (game->key == ESC && getch() == '[')
                game->key = getch(); 

            switch (game->key)
            {
            case MOVE_UP:
                game->gamemode = Mod((game->gamemode - 1), 3);
                break;

            case MOVE_DOWN: // left
                game->gamemode = Mod((game->gamemode + 1), 3);
                break;

            case SELECT:
                gamemodeSelectedFlag = 1;
                break;
            }

            // start game if selected
            if (gamemodeSelectedFlag)
            {
                switch (game->gamemode)
                {
                case SINGLE_PLAYER:
                    multiplayer(game);
                    break;
                case MULTI_PLAYER: 
                    multiplayer(game);
                    break;
                case VS_CPU:
                    game->playerTurn = 0; //default start with human
                    multiplayer(game);
                    break;
                }
                game->key = ' '; //otherwhise it exit because the key is ESC
            }
            gamemodeSelectedFlag = 0; //reset because if player return back to menu after a game
        }
        refresh();

    } while (game->key != ESC && game->gamemode != -1);

    endScreen();
    return 0;
}

void printMenu(Game* game){

    printwc(game->win, COLOR_WHITE, COLOR_BLUE, 0, "SELECT GAMEMODE\n\n", game->gamemode);

    char* gamemodes[] = {"Single Player", "Multi Player", "VS CPU"};

    for(int i=0; i<3; i++){
        if(i==game->gamemode) printw("[ ");

        printw("%s", gamemodes[i]);

        if(i==game->gamemode) printw(" ]");

        NEW_LINE
    }

    printw("\n\nPress ESC to exit...");
}