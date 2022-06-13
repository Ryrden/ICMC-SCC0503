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
    long pageRRN; // É necessário? (como vamos ter acesso ao rrn se precisamos ler primeiro?)
    // Como funciona o sistema de Espaço Livre??
};

struct promotedKey_st {
    int key;
    long recordRRN;
    long childs[2];
};

struct header_st { // store metadata about bTree
    unsigned int numberOfPages;
    unsigned int rootRRN;
};

static long getKey(BTPAGE *page) {
    return page->items->key;
}

HEADER *getTreeHeader(FILE *file) {
    HEADER *header = (HEADER *)malloc(sizeof(HEADER));

    rewind(file);
    unsigned int rootRRN;
    unsigned int numberOfPages;
    fread(&rootRRN, sizeof(long), 1, file);
    fread(&numberOfPages, sizeof(long), 1, file);
    if (!rootRRN || !numberOfPages)
        return NULL;

    if (header != NULL) {
        header->numberOfPages = numberOfPages;
        header->rootRRN = rootRRN;
    }
    return header;
}

/*Writes root RRN in header*/
boolean writeTreeHeader(FILE *file, unsigned int rootRRN, unsigned int numberOfPages) {
    // Calcula espaço livre e escreve no cabeçalho da árvore, junto com o RRN do nó raíz
    if (!file)
        return FALSE;

    fwrite(&rootRRN, sizeof(unsigned int), 1, file);
    fwrite(&numberOfPages, sizeof(unsigned int), 1, file);
    return TRUE;
}

PROMOTEDKEY *createPromotedKey(RECORD *record, long *childs) {
				printf(" key: %i, RRN: %li\n", record->key, record->recordRRN);
    PROMOTEDKEY *promo =(PROMOTEDKEY *) malloc(2 * sizeof(PROMOTEDKEY));
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

HEADER *createHeader() {
    HEADER *header = (HEADER *)calloc(1, sizeof(HEADER));
    header->numberOfPages = 0;
    header->rootRRN = 0;
    return header;
}

BTPAGE *createTree(FILE *file, HEADER *header) {
    // Aloca espaço pra raiz
    BTPAGE *page = (BTPAGE *)malloc(1 * PAGESIZE);
    page->items = (RECORD *)calloc(MAXKEYS, sizeof(RECORD));

				// TO DO: refatorar usando memset
				// mais clean e legivel

    // Inicializa items com valor nulo
    for (int i = 0; i < MAXKEYS; i++) {
        page->items[i].key = -1;
        page->items[i].recordRRN = -1;
    }

    page->childs = (long *)calloc(MAXKEYS + 1, sizeof(long));

    // Inicializa childs com valor nulo
    for (int i = 0; i < MAXKEYS + 1; i++) {
        page->childs[i] = -1;
    }

    page->numberOfKeys = 0;
    page->isLeaf = TRUE;
    page->pageRRN = header->numberOfPages;

    header->numberOfPages++;

    fwrite(page, PAGESIZE, 1, file);
    return page;
}

BTPAGE *changeRootIfNeeded(BTPAGE *root, HEADER *header, FILE *file){
				if(root->pageRRN == header->rootRRN){
								return root;
				}

				BTPAGE *oldRoot = root;

				root = readPageFromFile(file, header->rootRRN);
				return root;
}

RECORD *createRecord(int key, long recordRRN) {
    RECORD *item = (RECORD *)malloc(1 * sizeof(RECORD));
    item->key = key;
    item->recordRRN = recordRRN;
    return item;
}

BTPAGE *getOrCreateRoot(FILE *file) {
    // Verifica se a árvore já existe ou precisa criar uma nova
    HEADER *treeHeader = getTreeHeader(file);
    // Se a roote não existir, cria ela

    if (!treeHeader) {
        perror("bTree doesn't exists"); // apagar dps
        treeHeader = createHeader();
        return createTree(file, treeHeader);
    }
    // Se existir, só pega o RRN da raiz no cabeçalho e carrega sua página
    unsigned int rootRRN = treeHeader->rootRRN;
    return getPage(rootRRN, file);
    // Pode ser adaptada pra inserção e busca sem precisar de 2 funções
}

/*Get page by rrn*/
BTPAGE *getPage(long RRN, FILE *file) {
    if (!file)
        return NULL;
    // Recupera uma página baseado no RRN
    fseek(file, RRN * PAGESIZE, SEEK_SET);
    BTPAGE *page = readPageFromFile(file, RRN);
    page->pageRRN = RRN;

    return page;
}

/*Retrives page from file pointer*/
BTPAGE *readPageFromFile(FILE *file, long RRN) {
    // Coloca o ponteiro do arquivo no local correto
    fseek(file, RRN * PAGESIZE, SEEK_SET);

    // Aloca espaço para carregar página
    BTPAGE *page = (BTPAGE *)malloc(1 * sizeof(BTPAGE));

    // Lê dados da página do arquivo
				fread(page, sizeof(BTPAGE), 1, file);

    return page;
}

// Writes page into file in certain rrn position
boolean writePageIntoFile(long RRN, BTPAGE *page, FILE *file) {
    // Verifica se está tudo ok com os dados
    if (!file) {
        perror("File doesn't exists");
        return FALSE;
    }
    if (!page) {
        perror("Page doesn't exists");
        return FALSE;
    }
    // Encontra local para escrita baseado no RRN
    fseek(file, RRN * PAGESIZE, SEEK_SET);
    // Escreve dados
				fwrite(page, PAGESIZE, 1, file);
   
				// TO-DO: Escrever espaço Livre

    fflush(file);
    return TRUE;
    // Dica: você pode criar uma função que só lida com a escrita dos dados e chamar aqui
}

// Função mais abstrata de inserção
boolean bTreeInsert(RECORD *newRecord, BTPAGE *root, HEADER *header, FILE *file) {
    if (!root)
        return FALSE;

    // Prepara os dados da nova chave
    PROMOTEDKEY *promotedKey = createPromotedKey(newRecord, NULL);

    // Tenta inserir recursivamente
    promotedKey = _bTreeInsert(root, promotedKey, header, file);

    // Se tiver chave promovida no final da recursão, devemos criar nova raiz 
    if (promotedKey) {
        BTPAGE *newRoot = createNodeWithPromotedKey(promotedKey, header);
								
								writePageIntoFile(newRoot->pageRRN, newRoot, file);

        // atualiza o cabeçalho
								header->rootRRN = newRoot->pageRRN;
    }

				free(promotedKey);

    return TRUE;
}

BTPAGE *createNodeWithPromotedKey(PROMOTEDKEY *promoKey, HEADER *header) {
    // Se promoção cria estrutura para nova raiz,
    // Aloca espaço para ela
				BTPAGE *newRoot = (BTPAGE *)malloc(1 * PAGESIZE);

				// aloca espaço e atualiza registros e childs
    newRoot->items = (RECORD *)calloc(MAXKEYS, sizeof(RECORD));
				memset(&newRoot->items[0], -1, MAXKEYS*sizeof(RECORD));

    newRoot->childs = (long *)calloc(MAXKEYS + 1, sizeof(long));
				memset(&newRoot->childs[0], -1, (MAXKEYS + 1)*sizeof(RECORD));

    // Salva dados da chave promovida na nova raiz
				searchPositionOnPageAndInsert(newRoot, promoKey);

				//atualiza meta dados
				newRoot->numberOfKeys = 1;
    newRoot->isLeaf = FALSE;
    newRoot->pageRRN = header->numberOfPages;

    header->numberOfPages++;

    return newRoot;

    // atualiza os filhos deste novo nó/página
    // Pode reusar função que cria página nova e adicionar somente especificidades
}

// Recursive insertion
PROMOTEDKEY *_bTreeInsert(BTPAGE *node, PROMOTEDKEY *key, HEADER *header, FILE *file) {
    // Caso 1: nó é folha tenta inserir retorna PROMOTEDKEY != NULL caso houver split
    if (node->isLeaf) {
        key = insertIntoNode(node, key, header, file);
        return key;
    }

    // Caso 2: nó não folha, procura proximo nó filho
    long child;
    for (int i = 0; i < node->numberOfKeys; i++) {
        if (node->items[i].key > key->key) {
            child = i;
            break;
        }
        child = i + 1;
    }

    BTPAGE *nextNode = readPageFromFile(file, child);
    key = _bTreeInsert(nextNode, key, header, file);


    // Caso 3: key != NULL, foi promovida e precisa ser inserida
    if (key) {
        key = insertIntoNode(node, key, header, file);
        return key;
    }

				freePage(nextNode);
    return key;
}

PROMOTEDKEY *insertIntoNode(BTPAGE *page, PROMOTEDKEY *newKey, HEADER *header, FILE *file) {
    // Procura local pra inserir nova chave na página
    page = searchPositionOnPageAndInsert(page, newKey);

    // Se lotar splita a pagina e retorna o promted key
    if (page->numberOfKeys == MAXKEYS) {
								free(newKey);
        return _split(page, header, file);
    }

    // Se não lotar escreve a pagina e retorna NULL
    writePageIntoFile(page->pageRRN, page, file);
    return NULL;
}

// Insert some key on page
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
				if(position > MAXKEYS){ // não deve chegar nesse ponto
								exit(EXIT_FAILURE);
				}

				// insere a nova chave e atualiza as outras
				memcpy(&page->items[position + 1], &page->items[position], (page->numberOfKeys - position)*sizeof(RECORD));
				page->items[position].key = key->key;
				page->items[position].recordRRN = key->recordRRN;
				
				// insere os novos childs e atualiza os outros
				memcpy(&page->childs[position + 1], &page->childs[position], (page->numberOfKeys - position + 1) * sizeof(long));
				page->childs[position] = key->childs[0];
				page->childs[position + 1] = key->childs[1];


				page->numberOfKeys++;
    return page;
}


// Split node and writes into file
PROMOTEDKEY *_split(BTPAGE *originalPage, HEADER *header, FILE *file) {
    //cria o novo nó
				long middle = MAXKEYS/2;
				BTPAGE *newPage = createTree(file, header);

    // Extrai a chave promovida e atualiza os filhos da chave
				long childs[] = {originalPage->pageRRN, newPage->pageRRN};
				PROMOTEDKEY *promoKey = createPromotedKey(&originalPage->items[middle], childs); 
				promoKey->key = originalPage->items[middle].key;
				promoKey->recordRRN = originalPage->items[middle].recordRRN;
				promoKey->childs[0] = originalPage->pageRRN;
				promoKey->childs[1] = newPage->pageRRN;



				// Atualiza os valores das paginas
				memcpy(&newPage->items[0], &originalPage->items[middle + 1], (MAXKEYS - middle+1) * sizeof(RECORD));
				memset(&originalPage->items[middle], -1, (MAXKEYS - middle)*sizeof(RECORD));

				// Atualiza meta-dados das paginas 
				originalPage->numberOfKeys = middle;
				originalPage->isLeaf = TRUE;
				newPage->numberOfKeys = (MAXKEYS - (middle+1));
				newPage->isLeaf = TRUE;

    // Escreve a página nova e a que foi dividida (com suas atualizações) no arquivo
				writePageIntoFile(newPage->pageRRN, newPage, file);
				writePageIntoFile(originalPage->pageRRN, originalPage, file);

				freePage(originalPage);
				freePage(newPage);

				return promoKey;
}

void freePage(BTPAGE *page){
    free(page);
}


/* not implemented

//Returns rrn if key exist else return -1
long bTreeSelect(BTPAGE *node, int key, FILE *file) {
    // Procura no nó atual se a chave existe
    // Se não existir, tenta procurar no filho adequado, recursivamente
    // Se encontrar a chave, retorna RRN dela
    // Se não encontrar (chegar num nó folha e não estiver lá), retorna -1
}

//If page size is odd the return is biggest slice

BTPAGE *splitAndCreateNewNode(BTPAGE **page) {
    // Encontra a posição do meio das chaves
    // Cria espaço pra nova página
    // Copia metade das chaves pra página nova
    // Limpa elas do nó antigo
    // Atualiza os filhos de ambas as páginas
    // Atualiza o número de chaves de ambas
}

//Extract a promoted key from page
PROMOTEDKEY *extractpromotedKey(BTPAGE *page) {
    // Aloca espaço pra chave
    // Tira ela da página
    // Atualiza dados da página (filho, número de chaves, etc)
}



//Used if promotions reaches root
boolean setNodeAsRoot(BTPAGE *page, FILE *file, HEADER *header) {
				header->rootRRN = page->pageRRN;
				return TRUE;
}




*/

void debugPrintAllPages(BTPAGE *page, FILE *file){
				printf("but WHYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY\n");
				debugPrintPage(page, FALSE);

				for(int i=0; i< MAXKEYS +1; i++){
								if (page->childs[i] != -1){
												BTPAGE *nextPage = readPageFromFile(file, page->childs[i]);
												debugPrintPage(nextPage, FALSE);
								}

				}
}

void debugPrintPage(BTPAGE *page, boolean printChilds){
				
				printf("page:%ld\n keys:", page->pageRRN);

				for (int i=0; i<MAXKEYS; i++){
							long key = page->items[i].key;	
							if (key != -1) {
											printf("|%li", key);
							}
							else{
												printf("| ");
								}
				}
				printf("\nchilds:\n ");
				if(printChilds){
								for (int i=0; i<MAXKEYS+1; i++){
											if (page->childs[i] != -1) {
															printf("|%li", page->childs[i]);
											}
											else{
																printf("| ");
												}
								}
				}
				printf("\n");
}
