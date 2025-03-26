#ifndef FILA_H
#define FILA_H
typedef struct fila
{
    int popTurno;
    int prazo;
    int needPaus; 
    int needCopas;
    int needEspadas;
    int needOuro;
    int extraRem; // reembaralho extra if so
    void *prox;
}Tmissao;

typedef struct noFila
{
    Tmissao *primeiro;
    Tmissao *ultimo;
}TnoFila;

TnoFila *CriaFila();
Tmissao *CriaNoFila(Tmissao novoNo);
int FilaVazia(TnoFila *fila);
void LiberaFila(TnoFila *fila);
void InsereNoFila(TnoFila *fila, Tmissao *novoNo);
Tmissao *RemoveNoFila(TnoFila *fila);
Tmissao *AcessaPrimFila(TnoFila *fila);
int sizeFila(TnoFila *fila);
void ImprimeFila(TnoFila *fila);

#endif
