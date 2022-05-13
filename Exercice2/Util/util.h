#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define ERRO -32000

typedef int boolean;
typedef unsigned int KEY;


char *readStringUntilReach(char);

char *readLine();

long int getDataSize(FILE *, long);

void verifyNullPointerExceptionToFile(FILE *);

#endif // UTIL_H
