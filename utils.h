#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLS system("CLS");

typedef char *String;

int charToInt(char c)
{
    return c - '0';
}

char intToChar(int i){
    return i+'0';
}

//module func for negative and positive numbers
int Mod(int x, int m){
    return (x%m +m)%m;
}