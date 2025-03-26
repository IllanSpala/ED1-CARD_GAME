#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************************************************************
 * Cria uma lista vazia.
 * @return Um ponteiro para um Tno, que aponta para NULL.
 *********************************************************************************************/
Tno *CriaLista() {
    return NULL;
}

/*********************************************************************************************
 * Verifica se a lista está vazia.
 * @param lista Ponteiro para a lista a ser verificada.
 * @return 1 se a lista estiver vazia, 0 caso contrário.
 *********************************************************************************************/
int ListaVazia(Tno *lista) {
    return (lista == NULL);
}

/*********************************************************************************************
 * Libera toda a memória alocada para a lista.
 * @param lista Ponteiro para o ponteiro do início da lista.
*********************************************************************************************/
void LiberaLista(Tno **lista) {
    Tno *aux;
    while (!ListaVazia(*lista)) {
        aux = (*lista)->prox;
        free(*lista);
        *lista = aux;
    }
}


/*********************************************************************************************
 * Cria um novo nó para a lista.
 * @param carta Estrutura Tcarta que representa a carta a ser armazenada no nó.
 * @return Um ponteiro para o novo nó criado, que contém a carta e aponta para NULL.
 **********************************************************************************************/
Tno *CriaNoLista(Tcarta carta) {
    Tno *novoNo = malloc(sizeof(Tno));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o nó da lista");
        exit(1);
    }
    strcpy(novoNo->carta.face, carta.face);
    novoNo->carta.naipe = carta.naipe;
    novoNo->carta.valor = carta.valor;
    strcpy(novoNo->carta.nome, carta.nome);
    novoNo->prox = NULL;
    return novoNo;
}


/***********************************************************************************************
 * Insere um novo nó em uma posição especificada na lista.
 * @param lista Ponteiro para o ponteiro do início da lista.
 * @param novoNo Ponteiro para o novo nó a ser inserido.
 * @param pos A posição na lista onde o novo nó deve ser inserido.
 * Se a lista não estiver vazia, o novo nó é inserido na posição especificada.
 * Caso contrário, ele é inserido no início da lista.
 ***********************************************************************************************/
void InsereNoPosLista(Tno **lista, Tno *novoNo, int pos) {
    int i = 1;
    Tno *aux, **aux2;
    aux2 = lista;
    while (i < pos && (*aux2) != NULL) {
        aux2 = (Tno**) &((*aux2)->prox);
        i++;
    }
    aux = novoNo;
    aux->prox = (*aux2);
    (*aux2) = aux;
}


/***********************************************************************************************
 * Remove um nó de uma posição especificada na lista.
 * @param lista Ponteiro para o ponteiro do início da lista.
 * @param pos A posição do nó a ser removido.
 * @return Um ponteiro para o nó removido.
 ***********************************************************************************************/
Tno *RemovePosLista(Tno **lista, int pos) {
    int i;
    Tno *aux, *aux2;
    aux = (*lista);
    if (pos == 1) {
        (*lista) = aux->prox;
        aux->prox = NULL;
        return aux;
    } else {
        for (i = 1; i < pos - 1; i++) aux = aux->prox;
        aux2 = aux->prox;
        aux->prox = aux2->prox;
        aux2->prox = NULL;
        return aux2;
    }
}

/***********************************************************************************************
 * Acessa o elemento que se encontra na posição "pos" da lista.
 * @param lista Ponteiro para o início da lista.
 * @param pos A posição da lista que se deseja acessar.
 * @return Um ponteiro para o elemento que se encontra na posição "pos" da lista.
 ***********************************************************************************************/
Tno *AcessaPosLista(Tno *lista, int pos) {
    int i;
    Tno *aux = lista;
    for (i = 0; i < pos - 1; i++) {
        aux = aux->prox;
    }
    return aux;
}

/***********************************************************************************************
 * Troca a posição de um elemento na lista.
 * @param lista Ponteiro para o ponteiro do início da lista.
 * @param posOrig A posição original do elemento a ser movido.
 * @param posDest A posição destino do elemento a ser movido.
 ***********************************************************************************************/
void MudaPosLista(Tno **lista, int posOrig, int posDest) {
    Tno *aux = RemovePosLista(lista, posOrig);
    InsereNoPosLista(lista, aux, posDest);
}


/***********************************************************************************************
 * Move uma carta da lista original para a lista destino.
 * @param listaOriginal Ponteiro para o ponteiro do início da lista original.
 * @param ListaDestino Ponteiro para o ponteiro do início da lista destino.
 * @param tamanho A quantidade de cartas na lista original.
 ***********************************************************************************************/
void MudaLista(Tno **listaOriginal, Tno **ListaDestino, int tamanho) {
    Tno *aux = RemovePosLista(listaOriginal, 1);
    InsereNoPosLista(ListaDestino, aux, tamanho);
}

/***********************************************************************************************
 * Imprime os elementos de uma lista de cartas.
 * Cada carta é impressa no formato "face-naipe" até o final da lista.
 * @param lista Ponteiro para o início da lista de cartas a ser impressa.
 ***********************************************************************************************/
void ImprimeLista(Tno *lista) {
    Tno *aux = lista;
    if (!ListaVazia(aux)) {
        while (!ListaVazia(aux)) {
            printf("│%2s-%c ", aux->carta.face, aux->carta.naipe);
            aux = aux->prox;
        }
        printf("│\n");
    }
}

/***********************************************************************************************
 * Retorna o tamanho da lista.
 * @param lista Ponteiro para o início da lista.
 * @return O tamanho da lista.
 ***********************************************************************************************/
int sizeLista(Tno *lista) {
    int i = 0;
    Tno *aux = lista;
    while (aux != NULL) {
        aux = aux->prox;
        i++;
    }
    return i;
}