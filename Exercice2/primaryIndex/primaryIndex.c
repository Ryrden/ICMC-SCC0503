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

void eraseIndexData(INDEXFILE **indexData) {
    free(*indexData);
    (*indexData) = NULL;
}

unsigned int get_key(INDEXFILE *index) {
    return index->primaryKey;
}

unsigned int get_offset(INDEXFILE *index) {
    return index->offSet;
}

unsigned int set_key(INDEXFILE *index, unsigned int key) {
    return index->primaryKey = key;
}

unsigned int set_offset(INDEXFILE *index, unsigned int offset) {
    return index->offSet = offset;
}

boolean writeIndexInFile(FILE *indexFile, INDEXFILE *index) {
    fseek(indexFile, 0, SEEK_END);
    fwrite(index, sizeof(INDEXFILE), 1, indexFile);
    return TRUE;
}

INDEXFILE *search(FILE *indexFile, unsigned int key) {
    INDEXFILE *registerIndex = (INDEXFILE *) malloc(sizeof(INDEXFILE));
    rewind(indexFile);
    while (!feof(indexFile)) {
        fread(registerIndex, sizeof(INDEXFILE), 1, indexFile);
        if (get_key(registerIndex) == key)
            return registerIndex;
    }
    free(registerIndex);
    return NULL;
}

void deleteIndexInFile(FILE *indexFile, unsigned int key) {
    long dataSize = getDataSize(indexFile, sizeof(INDEXFILE));
    if (dataSize <= DATA_TO_DELETE) {
        indexFile = freopen("indexfile.bin", "wb+", indexFile);
        verifyNullPointerExceptionToFile(indexFile);
        return;
    }

    INDEXFILE **indexData = (INDEXFILE **)malloc(sizeof(INDEXFILE) * dataSize - 1);

    INDEXFILE *registerIndex = (INDEXFILE *)malloc(sizeof(INDEXFILE));

    rewind(indexFile);
    int index = 0;
    while (index < dataSize - DATA_TO_DELETE) {
        fread(registerIndex, sizeof(INDEXFILE), 1, indexFile);
        if (registerIndex) {
            if (get_key(registerIndex) != key) {
                INDEXFILE *newRegisterIndex = (INDEXFILE *)malloc(sizeof(INDEXFILE));
                set_key(newRegisterIndex, get_key(registerIndex));
                set_offset(newRegisterIndex, get_offset(registerIndex));
                indexData[index] = newRegisterIndex;
                index++;
            }
        } else
            break;
    }

    indexFile = freopen("indexfile.bin", "wb+", indexFile);

    if (indexFile == NULL) {
        perror("Error to open Archive");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dataSize - DATA_TO_DELETE; i++) {
        writeIndexInFile(indexFile, indexData[i]);
        eraseIndexData(&indexData[i]);
    }
    free(indexData);
    eraseIndexData(&registerIndex);
}
