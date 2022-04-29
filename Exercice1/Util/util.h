#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define ERROR -32000

typedef int boolean;

void boolean_print(boolean bool);

char *readStringUntilReach(char *string, char caractere);

char *readLine();

long int getDataSize(FILE *);
#endif // UTIL_H
