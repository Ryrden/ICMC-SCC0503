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

typedef struct record_st RECORD;
typedef struct page_st BTPAGE;
typedef struct promotedKey_st PROMOTEDKEY;
typedef struct header_st HEADER;

BTPAGE *createTree(FILE *, HEADER *);
RECORD *createRecord(int, long);
HEADER *createHeader();
HEADER *getTreeHeader(FILE *);
boolean writeTreeHeader(HEADER *, FILE *);
static PROMOTEDKEY *createPromotedKey(RECORD *, long *);

static BTPAGE *readPageFromFile(FILE *, long);
static boolean writePageIntoFile(long, BTPAGE *, FILE *);
void freePage(BTPAGE *);

BTPAGE *getRoot(FILE *, HEADER *);

BTPAGE *changeRootIfNeeded(BTPAGE *, HEADER *, FILE *);
boolean bTreeInsert(RECORD *, BTPAGE *, HEADER *, FILE *);

long bTreeSearch(BTPAGE *, int, FILE *);
static long bTreeSelect(BTPAGE *, int, FILE *);

static PROMOTEDKEY *insertIntoPage(BTPAGE *, PROMOTEDKEY *, HEADER *, FILE *);
static BTPAGE *searchPositionOnPageAndInsert(BTPAGE *, PROMOTEDKEY *);
static BTPAGE *splitAndCreateNewPage(BTPAGE **);
static PROMOTEDKEY *extractPromotedKey(const BTPAGE *, const BTPAGE *, long);
static void updatePagesValuesAndMetadata(BTPAGE *, BTPAGE *, long);
static long findNextChild(BTPAGE *, int);
static PROMOTEDKEY *_split(BTPAGE *, HEADER *, FILE *);
static BTPAGE *createPageWithPromotedKey(PROMOTEDKEY *, HEADER *);
static BTPAGE *alocatePage();

static PROMOTEDKEY *_bTreeInsert(BTPAGE *, PROMOTEDKEY *, HEADER *, FILE *);

void debugPrintPage(BTPAGE *, boolean);
void debugPrintAllPages(BTPAGE *, FILE *);
#endif // BTREE_H
