#include "bTree.h"
/*
Adaptado do código de:
Henrique Gomes Zanin NUSP: 10441321
Gabriel Guimaraes Vilas Boas Marin NUSP: 11218521
*/

struct record_st {
    int key;
    long recordRRN;
};

struct page_st {
    RECORD *items;
    long *childs;
    short numberOfKeys;
    boolean isLeaf;
    long pageRRN;
};

struct promotedKey_st {
    int key;
    long recordRRN;
    long childs[2];
};

// Armazena metadados da arvore, deve ser escrito no fim do arquivo
struct header_st {
    unsigned int numberOfPages;
    unsigned int rootRRN;
};

HEADER *createHeader() {
    HEADER *header = (HEADER *)calloc(1, sizeof(HEADER));
    header->numberOfPages = 0;
    header->rootRRN = 0;
    return header;
}

boolean writeTreeHeader(HEADER *header, FILE *file) {
    if (!file)
        return FALSE;

    fseek(file, (header->numberOfPages + 1) * PAGESIZE, SEEK_SET);

    fwrite(&header->rootRRN, sizeof(unsigned int), 1, file);
    fwrite(&header->numberOfPages, sizeof(unsigned int), 1, file);

    char *freeSpace = (char *)malloc(PAGESIZE - sizeof(HEADER));
    fwrite(freeSpace, sizeof(char), PAGESIZE - sizeof(HEADER), file);

    fflush(file);
    free(freeSpace);
    return TRUE;
}

HEADER *getTreeHeader(FILE *file) {
    HEADER *header = (HEADER *)malloc(sizeof(HEADER));

    fseek(file, -PAGESIZE, SEEK_END);

    fread(&header->rootRRN, sizeof(unsigned int), 1, file);
    fread(&header->numberOfPages, sizeof(unsigned int), 1, file);

    return header;
}

PROMOTEDKEY *createPromotedKey(RECORD *record, long *childs) {
    PROMOTEDKEY *promo = (PROMOTEDKEY *)malloc(1 * sizeof(PROMOTEDKEY));
    promo->key = record->key;
    promo->recordRRN = record->recordRRN;

    if (childs != NULL) {
        promo->childs[0] = childs[0];
        promo->childs[1] = childs[1];
    } else {
        promo->childs[0] = -1;
        promo->childs[1] = -1;
    }
    return promo;
}

BTPAGE *createTree(FILE *file, HEADER *header) {
    // Aloca espaço pra raiz
    BTPAGE *page = alocatePage();

    page->isLeaf = TRUE;
    page->pageRRN = header->numberOfPages;

    header->numberOfPages++;

    fwrite(page, PAGESIZE, 1, file);
    return page;
}

BTPAGE *alocatePage() {
    BTPAGE *page = (BTPAGE *)malloc(1 * PAGESIZE);
    page->items = (RECORD *)calloc(MAXKEYS, sizeof(RECORD));
    page->childs = (long *)calloc(MAXKEYS + 1, sizeof(long));
    page->isLeaf = TRUE;

    // Inicializa items com valor nulo
    memset(page->items, -1, MAXKEYS * sizeof(long));

    // Inicializa childs com valor nulo
    memset(page->childs, -1, (MAXKEYS + 1) * sizeof(long));

    page->numberOfKeys = 0;
    return page;
}

BTPAGE *changeRootIfNeeded(BTPAGE *root, HEADER *header, FILE *file) {
    if (header->rootRRN == root->pageRRN) {
        return root;
    }

    freePage(root);
    return readPageFromFile(file, header->rootRRN);
}

RECORD *createRecord(int key, long recordRRN) {
    RECORD *item = (RECORD *)malloc(1 * sizeof(RECORD));
    item->key = key;
    item->recordRRN = recordRRN;
    return item;
}

BTPAGE *getRoot(FILE *file, HEADER *header) {
    return readPageFromFile(file, header->rootRRN);
}

BTPAGE *readPageFromFile(FILE *file, long RRN) {
    BTPAGE *page = alocatePage();

    fseek(file, RRN * PAGESIZE, SEEK_SET);

    // Lê dados da página do arquivo
    for (int i = 0; i < MAXKEYS; i++)
        fread(&page->items[i].key, sizeof(int), 1, file);

    for (int i = 0; i < MAXKEYS; i++)
        fread(&page->items[i].recordRRN, sizeof(long), 1, file);

    fread(page->childs, sizeof(long), MAXKEYS + 1, file);
    fread(&page->isLeaf, sizeof(int), 1, file);
    fread(&page->numberOfKeys, sizeof(short), 1, file);

    page->pageRRN = RRN;

    return page;
}

boolean writePageIntoFile(long RRN, BTPAGE *page, FILE *file) {
    if (!file) {
        perror("File doesn't exists");
        return FALSE;
    }
    if (!page) {
        perror("Page doesn't exists");
        return FALSE;
    }
    fseek(file, RRN * PAGESIZE, SEEK_SET);

    for (int i = 0; i < MAXKEYS; i++) {
        fwrite(&page->items[i].key, sizeof(int), 1, file);
    }
    for (int i = 0; i < MAXKEYS; i++) {
        fwrite(&page->items[i].recordRRN, sizeof(long), 1, file);
    }
    fwrite(page->childs, sizeof(long), MAXKEYS + 1, file);
    fwrite(&page->isLeaf, sizeof(int), 1, file);
    fwrite(&page->numberOfKeys, sizeof(short), 1, file);

    // Aloca e Escreve o espaço livre
    char *freeSpace = (char *)malloc(FREE_SPACE * sizeof(char));
    fwrite(freeSpace, sizeof(char), FREE_SPACE, file);

    free(freeSpace);

    fflush(file);
    return TRUE;
}

boolean bTreeInsert(RECORD *newRecord, BTPAGE *root, HEADER *header, FILE *file) {
    if (!root)
        return FALSE;

    PROMOTEDKEY *promotedKey = createPromotedKey(newRecord, NULL);

    promotedKey = _bTreeInsert(root, promotedKey, header, file);

    if (promotedKey) {
        BTPAGE *newRoot = createPageWithPromotedKey(promotedKey, header);

        writePageIntoFile(newRoot->pageRRN, newRoot, file);

        header->rootRRN = newRoot->pageRRN;

        freePage(newRoot);
        newRoot = NULL;
        free(promotedKey);
        promotedKey = NULL;
    }

    return TRUE;
}

BTPAGE *createPageWithPromotedKey(PROMOTEDKEY *promoKey, HEADER *header) {
    BTPAGE *newRoot = alocatePage();

    searchPositionOnPageAndInsert(newRoot, promoKey);

    newRoot->numberOfKeys = 1;
    newRoot->isLeaf = FALSE;

    newRoot->pageRRN = header->numberOfPages;
    header->numberOfPages++;

    return newRoot;
}

PROMOTEDKEY *_bTreeInsert(BTPAGE *page, PROMOTEDKEY *key, HEADER *header, FILE *file) {
    // confere se o registro é repetido
    for (int i = 0; i < page->numberOfKeys; i++) {
        if (page->items[i].key == key->key) {
            printf("O Registro ja existe!\n");
            free(key);
            return NULL;
        }
    }

    // Caso 1: nó é folha tenta inserir
    if (page->isLeaf) {
        key = insertIntoPage(page, key, header, file);
        return key;
    }

    // Caso 2: nó não folha, procura proximo nó filho
    long child;
    for (int i = 0; i < page->numberOfKeys; i++) {
        if (page->items[i].key > key->key) {
            child = i;
            break;
        }
        child = i + 1;
    }

    BTPAGE *nextPage = readPageFromFile(file, page->childs[child]);
    key = _bTreeInsert(nextPage, key, header, file);
    freePage(nextPage);
    nextPage = NULL;

    // Caso 3: key != NULL, foi promovida e precisa ser inserida no nó atual
    if (key) {
        key = insertIntoPage(page, key, header, file);
        return key;
    }

    return key;
}

PROMOTEDKEY *insertIntoPage(BTPAGE *page, PROMOTEDKEY *newKey, HEADER *header, FILE *file) {
    page = searchPositionOnPageAndInsert(page, newKey);
    free(newKey);
    newKey = NULL;

    // Se lotar depois de inserir splita a pagina e retorna o promted key
    if (page->numberOfKeys == MAXKEYS) {
        return _split(page, header, file);
    }

    // Se não lotar escreve a pagina e retorna NULL
    writePageIntoFile(page->pageRRN, page, file);
    return NULL;
}

BTPAGE *searchPositionOnPageAndInsert(BTPAGE *page, PROMOTEDKEY *key) {
    // Encontra a posição para inserir a chave
    long position = 0;
    for (int i = 0; i < page->numberOfKeys; i++) {
        if (page->items[i].key > key->key) {
            position = i;
            break;
        }
        position = i + 1;
    }
    if (position > MAXKEYS | page->numberOfKeys >= MAXKEYS) {
        perror("posição invalida ou pagina cheia\n");
    }

    // insere a nova chave e atualiza as outras
    memcpy(&page->items[position + 1], &page->items[position], (page->numberOfKeys - position) * sizeof(RECORD));
    page->items[position].key = key->key;
    page->items[position].recordRRN = key->recordRRN;

    // insere os novos childs e atualiza os outros
    if (key->childs[0] != -1 | key->childs[1] != -1) {
        memcpy(&page->childs[position + 1], &page->childs[position], ((page->numberOfKeys - position) + 1) * sizeof(long));
        page->childs[position] = key->childs[0];
        page->childs[position + 1] = key->childs[1];
    }

    page->numberOfKeys++;
    return page;
}

static PROMOTEDKEY *extractPromotedKey(const BTPAGE *originalPage, const BTPAGE *newPage, long middle) {
    long childs[] = {originalPage->pageRRN, newPage->pageRRN};
    PROMOTEDKEY *promoKey = createPromotedKey(&originalPage->items[middle], childs);
    promoKey->key = originalPage->items[middle].key;
    promoKey->recordRRN = originalPage->items[middle].recordRRN;
    promoKey->childs[0] = originalPage->pageRRN;
    promoKey->childs[1] = newPage->pageRRN;

    return promoKey;
}

static void updatePagesValuesAndMetadata(BTPAGE *originalPage, BTPAGE *newPage, long middle) {
    // Atualiza os valores das paginas
    memcpy(newPage->items, &originalPage->items[middle + 1], (originalPage->numberOfKeys - (middle + 1)) * sizeof(RECORD));
    memset(&originalPage->items[middle], -1, (originalPage->numberOfKeys - middle) * sizeof(RECORD));
    memcpy(&newPage->childs[0], &originalPage->childs[middle + 1], (MAXKEYS - middle) * sizeof(long));
    memset(&originalPage->childs[middle + 1], -1, (MAXKEYS - middle) * sizeof(long));

    // Atualiza meta-dados das paginas
    originalPage->numberOfKeys = middle;
    newPage->numberOfKeys = (MAXKEYS - (middle + 1));
    newPage->isLeaf = originalPage->isLeaf;
}

PROMOTEDKEY *_split(BTPAGE *originalPage, HEADER *header, FILE *file) {
    // cria o novo nó
    long middle = MAXKEYS / 2;
    BTPAGE *newPage = alocatePage();
    newPage->pageRRN = header->numberOfPages;
    header->numberOfPages++;

    // Extrai a chave promovida e atualiza os filhos da chave
    PROMOTEDKEY *promoKey = extractPromotedKey(originalPage, newPage, middle);

    // Atualiza os valores e meta-dados das paginas
    updatePagesValuesAndMetadata(originalPage, newPage, middle);

    // Escreve a página nova e a que foi dividida (com suas atualizações) no arquivo
    writePageIntoFile(newPage->pageRRN, newPage, file);
    writePageIntoFile(originalPage->pageRRN, originalPage, file);

    // Libera memoria
    freePage(newPage);
    newPage = NULL;

    return promoKey;
}

long bTreeSelect(BTPAGE *page, int key, FILE *file) {
    for (int i = 0; i < page->numberOfKeys; i++) {
        if (page->items[i].key == key) {
            return page->items[i].recordRRN;
        }
    }

    long child;
    for (int i = 0; i < page->numberOfKeys; i++) {
        if (page->items[i].key > key) {
            child = i;
            break;
        }
        child = i + 1;
    }

    if (page->childs[child] != -1) {
        BTPAGE *nextPage = readPageFromFile(file, page->childs[child]);
        long RRN = bTreeSelect(nextPage, key, file);
        freePage(nextPage);
        nextPage = NULL;
        return RRN;
    }

    return -1;
}

void freePage(BTPAGE *page) {
    free(page->items);
    free(page->childs);
    free(page);
}