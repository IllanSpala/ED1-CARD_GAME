#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/**********************************************************************************************
 * Cria uma fila vazia.
 * @return Um ponteiro para uma estrutura TnoFila, que representa a fila.
 **********************************************************************************************/
TnoFila *CriaFila() {
    TnoFila *fila = (TnoFila*) malloc(sizeof(TnoFila));
    if (fila == NULL) {
        perror("Erro ao alocar memória para a fila");
        exit(1);
    }
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    return fila;
}

/***********************************************************************************************
 * Cria um novo nó para a fila.
 * @param novoNo Estrutura Tmissao que representa a miss o a ser armazenada no nó.
 * @return Um ponteiro para o novo nó criado, que contém a miss o e aponta para NULL.
 **********************************************************************************************/
Tmissao *CriaNoFila(Tmissao novoNo){
    Tmissao *aux = (Tmissao*) malloc(sizeof(Tmissao));
    if (aux == NULL) {
        perror("Erro ao alocar memória para o nó da fila");
        exit(1);
    }
    aux->popTurno = novoNo.popTurno;
    aux->prazo = novoNo.prazo;
    aux->needPaus = novoNo.needPaus;
    aux->needCopas = novoNo.needCopas;
    aux->needEspadas = novoNo.needEspadas;
    aux->needOuro = novoNo.needOuro;
    aux->extraRem = novoNo.extraRem;
    aux->prox = NULL;
    return aux;
}

/***********************************************************************************************
 * Verifica se a fila est  vazia.
 * @param fila Ponteiro para a fila a ser verificada.
 * @return 1 se a fila estiver vazia, 0 caso contr rio.
 **********************************************************************************************/
int FilaVazia(TnoFila *fila){
    return (fila->primeiro == NULL && fila->ultimo == NULL);
}

/***********************************************************************************************
 * Libera toda a memória alocada para a fila.
 * @param fila Ponteiro para a fila a ser liberada.
 **********************************************************************************************/
void LiberaFila(TnoFila *fila){
    Tmissao *aux, *aux2;
    aux = fila->primeiro;
    while(aux != NULL){
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(fila);
}

/**********************************************************************************************
 * Imprime as informa es de todos os n s da fila.
 * O formato de impress o  o seguinte:
 *  <n mero de turnos> Turnos.(V: <n mero> || P: <n mero> || E: <n mero> || O: <n mero> || C: <n mero>  || *: <n mero> )
 * @param fila Ponteiro para a fila a ser impressa.
 **********************************************************************************************/
void ImprimeFila(TnoFila *fila){
    Tmissao *aux = fila->primeiro;
    if(!FilaVazia(fila)){
        printf("%d Turnos.(V: %d || P: %d || E: %d || O: %d || C: %d  || *: %d )\n", aux->popTurno, aux->prazo, aux->needPaus, aux->needEspadas, aux->needOuro, aux->needCopas, aux->extraRem);
        aux = aux->prox;
    }
}

/**********************************************************************************************
 * Insere um novo n o na fila.
 * Caso a fila esteja vazia, o novo n o ser  o primeiro e o  ltimo.
 * Caso contr rio, o novo n o ser  inserido ap s o  ltimo n o da fila.
 * @param fila Ponteiro para a fila a ser inserido o novo n o.
 * @param novoNo Ponteiro para o novo n o a ser inserido na fila.
 **********************************************************************************************/
void InsereNoFila(TnoFila *fila, Tmissao *novoNo){
    if(FilaVazia(fila)){
        fila->primeiro = novoNo;
        fila->ultimo = novoNo;
    }else{
        fila->ultimo->prox = novoNo;
        fila->ultimo = novoNo;
    }
}

/*********************************************************************************************
 * Remove o primeiro nó da fila e o retorna.
 * Se a fila estiver vazia, retorna NULL.
 * @param fila Ponteiro para a estrutura da fila.
 * @return Um ponteiro para o Tmissao removido da fila.
 *********************************************************************************************/

Tmissao *RemoveNoFila(TnoFila *fila){
    Tmissao *aux;
    if (!FilaVazia(fila)){
        aux = fila->primeiro;
        fila->primeiro = fila->primeiro->prox;
        if (fila->primeiro == NULL) {
            fila->ultimo = NULL;
        }
        aux->prox = NULL;
        return aux;
    }
    return NULL;
}

/*********************************************************************************************
 * Retorna o n mero de elementos na fila.
 * @param fila Ponteiro para a estrutura da fila.
 * @return O n mero de elementos na fila.
 ********************************************************************************************/
int sizeFila(TnoFila *fila){
    int i = 0;
    Tmissao *aux = fila->primeiro;
    while(aux != NULL){
        aux = aux->prox;
        i++;
    }
    return i;
}

/*********************************************************************************************
 * Acessa o primeiro nó da fila.
 * @param fila Ponteiro para a estrutura da fila.
 * @return Um ponteiro para o primeiro Tmissao na fila, ou NULL se a fila estiver vazia.
 *********************************************************************************************/
Tmissao *AcessaPrimFila(TnoFila *fila){
    return fila->primeiro;
}