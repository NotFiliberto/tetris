
/** @struct Game
 *  @brief A structure to rappresent the game and all stuffs related to it
 *
 *  @var Game::key it contains the keyboard's input
 *  @var Game::win store the current window used by the terminal
 *  @var Game::tetris store all the tetris sessions
 *  @var Game::gamemode gamemode selected
 *  @var Game::playerTurn code of the current player
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