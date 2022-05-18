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

btPage *readPageFromFile(FILE *fp);
Errors writePageIntoFile(long rrn, btPage *page, FILE *fp);
btPage *getPage(long RRN, FILE *fp);
long getTreeHeader(FILE *fp);
void writeTreeHeader(FILE *fp, long rootRRN);
btPage *createTree(FILE *fp);
btPage *getOrCreateRoot(FILE *fp);
promotedKey *insertIntoNode(btPage *page, promotedKey *newKey, FILE *fp);
btPage *searchPositionOnPageAndInsert(btPage *page, promotedKey *newKey);
btPage *splitAndCreateNewNode(btPage **page);
promotedKey *extractpromotedKey(btPage *page);
promotedKey *_split(btPage *page, FILE *fp, promotedKey *newKey);
btPage *createNodeWithPromotedKey(promotedKey *promoKey);
Errors setNodeAsRoot(btPage *page, FILE *fp);
promotedKey *_bTreeInsert(btPage *node, promotedKey *key, FILE *fp);
Errors bTreeInsert(PrimaryIndex *newRecord, btPage *root, FILE *fp);
long bTreeSelect(btPage *node, int key, FILE *fp);
#endif // BTREE_H
