
/**
 * @file game.h
 * @brief library for the game object
 *
 */

/** @struct Game
 *  @brief Structure to rappresent the game and all stuffs related to it, used to wrap all the things
 *
 *  @param key it contains the keyboard's input
 *  @param win store the current window used by the terminal
 *  @param tetris store all the tetris sessions
 *  @param gamemode gamemode selected
 *  @param playerTurn code of the current player
 *
 */
typedef struct game
{
    char key;        /* input key */
    WINDOW *win;     /* screen */
    Tetris **tetris; /* array of tetris game */
    int gamemode;
    int numberOfPlayers;
    int playerTurn;
} Game;

/**
 * @brief Create a Game object
 *
 * @return Game* object
 */
Game *createGame()
{
    Game *game = (Game *)malloc(sizeof(Game));
    game->win = initScreen();
    game->gamemode = 0;
    game->numberOfPlayers = 0;
    game->playerTurn = 0;
    return game;
}

/**
 * @brief delete game object
 *
 * @param game object to delete
 */
void deleteGame(Game *game)
{
    free(game);
}