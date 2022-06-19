#ifndef BTREE_H
#define BTREE_H

#include "../Util/util.h"
#include "../uspDatabase/uspDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGESIZE 4096
#define TREE_HEADER PAGESIZE
#define MAXKEYS 204
#define AUX_FIELDS_SIZE_ON_PAGE (2 + 1) //∗ number o f k e y s and ” i s l e a f ” b o o l ∗/
#define FREE_SPACE (PAGESIZE - ((MAXKEYS * 4) + (MAXKEYS * 8) + ((MAXKEYS + 1) * 8) + 6))
// tamanho da pagina - tamanho ocupado
// FREE_SPACE serve para ocupar o arquivo (mesmo que com dados inuteis) para n atingir EOF durante a leitura

typedef struct record_st RECORD;
typedef struct page_st BTPAGE;
typedef struct promotedKey_st PROMOTEDKEY;
typedef struct header_st HEADER;

BTPAGE *createTree(FILE *, HEADER *);
BTPAGE *createPage(RECORD *, long *, boolean, int);
PROMOTEDKEY *createPromotedKey(RECORD *, long *);
RECORD *createRecord(int, long);
HEADER *createHeader();
HEADER *getTreeHeader(FILE *);
boolean writeTreeHeader(FILE *, unsigned int, unsigned int);

BTPAGE *getPage(long, FILE *);
BTPAGE *readPageFromFile(FILE *, long);
boolean writePageIntoFile(long, BTPAGE *, FILE *);
void freePage(BTPAGE *);

BTPAGE *getOrCreateRoot(FILE *);

PROMOTEDKEY *insertIntoPage(BTPAGE *, PROMOTEDKEY *, HEADER *, FILE *);
BTPAGE *searchPositionOnPageAndInsert(BTPAGE *, PROMOTEDKEY *);
BTPAGE *splitAndCreateNewPage(BTPAGE **);
PROMOTEDKEY *extractpromotedKey(BTPAGE *);
PROMOTEDKEY *_split(BTPAGE *, HEADER *, FILE *);
BTPAGE *createPageWithPromotedKey(PROMOTEDKEY *, HEADER *);
boolean setPageAsRoot(BTPAGE *, FILE *, HEADER *);
BTPAGE *changeRootIfNeeded(BTPAGE *, HEADER *, FILE *);
BTPAGE *alocatePage();

PROMOTEDKEY *_bTreeInsert(BTPAGE *, PROMOTEDKEY *, HEADER *, FILE *);
boolean bTreeInsert(RECORD *, BTPAGE *, HEADER *, FILE *);

long bTreeSelect(BTPAGE *, int, FILE *);

void debugPrintPage(BTPAGE *, boolean);
void debugPrintAllPages(BTPAGE *, FILE *);
#endif // BTREE_H
