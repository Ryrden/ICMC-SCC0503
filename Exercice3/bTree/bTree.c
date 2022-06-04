#include "bTree.h"
#include <stdio.h>
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

struct header_st { // store metadata about bTree
				unsigned int numberOfPages;
				unsigned int rootRRN;
};

/*
struct primaryIndex {
				unsigned int key; // probably nUSP of the student
				unsigned int offSet; // adress of the registry on the datafile 

};
*/

static long getKey(BTPAGE *page){
    return page->items->key;
}

/*Get root RRN from header*/
static long getTreeHeader(FILE *file) {
    // Carrega o cabeçalho da árvore, que está no início do arquivo
    rewind(file);
    long rrnHeader;
    fread(&rrnHeader, sizeof(long), 1, file);
    return rrnHeader;
}

/*Writes root RRN in header*/
static void writeTreeHeader(FILE *file, long rootRRN) {
    // Calcula espaço livre e escreve no cabeçalho da árvore, junto com o RRN do nó raíz
    fwrite(&rootRRN, sizeof(long), 1, file);
}

BTPAGE *createTree(FILE *file, HEADER *header) {
    // Aloca espaço pra raiz
    BTPAGE *page = (BTPAGE *) malloc(1*PAGESIZE);
    page->items = (RECORD *) calloc(MAXKEYS, sizeof(RECORD));

				// Inicializa items com valor nulo
				for(int i=0; i<MAXKEYS; i++){
								page->items[i].key = -1;
								page->items[i].recordRRN = -1;
				}

    page->childs = (long *) calloc(MAXKEYS + 1, sizeof(long));
				
				// Inicializa childs com valor nulo
				for(int i=0; i<MAXKEYS + 1; i++){
								page->childs[i] = -1;
				}

    page->numberOfKeys = 0;
    page->isLeaf = TRUE;
				page->pageRRN = header->numberOfPages;

				header->numberOfPages++;

    fwrite(page, PAGESIZE, 1, file);
    return page;
}

RECORD *createRecord(int key, long recordRRN) {
    RECORD *item = (RECORD *)malloc(1*sizeof(RECORD));
    item->key = key;
    item->recordRRN = recordRRN;
    return item;
}

/* função redundante, da pra usar apenas createTree
BTPAGE *createPage(RECORD *record, long *childs, boolean isLeaf, int numberOfKeys) {
    BTPAGE *page = (BTPAGE *) malloc(1*PAGESIZE);
    page->item = record;
    page->childs = childs;
    page->isLeaf = isLeaf;
    page->numberOfKeys = numberOfKeys;
    
    page->freeSpace = PAGESIZE;

    return page;
}
*/

PROMOTEDKEY *createPromotedKey(RECORD *record, long *childs) {
    PROMOTEDKEY *promo = (PROMOTEDKEY *)malloc(1*sizeof(PROMOTEDKEY));
    promo->key = record->key;
    promo->recordRRN = record->recordRRN;
				if(!childs){
								promo->childs[0] = childs[0];
								promo->childs[1] = childs[1];
				}
    return promo;
}

HEADER *createHeader(){
				HEADER *header = (HEADER *) calloc(1, sizeof(HEADER));
				header->numberOfPages = 0;
				header->rootRRN = 0;
				return header;
}

/*Retrives page from file pointer*/
BTPAGE *readPageFromFile(FILE *file) {
    // Aloca espaço para carregar página
    BTPAGE *page = (BTPAGE *)malloc(1*PAGESIZE);
    // Lê dados da página do arquivo
    fread(page, PAGESIZE, 1, file);

    return page;
}

/*Get page by rrn*/
BTPAGE *getPage(long RRN, FILE *file) {
    // Recupera uma página baseado no RRN
    BTPAGE *currentPage = readPageFromFile(file);

    if (currentPage == NULL)
        return currentPage;

    if (currentPage->items->recordRRN == RRN)
        return currentPage;

    // Procura e carrega seus dados
    long offSet = currentPage->items->recordRRN * PAGESIZE;

    fseek(file, offSet, SEEK_SET);

    return getPage(RRN, file);
}


/*Not fully implemented
	*
//Writes page into file in certain rrn position
boolean writePageIntoFile(long rrn, BTPAGE *page, FILE *file) {
    // Verifica se está tudo ok com os dados
    if (!file) {
        perror("File doesn't exists");
        exit(EXIT_FAILURE);
    }

    // Encontra local para escrita baseado no RRN
    long offSet = currentPage->items->recordRRN * PAGESIZE;
    fseek(file, offSet, SEEK_SET);
    BTPAGE *page = readPageFromFile(file);

    if (page->items->recordRRN > rrn)
        fseek(file,page->childs[0]); // Esquerda ??
    else if (page->items->recordRRN < rrn)
        fseek(file,page->childs[1]); // Direita ??
    else if (page->items->recordRRN == rrn)
        printf("Já existe");
        return FALSE;
    else if (Encontrou => == NULL){
        // Escreve dados
        fwrite(page, PAGESIZE, file);

        // Atualiza valor de espaço livre na página
        page->freeSpace = FREE_SPACE_ON_PAGE;
        return TRUE; 
    }
    writePageIntoFile(rrn,page,file);
    // Dica: você pode criar uma função que só lida com a escrita dos dados e chamar aqui
}


BTPAGE *getOrCreateRoot(FILE *file) {
    // Verifica se a árvore já existe ou precisa criar uma nova
    long rrnTreeHeader = getTreeHeader(file);
    // Se a roote não existir, cria ela
    if (rrnTreeHeader == NULL) {
        perror("bTree doesn't exists");
        return createTree(file);
    }

    // Se existir, só pega o RRN da raiz no cabeçalho e carrega sua página
    BTPAGE *root;
    fread(root, PAGESIZE, 1, file);

    return root;
    // Pode ser adaptada pra inserção e busca sem precisar de 2 funções
}


*/


boolean bTreeInsert(RECORD *newRecord, BTPAGE *root, FILE *file) {
    if (!root)
								return FALSE;
				// Função mais abstrata de inserção

    // Prepara os dados da nova chave
				PROMOTEDKEY *keyToInsert = createPromotedKey(newRecord, NULL);

    // Tenta inserir recursivamente
				PROMOTEDKEY *promotedKey = NULL;
				promotedKey = _bTreeInsert(root,keyToInsert ,file);
				
    // Se tiver chave promovida no final da recursão, é que existe nova raiz
				if (promotedKey){
								//faz os esquema de dividir
								// Chama as funções pra criar nova raiz e atualizar o cabeçalho
				}
				
				return TRUE;
}

//Recursive insertion
PROMOTEDKEY *_bTreeInsert(BTPAGE *node, PROMOTEDKEY *key, FILE *file) {
    // Se nó a ser inserido a chave é folha, tenta inserir
				if(node->isLeaf){
						// manipular o vetor records para fazer inserção		
						// verificar se lotou a pagina


				}
    // Caso a inserção crie uma promoção, precisa retornar a chave promovida para a recursão
    // Se não for nó folha, procura qual sub-árvore seguir para inserir numa folha
				long child;
				PROMOTEDKEY *promotedKey = NULL;
				for(int i = 0; i<node->numberOfKeys ;i++){
								if (node->items[i].key > key->key){
												if (node->childs[i]){
																//acessa o filho e continua descendo
																fseek(file,node->childs[i],SEEK_SET);
																break;
												}
												//Insere na posição i 
												//manipula records e verifica se super lotou a pagina
												return promotedKey;
								}
				}
				node = readPageFromFile(file);
				return _bTreeInsert(node,key,file);
				
    // Encontrar a posição correta e descer para filho à esquerda se a chave for menor
    // E descer à direita se for maior
    // Chamar a inserção recursiva pro filho escolhido
    // Se a inserção recursiva retornar uma chave promovida, precisa tentar inserir essa chave promovida no nó atual
    // Retornar chave promovida ou um valor NULL se não houve promoção
}

PROMOTEDKEY *insertIntoNode(BTPAGE *page, PROMOTEDKEY *newKey, FILE *file) {
    // Procura local pra inserir nova chave na página
    // Se não couber, splitta ele
    // Escreve dados na página
}

//Insert some key on page
BTPAGE *searchPositionOnPageAndInsert(BTPAGE *page, PROMOTEDKEY *newKey) {
    // Encontra a posição para inserir a chave
    // Se não existir espaço, precisa criar uma nova página (usem uma função para criar)
    // Salvar dados da nova chave na página
}

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

//Split node and writes into file
PROMOTEDKEY *_split(BTPAGE *page, FILE *file, PROMOTEDKEY *newKey) {
    // Divide a página, cria o novo nó (faça numa função auxiliar pois é complexo)
    // Extrai a chave promovida e atualiza os filhos da chave
    // Escreve a página nova e a que foi dividida (com suas atualizações) no arquivo
}

//Used if promotions reaches root
BTPAGE *createNodeWithPromotedKey(PROMOTEDKEY *promoKey) {
    // Se promoção cria estrutura para nova raiz,
    // Aloca espaço para ela
    // Salva dados da chave promovida na nova raiz
    // atualiza os filhos deste novo nó/página
    // Pode reusar função que cria página nova e adicionar somente especificidades
}

boolean setNodeAsRoot(BTPAGE *page, FILE *file) {
    // Escreve página nova e atualiza o cabeçalho para conter ela como raiz
    // Deveria ser chamada junto com criação de novo nó quando promoção cria uma nova raiz
}


