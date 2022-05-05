#ifndef PRIMARYINDEX_H
#define PRIMARYINDEX_H

typedef struct indexFile_st INDEXFILE;

INDEXFILE **getIndex(FILE*, FILEHEADER*);
int writeIndex(FILE *, INDEXFILE**, FILEHEADER*);
void sortIndex(INDEXFILE**, FILEHEADER*);

#endif // PRIMARYINDEX_H