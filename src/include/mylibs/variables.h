#define DEFAULT_HEIGHT 15
#define DEFAULT_WIDTH 10
#define ESC 27
#define GRAVITY 1 //ENABLED by default
#define DEFAULT_AVAILABILITY 10
#define SHOW_WALLS 1

//controls
#define SWITCH ' '
#define MOVE_DOWN 'S'
#define MOVE_UP 'W'
#define MOVE_RIGHT 'D'
#define MOVE_LEFT 'A'
#define SELECT '\n'

//graphic
#define EMPTY_SPACE " "
#define WALL "#"
#define PIECE "@"
#define SPACE_BETWEEN_PLAYERS_SCREEN 25
#define SPACE_BETWEEH_GAMES (DEFAULT_WIDTH + 2 + SPACE_BETWEEN_PLAYERS_SCREEN)

//gamemodes
#define SINGLE_PLAYER 0
#define MULTI_PLAYER 1
#define VS_CPU 2

//usefull
#define NEW_LINE printw("\n");

//For colors
typedef struct playerColor{
    int textColor;
    int backgroudColor;
} PlayerColor;

PlayerColor playerColors[] = {
    {COLOR_WHITE, COLOR_MAGENTA},
    {COLOR_MAGENTA, COLOR_WHITE}
};