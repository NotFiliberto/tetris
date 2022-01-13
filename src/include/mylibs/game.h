typedef struct game{
    char key; /* input key */
    WINDOW *win;     /* screen */
    Tetris **tetris; /* array of tetris game */
    int gamemode;
    int numberOfPlayers;
    int playerTurn;
}Game;

Game* createGame(){
    Game* game = (Game*) malloc(sizeof(Game));

    game->win = initScreen();
    game->gamemode = 0;
    game->numberOfPlayers = 0;
    game->playerTurn = 0;

    return game;
}

void deleteGame(Game* game){
    free(game);
}