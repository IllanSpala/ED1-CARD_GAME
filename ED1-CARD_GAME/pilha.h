#include <stdlib.h>
#include "lista.h"
#ifndef PILHA_H
#define PILHA_H

typedef Tno tNoPilha; // carta && *prox 
typedef struct pilha{
    tNoPilha *topo;
    tNoPilha *base;
}tPilha;
#endif

tPilha *CriaPilha();
int PilhaVazia(tPilha *pilha);
void LiberaPilha(tPilha *pilha);
void InsereNoPilha(tPilha *pilha, tNoPilha *novoNo);
tNoPilha *RemoveNoPilha(tPilha *pilha);
tNoPilha *AcessaTopoPilha(tPilha *pilha);
int sizePilha(tPilha *pilha);
