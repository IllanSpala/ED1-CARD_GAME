#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "features.h"

/***********************************************************************************************
 * Gera um número aleatório entre 0 e n.
 * @param n O limite superior para o número aleatório.
 * @return Um número aleatório entre 0 e n.
 ***********************************************************************************************/
int aleatorio(int n) {  
    return rand() % (n + 1);
}

/***********************************************************************************************
 * Sorteia uma carta de uma lista original e insere na lista destino.
 * @param listaOrig Ponteiro para o ponteiro do início da lista original.
 * @param listaDest Ponteiro para o ponteiro do início da lista destino.
 * @param tamanho O tamanho da lista original.
 ***********************************************************************************************/
void SorteiaCarta(Tno **listaOrig, Tno **listaDest, int tamanho){
    if(tamanho > 0) {
        int pos = aleatorio(tamanho);
        InsereNoPosLista(listaDest, RemovePosLista(listaOrig, pos), 1);
    }
}

/***********************************************************************************************
 * Preenche a mão do jogador com cartas da pilha.
 * @param pilha Ponteiro para a pilha de cartas.
 * @param lista Ponteiro para o ponteiro do início da lista de cartas na mão.
 * @param tamanho O número de cartas a serem movidas da pilha para a mão.
 ***********************************************************************************************/
void PreencheMao(tPilha *pilha, Tno **lista, int tamanho){
    while(sizeLista(*lista) < 5){
        if(!PilhaVazia(pilha)){
            InsereNoPosLista(lista, CriaNoLista(RemoveNoPilha(pilha)->carta), 1);
        }
    }
}

/***********************************************************************************************
 * Conta os pontos das cartas na lista.
 * @param lista Ponteiro para o início da lista de cartas.
 * @param tamanho O tamanho da lista de cartas.
 * @param recPaus Ponteiro para o contador de cartas de Paus.
 * @param recEspada Ponteiro para o contador de cartas de Espadas.
 * @param recOuro Ponteiro para o contador de cartas de Ouros.
 * @param recCopas Ponteiro para o contador de cartas de Copas.
 * @return A pontuação total das cartas na lista.
 ***********************************************************************************************/
int contaPontos(Tno *lista, int tamanho, int *recPaus, int *recEspada, int *recOuro, int *recCopas) {
    if (tamanho <= 1) return 0; // Descarte único não gera bônus!

    int pontuacao = 0;
    int seq = 1, max_seq = 1;
    int numP = 0, numE = 0, numO = 0, numC = 0;
    int temPar = 0, temTrinca = 0, temQuadra = 0, temSequencia = 0, temNaipe = 0;
    
    Tcarta *cartas = malloc(tamanho * sizeof(Tcarta));
    Tno *current = lista;
    
    // Copia cartas para o array
    for (int i = 0; i < tamanho && current != NULL; i++) {
        cartas[i] = current->carta;
        current = current->prox;
        
        // Conta cartas por naipe
        switch (cartas[i].naipe) {
            case 'P': numP++; break;
            case 'E': numE++; break;
            case 'O': numO++; break;
            case 'C': numC++; break;
        }
    }

    // Ordena cartas por valor (para sequências)
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (cartas[i].valor > cartas[j].valor) {
                Tcarta temp = cartas[i];
                cartas[i] = cartas[j];
                cartas[j] = temp;
            }
        }
    }

    // Verifica sequências (apenas se tamanho >= 2)
    for (int i = 0; i < tamanho - 1; i++) {
        if (cartas[i].valor + 1 == cartas[i + 1].valor) {
            seq++;
            max_seq = (seq > max_seq) ? seq : max_seq;
        } else {
            seq = 1;
        }
    }
    if (max_seq >= 2) {
        pontuacao += 2 * max_seq; // +2 por carta na sequência
        temSequencia = 1;
    }

    // Verifica pares/trincas/quadras (apenas se tamanho >= 2)
    for (int i = 0; i < tamanho; i++) {
        int count = 1;
        for (int j = i + 1; j < tamanho; j++) {
            if (cartas[i].valor == cartas[j].valor) {
                count++;
            }
        }
        // Aplica bônus apenas se houver combinações válidas
        if (count >= 2) {
            switch (count) {
                case 2: pontuacao += 2; temPar = 1; break;  // Par
                case 3: pontuacao += 5; temTrinca = 1; break;  // Trinca
                case 4: pontuacao += 20; temQuadra = 1; break; // Quadra
            }
        }
    }

    // Bônus por naipe (apenas se >= 2 cartas do mesmo naipe)
    if (numP >= 2) { pontuacao += 3 * numP; temNaipe = 1; }
    if (numE >= 2) { pontuacao += 3 * numE; temNaipe = 1; }
    if (numO >= 2) { pontuacao += 3 * numO; temNaipe = 1; }
    if (numC >= 2) { pontuacao += 3 * numC; temNaipe = 1; }

    free(cartas);

    // Aplica bônus apenas se houver pelo menos uma combinação válida
    if (temPar || temTrinca || temQuadra || temSequencia || temNaipe) {
        EscolheNaipeBonus(pontuacao, recPaus, recEspada, recOuro, recCopas);
        return pontuacao;
    }

    return 0; // Retorna 0 se não houver combinações válidas
}
/***********************************************************************************************
 * Permite ao jogador escolher um naipe para aplicar um bônus de pontos.
 * @param pontos A quantidade de pontos de bônus.
 * @param recPaus Ponteiro para o contador de cartas de Paus.
 * @param recEspada Ponteiro para o contador de cartas de Espadas.
 * @param recOuro Ponteiro para o contador de cartas de Ouros.
 * @param recCopas Ponteiro para o contador de cartas de Copas.
 ***********************************************************************************************/
void EscolheNaipeBonus(int pontos, int *recPaus, int *recEspada, int *recOuro, int *recCopas) {
    int escolha;
    printf("************************Você ganhou um bônus de %d pontos! Escolha onde aplicar esse B Ô N U S************************\n", pontos);
    printf("1 - Paus\n2 - Espadas\n3 - Ouros\n4 - Copas\n");
    printf("Escolha: ");
    if (scanf("%d", &escolha) != 1) {
        printf("Entrada inválida!\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    switch (escolha) {
        case 1: *recPaus += pontos; break;
        case 2: *recEspada += pontos; break;
        case 3: *recOuro += pontos; break;
        case 4: *recCopas += pontos; break;
        default: printf("Opção inválida!\n"); break;
    }
}

/***********************************************************************************************

 ***********************************************************************************************/
void Reembaralhar(Tno **mao, tPilha *monte, tPilha *descarte) {
    // 1. Juntar TODAS as cartas em um array temporário
    int total_cartas = sizeLista(*mao) + sizePilha(monte) + sizePilha(descarte);
    Tcarta *cartas = malloc(total_cartas * sizeof(Tcarta));
    int idx = 0;

    // Extrai cartas da mão (sem criar novas)
    while (!ListaVazia(*mao)) {
        Tno *carta = RemovePosLista(mao, 1);
        cartas[idx++] = carta->carta;
        free(carta); // Libera o nó, mas preserva a carta
    }

    // Extrai cartas do monte
    while (!PilhaVazia(monte)) {
        tNoPilha *carta = RemoveNoPilha(monte);
        cartas[idx++] = carta->carta;
        free(carta);
    }

    // Extrai cartas do descarte
    while (!PilhaVazia(descarte)) {
        tNoPilha *carta = RemoveNoPilha(descarte);
        cartas[idx++] = carta->carta;
        free(carta);
    }

    // 2. Embaralha o array
    embaralhaCartas(cartas, total_cartas);

    // 3. Reinsere TODAS as cartas no monte
    for (int i = 0; i < total_cartas; i++) {
        tNoPilha *novoNo = malloc(sizeof(tNoPilha));
        novoNo->carta = cartas[i];
        InsereNoPilha(monte, novoNo);
    }

    // 4. Distribui 5 cartas para a mão
    for (int i = 0; i < 5 && !PilhaVazia(monte); i++) {
        tNoPilha *carta = RemoveNoPilha(monte);
        InsereNoPosLista(mao, CriaNoLista(carta->carta), 1);
        free(carta);
    }

    free(cartas); // Libera o array temporário
}


/*********************************************************************************************
 * Embaralha um vetor de cartas.
 * @param cartas Ponteiro para o vetor de cartas a ser embaralhado.
 * @param n O número de cartas no vetor.
*********************************************************************************************/
void embaralhaCartas(Tcarta *cartas, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Tcarta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
}