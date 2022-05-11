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

INDEXFILE *search(FILE *indexFile, unsigned int key) {
    INDEXFILE *registerIndex = malloc(sizeof(INDEXFILE));
				rewind(indexFile);
				while(!feof(indexFile)){
        fread(registerIndex,sizeof(INDEXFILE),1,indexFile);
        if (get_key(registerIndex) == key)
            return registerIndex;
    }
    return NULL;
}
// fazer deleção 
/* unsigned int delete(FILE *indexFile, unsigned int key){
    long fileSize, structSize, dataSize;
    fseek(indexFile, 0, SEEK_END);
    fileSize = ftell(indexFile);
    fseek(indexFile, 0, SEEK_SET);
    structSize = sizeof(INDEXFILE);
    dataSize = (fileSize / structSize); // key on the struct

    INDEXFILE *indexData = (INDEXFILE*) malloc(sizeof(INDEXFILE)*dataSize-1);

    INDEXFILE *registerIndex;
    int i = 0;
    unsigned int offSet = 0;
    while(!feof(indexFile)){
        fread(registerIndex,sizeof(INDEXFILE),1,indexFile);
        if (get_key(registerIndex) != key){
            indexData[i] = registerIndex;
            i++;    
        }
        else {
            offSet = get_offset(registerIndex);
        }
    }
    indexFile = fopen("indexfile.bin", "wb+");
    
    for(int i = 0; i < dataSize-1; i++){
        writeIndexInFile(indexFile,indexData[i]);
    }
    
    return offSet;
} */
