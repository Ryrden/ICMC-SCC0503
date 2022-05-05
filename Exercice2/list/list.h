#ifndef LIST_H
#define LIST_H

#include "../Util/util.h"
#include "../primaryIndex/primaryIndex.h"
#define ERRO_LIST (-300)

typedef struct list LIST;

LIST *create_list();
int list_insert(LIST *, INDEFILE *);
boolean list_erase(LIST **);
boolean list_remove(LIST *);
boolean list_remover_item(LIST *, int);
long list_size(const LIST *);
boolean list_empty(const LIST *);
boolean list_full(const LIST *);
INDEFILE *sequential_search(const LIST *, unsigned int);
void print_list(const LIST *, int, int);

#endif // LIST_H
