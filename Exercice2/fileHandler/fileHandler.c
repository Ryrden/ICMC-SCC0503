#include "fileHandler.h"

struct fileHeader_st {
    unsigned int nRegister;
    unsigned char regSize;
    int stackHead;
};

FILEHEADER *getHeader(FILE *){
//Desenvolver
}

boolean writeHeader(FILE *, FILEHEADER *){
//Desenvolver
}
