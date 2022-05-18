#ifndef BTREE_H
#define BTREE_H

#include "../Util/util.h"
#include <btree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record_st RECORD;
typedef struct page_st BTPAGE;
typedef struct promotedKey_st PROMOTEDKEY;

BTPAGE *readPageFromFile(FILE *fp);
Errors writePageIntoFile(long rrn, BTPAGE *page, FILE *fp);
BTPAGE *getPage(long RRN, FILE *fp);
long getTreeHeader(FILE *fp);
void writeTreeHeader(FILE *fp, long rootRRN);
BTPAGE *createTree(FILE *fp);
BTPAGE *getOrCreateRoot(FILE *fp);
PROMOTEDKEY *insertIntoNode(BTPAGE *page, PROMOTEDKEY *newKey, FILE *fp);
BTPAGE *searchPositionOnPageAndInsert(BTPAGE *page, PROMOTEDKEY *newKey);
BTPAGE *splitAndCreateNewNode(BTPAGE **page);
PROMOTEDKEY *extractpromotedKey(BTPAGE *page);
PROMOTEDKEY *_split(BTPAGE *page, FILE *fp, PROMOTEDKEY *newKey);
BTPAGE *createNodeWithPromotedKey(PROMOTEDKEY *promoKey);
Errors setNodeAsRoot(BTPAGE *page, FILE *fp);
PROMOTEDKEY *_bTreeInsert(BTPAGE *node, PROMOTEDKEY *key, FILE *fp);
Errors bTreeInsert(PrimaryIndex *newRecord, BTPAGE *root, FILE *fp);
long bTreeSelect(BTPAGE *node, int key, FILE *fp);
#endif // BTREE_H
