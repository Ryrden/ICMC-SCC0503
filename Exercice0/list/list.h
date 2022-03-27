#ifndef LIST_H
#define LIST_H

#include "../Util/util.h"
#define MAX_SIZE 100
#define START 0
#define ERRO_LIST (-300)

typedef struct list_st LIST;

LIST *createList();
int listInsert(LIST *list, void *item);
boolean listErase(LIST **list);
boolean listRemove(LIST *list);
boolean listRemoverItem(LIST *list, int key);
int listSize(const LIST *list);
boolean listEmpty(const LIST *list);
boolean listFull(const LIST *list);
void *sequentialSearch(const LIST *list, int key);
void printList(const LIST *list,int start, int end);

#endif //LIST_H
