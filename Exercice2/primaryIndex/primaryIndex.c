#include "primaryIndex.h"

struct indexFile_st {
    unsigned int primaryKey;
    unsigned int offSet;
};

INDEXFILE *createIndexData(unsigned int key, unsigned int offSet) {
    INDEXFILE *index = (INDEXFILE *)malloc(sizeof(INDEXFILE));
    index->primaryKey = key;
    index->offSet = offSet;
    return index;
}

unsigned int get_key(INDEXFILE *index) {
    return index->primaryKey;
}

boolean writeIndex(FILE *dataFile, INDEXFILE *index) {
}

unsigned int search(INDEXFILE *index, unsigned int key) {
}
