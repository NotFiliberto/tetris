/**
 * @file headers.h
 * @brief library wrapper for the other libraries 
 */

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <curses.h> /* to implement cross platform non blocking terminal keyboard input */
#include <unistd.h>
/* #include <sys/ioctl.h> */
#include <string.h>
#include "mylibs/variables.h"
#include "mylibs/utils.h"
#include "mylibs/matrix.h"
#include "mylibs/tetramini.h"
#include "mylibs/tetris.h"
#include "mylibs/gamescreen.h"
#include "mylibs/game.h"
