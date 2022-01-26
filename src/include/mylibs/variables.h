/**
 * @file variables.h
 * @brief Library that contains the variables for the game.
 *
 * In that file are containted all variables reletated to the game, for game, for example the default width of the matrix map, or some other stuffs very useful
 */

/**
 * @defgroup Game_options
 * @brief default game options constants
 *
 * @{
 */

/**
 * @brief default tetris map's heigth
 */
#define DEFAULT_HEIGHT 15
/**
 * @brief default tetris map's width
 */
#define DEFAULT_WIDTH 10
/**
 * @brief tetris pieces's graivity, enabled by default
 *
 */
#define GRAVITY 1
/**
 * @brief default availability for every type of tetramino
 *
 */
#define DEFAULT_AVAILABILITY 10
/**
 * @brief show/hide tetris's walls
 *
 */
#define SHOW_WALLS 1

/** @} */

/**
 * @defgroup controls
 * @brief control mapping constants
 *
 * @{
 */

/**
 * @brief ESC key
 *
 */
#define ESC 27
/**
 * @brief switch key
 *
 */
#define SWITCH ' '
/**
 * @brief move down key
 *
 */
#define MOVE_DOWN 'S'
/**
 * @brief move up key
 *
 */
#define MOVE_UP 'W'
/**
 * @brief move right key
 *
 */
#define MOVE_RIGHT 'D'
/**
 * @brief move left key
 *
 */
#define MOVE_LEFT 'A'
/**
 * @brief select key
 *
 */
#define SELECT '\n'

/** @} */

/**
 * @defgroup graphic
 *
 * @{
 */

/**
 * @brief empty space character
 *
 */
#define EMPTY_SPACE " "
/**
 * @brief wall character
 *
 */
#define WALL "#"
/**
 * @brief piece character
 *
 */
#define PIECE "@"
/**
 * @brief padding between players maps
 *
 */
#define SPACE_BETWEEN_PLAYERS_SCREEN 25
/**
 * @brief space between players games, considering the score and other stats
 *
 */
#define SPACE_BETWEEN_GAMES (DEFAULT_WIDTH + 2 + SPACE_BETWEEN_PLAYERS_SCREEN)

/** @} */

/**
 * @defgroup gamemodes
 * @brief game modes codification
 *
 * @{
 */

/**
 * @brief single player
 *
 */
#define SINGLE_PLAYER 0
/**
 * @brief player vs player
 *
 */
#define MULTI_PLAYER 1
/**
 * @brief player vs CPU
 *
 */
#define VS_CPU 2
/** @} */

/**
 * @brief constants to print in a new line
 *
 */
#define NEW_LINE printw("\n");

/* For colors */

/**
 * @brief player colors structure to define text color for stats of a specific player
 * 
 * @param textColor text color
 * @param backgroudColor backgroud color
 * 
 */
typedef struct playerColor
{
    int textColor;
    int backgroudColor;
} PlayerColor;

/**
 * @brief global array to set the default color for the text for every player
 * 
 */
PlayerColor playerColors[] = {
    {COLOR_WHITE, COLOR_MAGENTA},
    {COLOR_MAGENTA, COLOR_WHITE}};