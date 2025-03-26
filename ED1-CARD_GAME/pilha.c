#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/*/*********************************************************************************************
 * Cria uma pilha vazia.
 * @return Um ponteiro para uma pilha vazia. Se não for possível alocar memória,
 *         termina o programa com um erro.
 *********************************************************************************************/
tPilha *CriaPilha() {
    tPilha *aux = malloc(sizeof(tPilha));
    if (aux == NULL) {
        perror("Erro ao alocar memória para a pilha");
        exit(1);
    }
    aux->topo = NULL;
    aux->base = NULL;
    return aux;
}

/*********************************************************************************************
 * Verifica se a pilha está vazia.
 * @param pilha Ponteiro para a pilha a ser verificada.
 * @return 1 se a pilha estiver vazia, 0 caso contrário.
*********************************************************************************************/
int PilhaVazia(tPilha *pilha) {
    return (pilha->topo == NULL && pilha->base == NULL);
}


/**********************************************************************************************
 * Libera toda a memória alocada para a pilha.
 * @param pilha Ponteiro para a pilha a ser liberada.
 *********************************************************************************************/
void LiberaPilha(tPilha *pilha) {
    tNoPilha *aux;
    while (!PilhaVazia(pilha)) {
        aux = pilha->topo->prox;
        free(pilha->topo);
        pilha->topo = aux;
    }
    free(pilha);
}

/*********************************************************************************************
 * Insere um novo nó na pilha.
 * @param pilha Ponteiro para a pilha na qual o novo nó deve ser inserido.
 * @param novoNo Ponteiro para o novo nó a ser inserido. Se for NULL, termina
 *               o programa com um erro.
 * Se a pilha estiver vazia, o novo nó se torna o topo e a base da pilha.
 * Caso contrário, o novo nó é inserido na frente do atual topo da pilha e
 * se torna o novo topo.
 *********************************************************************************************/
void InsereNoPilha(tPilha *pilha, tNoPilha *novoNo) {
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o nó da pilha");
        exit(1);
    }
    if (PilhaVazia(pilha)) {
        pilha->topo = novoNo;
        pilha->base = novoNo;
    } else {
        novoNo->prox = pilha->topo;
        pilha->topo = novoNo;
    }
}

/*********************************************************************************************
 * Remove o nó do topo da pilha.
 * @param pilha Ponteiro para a pilha da qual o nó do topo será removido.
 * @return Um ponteiro para o nó removido ou NULL se a pilha estiver vazia.
 * Se a pilha ficar vazia após a remoção, atualiza o ponteiro da base para NULL.
 *********************************************************************************************/
tNoPilha *RemoveNoPilha(tPilha *pilha) {
    if (PilhaVazia(pilha)) {
        return NULL;
    }
    tNoPilha *aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    if (pilha->topo == NULL) {
        pilha->base = NULL;
    }
    aux->prox = NULL;
    return aux;
}

/*********************************************************************************************
 * Acessa o nó do topo da pilha sem o remover.
 * @param pilha Ponteiro para a pilha cujo nó do topo se deseja acessar.
 * @return Um ponteiro para o nó do topo da pilha ou NULL se a pilha estiver vazia.
 *********************************************************************************************/
tNoPilha *AcessaTopoPilha(tPilha *pilha) {
    return pilha->topo;
}

/**********************************************************************************************
 * Retorna o tamanho da pilha.
 * @param pilha Ponteiro para a pilha cujo tamanho se deseja obter.
 * @return O tamanho da pilha.
 *********************************************************************************************/
int sizePilha(tPilha *pilha) {
    int i = 0;
    tNoPilha *aux = pilha->topo;
    while (aux != NULL) {
        aux = aux->prox;
        i++;
    }
    return i;
}