#include "lista.h"
#include "fila.h"
#include "pilha.h"


int aleatorio(int n);
void SorteiaCarta(Tno **listaOriginal, Tno **listaDestino, int tamanho);
void PreencheMao(tPilha *pilha, Tno **lista, int tamanho);
void Reembaralhar(Tno **mao, tPilha *monte, tPilha *descarte);
int contaPontos(Tno *lista, int tamanho, int *recPaus, int *recEspada, int *recOuro, int *recCopas);
void EscolheNaipeBonus(int pontos, int *recPaus, int *recEspada, int *recOuro, int *recCopas);
void embaralhaCartas(Tcarta *cartas, int n);