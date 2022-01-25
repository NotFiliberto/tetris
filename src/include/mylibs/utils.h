#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLS system("CLS");

/**
 * @brief string type
 *
 * type to rappresent a string
 */
typedef char *String;

/**
 * @brief convert character to int
 *
 * @param c character to convert
 * @return int number that corresponds to the character
 */
int charToInt(char c)
{
    return c - '0';
}

/**
 * @brief convert int to char
 *
 * @param i int number to convert
 * @return character that corresponds to the int number
 */
char intToChar(int i)
{
    return i + '0';
}

/* module func for negative and positive numbers */
/**
 * @brief % operator without sign
 *
 * @param x number
 * @param m value of the module
 * @return result of the operation (x%m) without the sign
 */
int Mod(int x, int m)
{
    return (x % m + m) % m;
}