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

unsigned int get_offset(INDEXFILE *index) {
    return index->offSet;
}

boolean writeIndexInFile(FILE *indexFile, INDEXFILE *index) {
    fseek(indexFile, 0, SEEK_END);
    fwrite(index, sizeof(INDEXFILE), 1, indexFile);
    return TRUE;
}

INDEXFILE *search(FILE *indexFile, unsigned int key) {
    INDEXFILE *registerIndex = malloc(sizeof(INDEXFILE));
    rewind(indexFile);
    while (!feof(indexFile)) {
        fread(registerIndex, sizeof(INDEXFILE), 1, indexFile);
        if (get_key(registerIndex) == key)
            return registerIndex;
    }
    return NULL;
}

void deleteIndexInFile (FILE *indexFile, unsigned int key) {

    long dataSize = getDataSize(indexFile, sizeof(INDEXFILE));

    INDEXFILE **indexData = (INDEXFILE **)malloc(sizeof(INDEXFILE) * dataSize - 1);

    INDEXFILE *registerIndex = (INDEXFILE*) malloc(sizeof(INDEXFILE));
    int i = 0;
    rewind(indexFile);
    while (!feof(indexFile)) {
        fread(registerIndex, sizeof(INDEXFILE), 1, indexFile);
        if (get_key(registerIndex) != key) {
            indexData[i] = registerIndex;
            i++;
        }
    }
    indexFile = fopen("indexfile.bin", "wb+");

    for (int i = 0; i < dataSize - 1; i++) {
        writeIndexInFile(indexFile, indexData[i]);
    }
    free(registerIndex);
    free(indexData);
}
