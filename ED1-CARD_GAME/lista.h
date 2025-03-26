#include<stdio.h>
#ifndef LISTA_H
#define LISTA_H

typedef struct carta{
  char face[3];
  char naipe;
  int valor;
  char nome[18];
}Tcarta;

typedef struct _noh{
    Tcarta carta;
    void *prox;
}Tno;

Tno *CriaLista(); // ok
int ListaVazia(Tno *lista); // ok
void LiberaLista(Tno **lista); // ok
Tno *CriaNoLista(Tcarta carta); // ok
void InsereNoPosLista(Tno **lista, Tno *novoNo, int pos); // ok aka *InsereNo
Tno *RemovePosLista(Tno **lista, int pos); // ok aka *RemoveNo
Tno *AcessaPosLista(Tno *lista, int pos); // ok aka *AcessaNo
void MudaPosLista(Tno **lista, int posOrig, int posDest); // ok
void MudaLista(Tno **listaOriginal, Tno **ListaDestino, int tamanho); // ok
void ImprimeLista(Tno *lista); // okok testing
int sizeLista(Tno *lista);



#endif