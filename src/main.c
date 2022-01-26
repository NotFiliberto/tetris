/**
 * @file main.c
 * @brief wrap all the things
 * @author Filiberto
 * @mainpage X-Tetris
 * @section Intro
 * X-Tetris game implementantion in C
 * @section Dependencies
 *
 * <ul>
 *      <li>MinGW (for windows users)</li>
 *      <li>ncurses <a href="https://e-l.unifi.it/pluginfile.php/805205/mod_resource/content/0/ncurses%20installation%20-%20en.pdf">tutorial</a></li>
 * </ul>
 *
 * @section Installation
 * <ol>
 *      <li>
 *          Download the repository
 *          <br />
 *          <code>git clone https://github.com/Filibertoo/tetris</code>
 *      </li>
 *      <li>
 *          Install every dependecies
 *      </li>
 *      <li>
 *          Go into the repository folder and then change directory
 *          <br />
 *          <code>cd src</code>
 *      </li>
 *      <li>
 *          Compile and run the game
 *          <br />
 *          <code>gcc main.c -o main -lncurses -ansi && ./main</code>
 *      </li>
 * </ol>
 *
 * @section Commands
 * Here the complete list of commands for the game. First of all you can select the game mode moving your selection with <code>W</code> key (up) or <code>D</code> key (down) and confirm with <code>ENTER</code>
 * <br />
 * When u join the game, here is a list of complete commands:
 *
 * <ul>
 *      <li><code>ESC</code>: exit from the gamemode select or close the "game"</li>
 *      <li><code>W</code>: rotate tetramino</li>
 *      <li><code>A</code>: move left</li>
 *      <li><code>D</code>: move rigth</li>
 *      <li><code>SPACE</code>: switch tetramino</li>
 *      <li><code>ENTER</code>: insert tetramino in the map</li>
 * </ul>
 *
 * If you selected multiplayer, the commands for the other player are the <b>same</b>.
 */

#include "gamemodes/gamemodes.h"

/**
 * @brief print menù for selecting the gamemode
 * 
 * @param game game object
 */
void printMenu(Game *game);

int main(void)
{
    srand(time(NULL));
    Game *game = createGame();
    int gamemodeSelectedFlag = 0;

    do
    {
        clear();
        printMenu(game);

        game->key = toupper(getch());
        if (game->key > -1)
        {
            /* default is -1 if u dont press anything*/
            if (game->key == ESC && getch() == '[')
                game->key = getch();

            switch (game->key)
            {
            case MOVE_UP:
                game->gamemode = Mod((game->gamemode - 1), 3);
                break;

            case MOVE_DOWN: /* left */
                game->gamemode = Mod((game->gamemode + 1), 3);
                break;

            case SELECT:
                gamemodeSelectedFlag = 1;
                break;
            }

            /* start game if selected */
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
                    game->playerTurn = 0; /* default start with human */
                    multiplayer(game);
                    break;
                }
                game->key = ' '; /* otherwhise it exit because the key is ESC */
            }
            gamemodeSelectedFlag = 0; /* reset because if player return back to menu after a game */
        }
        refresh();

    } while (game->key != ESC && game->gamemode != -1);

    endScreen();
    return 0;
}

void printMenu(Game *game)
{

    printwc(game->win, COLOR_WHITE, COLOR_BLUE, 0, "SELECT GAMEMODE\n\n", game->gamemode);

    char *gamemodes[] = {"Single Player", "Multi Player", "VS CPU"};

    int i;
    for (i = 0; i < 3; i++)
    {
        if (i == game->gamemode)
            printw("[ ");

        printw("%s", gamemodes[i]);

        if (i == game->gamemode)
            printw(" ]");

        NEW_LINE
    }

    printw("\n\nPress ESC to exit...");
}