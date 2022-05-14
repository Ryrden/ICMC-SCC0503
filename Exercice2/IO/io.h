#ifndef IO_H
#define IO_H

#include "../dataHandler/dataHandler.h"
#include "../primaryIndex/primaryIndex.h"
#include "../uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 256

// Observação, eu iria modularizar mais, mas n tive tempo (falta 2 minutos pra enviar), importante é passar

void run();
void readStudentFile(FILE *dataFile, unsigned int studentOffset);

#endif // !IO_H