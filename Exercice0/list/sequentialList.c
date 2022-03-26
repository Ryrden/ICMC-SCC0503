#include "./list.h"
#include "../uspDatabase/uspDatabase.h"
#include <malloc.h>

struct list_st {
    void *values[MAX_SIZE];
    int start;
    int end;
};

static boolean validPosition(const LIST *list, int pos);

static void moveDataRight(LIST *list, int pos);

static void listRemoveAll(LIST *list);

LIST *createList() {
    LIST *list = (LIST*)malloc(sizeof(LIST));
    if (list != NULL) {
        list->start = START;
        list->end = list->start;
    }
    return list;
}

boolean listInsert(LIST *list, void *item) {

    if ((list != NULL) && !listFull(list)) {
        (list->values[list->end]) = item;
        list->end++;
        return TRUE;
    }
    return FALSE;
}

boolean listFull(const LIST *list) {
    return list->end >= MAX_SIZE;
}
boolean listEmpty(const LIST *list) {
    return list->end == START;
}

boolean listInsertPosition(LIST *list, int position, void *item) {
    if (!listFull(list) && validPosition(list, position)) {
        moveDataRight(list, position);
        list->values[position] = item;
        list->end++;
        return TRUE;
    }
    return FALSE;
}

void *sequentialSearch(const LIST *list, int key) {
    for (int i = 0; i < list->end; i++) {
        if (getKey(list->values[i]) == key) {
            return list->values[i];
        }
    }
    return NULL;
}

void *OrdeneredSearch(const LIST *list, int key) {
    for (int i = 0; i < list->end; i++) {
        if (getKey(list->values[i]) == key) {
            return (list->values[i]);
        } else if (getKey(list->values[i]) > key) {
            return NULL; // retorna erro – não está na values – elemento > key
        }
    }
    return NULL; // retorna erro – não está na values - percorreu toda a values
}

static boolean validPosition(const LIST *list, int pos) {
    return pos < list->end;
}

static void moveDataRight(LIST *list, int pos) {
    for (int i = (list->end - 1); i >= pos; i--) {
        list->values[i + 1] = list->values[i];
    }
}

boolean listErase(LIST **list) {
    if ((*list != NULL) && (!listEmpty(*list))) {
        listRemoveAll(*list);
        free(*list);
        *list = NULL;
        return TRUE;
    }
    return FALSE;
}

static void listRemoveAll(LIST *list) {
    for (int i = 0; i < list->end; ++i) {
        item_apagar(&list->values[i]);
        list->values[i] = NULL;
    }
    list->end = START;
}


void printList(const LIST *list){
    
}