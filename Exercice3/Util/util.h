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

void verifyNullPointerExceptionToFile(FILE *);

boolean isBigger(void*, void*);

boolean isSmaller(void*, void*);

boolean isEqual(void*, void*);

#endif // UTIL_H
