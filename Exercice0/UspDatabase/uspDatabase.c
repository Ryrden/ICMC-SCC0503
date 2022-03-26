#include "uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_st{
    int nUsp;
    char name[50];
    char course[50];
    float grade;
};


operation select_command(int command) {

    if (command == 1)
        return all;
    else if (command == 2)
        return halfFromStart;
    else if (command == 3)
        return halfFromEnd;
    else if (command == 4)
        return fromRangeTo;
    else if (command == 5)
        return specificData;

    return ERROR;
}