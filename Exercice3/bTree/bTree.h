#ifndef BTREE_H
#define BTREE_H

#include "../Util/util.h"
#include <btree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGESIZE 4096
#define TREE_HEADER PAGESIZE
#define MAXKEYS 204
#define AUX_FIELDS_SIZE_ON_PAGE (2 + 1) //∗ number o f k e y s and ” i s l e a f ” b o o l ∗/
#define FREE_SPACE_ON_PAGE (PAGESIZE - ((MAXKEYS * 4) + (MAXKEYS * 8) + ((MAXKEYS + 1) * 8) + 3))

typedef struct record_st RECORD;
typedef struct page_st BTPAGE;
typedef struct promotedKey_st PROMOTEDKEY;

BTPAGE *readPageFromFile(FILE *file);
boolean writePageIntoFile(long rrn, BTPAGE *page, FILE *file);
BTPAGE *getPage(long RRN, FILE *file);
long getTreeHeader(FILE *file);
void writeTreeHeader(FILE *file, long rootRRN);
BTPAGE *createTree(FILE *file);
BTPAGE *getOrCreateRoot(FILE *file);
PROMOTEDKEY *insertIntoNode(BTPAGE *page, PROMOTEDKEY *newKey, FILE *file);
BTPAGE *searchPositionOnPageAndInsert(BTPAGE *page, PROMOTEDKEY *newKey);
BTPAGE *splitAndCreateNewNode(BTPAGE **page);
PROMOTEDKEY *extractpromotedKey(BTPAGE *page);
PROMOTEDKEY *_split(BTPAGE *page, FILE *file, PROMOTEDKEY *newKey);
BTPAGE *createNodeWithPromotedKey(PROMOTEDKEY *promoKey);
boolean setNodeAsRoot(BTPAGE *page, FILE *file);
PROMOTEDKEY *_bTreeInsert(BTPAGE *node, PROMOTEDKEY *key, FILE *file);
boolean bTreeInsert(PrimaryIndex *newRecord, BTPAGE *root, FILE *file);
long bTreeSelect(BTPAGE *node, int key, FILE *file);

#endif // BTREE_H
