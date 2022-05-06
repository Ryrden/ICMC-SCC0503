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

unsigned int get_offset(INDEXFILE *index){
    return index->offSet;
}

boolean writeIndexInFile(FILE *indexFile, INDEXFILE *index) {
    fseek(indexFile,0,SEEK_END);
    fwrite(index, sizeof(INDEXFILE), 1, indexFile);
    return TRUE;
}

unsigned int search(INDEXFILE *index, unsigned int key) {
}
