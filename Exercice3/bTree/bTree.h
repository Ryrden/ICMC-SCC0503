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
#define FREE_SPACE_ON_PAGE (PAGESIZE - ((MAXKEYS * 4) + (MAXKEYS * 8) + ((MAXKEYS + 1) * 8) + 3))

typedef struct record_st RECORD;
typedef struct page_st BTPAGE;
typedef struct promotedKey_st PROMOTEDKEY;
//typedef struct primaryIndex PrimaryIndex;

static long getKey(BTPAGE *page);

BTPAGE *createTree(FILE *);
BTPAGE *createPage(RECORD *, long *, boolean, int);
PROMOTEDKEY *createPromotedKey(int, long, long *);
RECORD *createRecord(int, long);

BTPAGE *getPage(long, FILE *);
BTPAGE *readPageFromFile(FILE *);
boolean writePageIntoFile(long, BTPAGE *, FILE *);

static long getTreeHeader(FILE *);
static void writeTreeHeader(FILE *, long);

BTPAGE *getOrCreateRoot(FILE *);

PROMOTEDKEY *insertIntoNode(BTPAGE *, PROMOTEDKEY *, FILE *);
BTPAGE *searchPositionOnPageAndInsert(BTPAGE *, PROMOTEDKEY *);
BTPAGE *splitAndCreateNewNode(BTPAGE **);
PROMOTEDKEY *extractpromotedKey(BTPAGE *);
PROMOTEDKEY *_split(BTPAGE *, FILE *, PROMOTEDKEY *);
BTPAGE *createNodeWithPromotedKey(PROMOTEDKEY *);
boolean setNodeAsRoot(BTPAGE *, FILE *);

PROMOTEDKEY *_bTreeInsert(BTPAGE *, PROMOTEDKEY *, FILE *);
boolean bTreeInsert(RECORD *, BTPAGE *, FILE *);

long bTreeSelect(BTPAGE *, int, FILE *);

#endif // BTREE_H
