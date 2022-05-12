#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define ERRO -32000

typedef int boolean;

char *readStringUntilReach(char);

char *readLine();

long int getDataSize(FILE *, long);

#endif // UTIL_H
