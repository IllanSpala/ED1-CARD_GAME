#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "features.h"

// Variável global para acumular a pontuação
//feito por illan spala e bia gabriela neves de azevedo
static int pontuacao_acumulada = 0;

int main() {
    
    int i = 0, escolha, monteCont = 0, descarteCont = 0, contaCartas = 0, posOriginal, posDestino, quantDescarteTemp,
        recPaus = 0, recEspada = 0, recOuro = 0, recCopas = 0, turno = 1, turnoTarefa = 0, reembaralhos = 1, remain = 0, penalidade = 0, atvOk = 0;

    tPilha *monte = CriaPilha();
    tPilha *descarte = CriaPilha();
    Tno *mao = CriaLista();
    TnoFila *filatarefas = CriaFila();
    Tmissao missao;

    FILE *baralho = fopen("baralho1.dat", "r"); 
    if (baralho == NULL) {
        perror("Erro ao abrir o arquivo baralho1.dat");
        return 1;
    }

    FILE *tarefas = fopen("tarefas.dat", "r");
    if (tarefas == NULL) {
        perror("Erro ao abrir o arquivo tarefas.dat");
        fclose(baralho);
        return 1;
    }

    // Leitura do baralho
    Tcarta baralhoCartas[52];
    for (i = 0; i < 52; i++) {
        fscanf(baralho, "%2s %c %d %[^\n]s", baralhoCartas[i].face, &baralhoCartas[i].naipe, &baralhoCartas[i].valor, baralhoCartas[i].nome);
    }
    fclose(baralho);
    srand(time(NULL));
    embaralhaCartas(baralhoCartas, 52);

    // Insere cartas no monte
    for (i = 0; i < 52; i++) {
        tNoPilha *novoNo = malloc(sizeof(tNoPilha));
        if (novoNo == NULL) {
            perror("Erro ao alocar memória");
            return 1;
        }
        novoNo->carta = baralhoCartas[i];
        InsereNoPilha(monte, novoNo);
        monteCont++;
    }

    // Leitura das tarefas
    for (i = 0; i < 10; i++) {
        fscanf(tarefas, "%d %d %d %d %d %d %d", &missao.popTurno, &missao.prazo, &missao.needPaus, &missao.needEspadas, &missao.needOuro, &missao.needCopas, &missao.extraRem);
        InsereNoFila(filatarefas, CriaNoFila(missao));
    }
    fclose(tarefas);

    // Sorteia 5 cartas para a mão
    for (i = 0; i < 5; i++) {
        tNoPilha *cartaSorteada = RemoveNoPilha(monte);
        if (cartaSorteada) {
            InsereNoPosLista(&mao, CriaNoLista(cartaSorteada->carta), 1);
            monteCont--;
            contaCartas++;
        }
    }

    // Loop principal do jogo
    do {
        printf("\n\n");
        printf(" \n  \tTESTE **Cartas no monte: %d | Mão: %d | Descarte: %d  **TESTE \t\n", sizePilha(monte), sizeLista(mao), sizePilha(descarte));
        printf("*********************************************************************************************************************\n");
        printf("(P: %2d || E: %2d || O: %2d || C: %2d || *: %d) \tTurno: %d \t Cartas na Mão: %d \n \n", recPaus, recEspada, recOuro, recCopas, reembaralhos, turno, contaCartas);
        printf("Tarefas: ");
        if (!FilaVazia(filatarefas)) {
            if (filatarefas->primeiro->popTurno <= turno) {
                turnoTarefa = filatarefas->primeiro->popTurno + filatarefas->primeiro->prazo - turno;
                ImprimeFila(filatarefas);
            } else {
                printf("Nenhuma tarefa no momento!");
            }
        }
        printf("\nMonte(%d) \t\t\t Descarte(%d) \n \n", monteCont, descarteCont);
        ImprimeLista(mao);
        printf("   1     2     3     4     5    <- Mão \n\n");
        printf("Menu: \n");
        printf(" 1 - Reposicionar carta \n 2 - Descartar cartas \n 3 - Cumprir tarefa \n 4 - Reembaralhar tudo (*:X) \n 5 - Finalizar turno\n 6 - Finalizar jogo\n");
        printf("\n \n");
        printf("Digite a opção desejada: ");
        if (scanf("%d", &escolha) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (escolha) {
            case 1:  // Reposicionar carta
                printf("Posição de Origem: ");
                scanf("%d", &posOriginal);
                printf("Posição de Destino: ");
                scanf("%d", &posDestino);
                if (posOriginal > 0 && posOriginal < 6 && posDestino > 0 && posDestino < 6) {
                    MudaPosLista(&mao, posOriginal, posDestino);
                }
                break;

            case 2:  // Descartar cartas
                printf("Quantidade de cartas a serem descartadas: ");
                scanf("%d", &quantDescarteTemp);
                if (quantDescarteTemp > 0 && quantDescarteTemp < 6) {
                    for (i = 1; i <= quantDescarteTemp; i++) {
                        Tno *cartaDescartada = RemovePosLista(&mao, 1);
                        if (cartaDescartada) {
                            switch (cartaDescartada->carta.naipe) {
                                case 'P': recPaus += cartaDescartada->carta.valor; break;
                                case 'E': recEspada += cartaDescartada->carta.valor; break;
                                case 'O': recOuro += cartaDescartada->carta.valor; break;
                                case 'C': recCopas += cartaDescartada->carta.valor; break;
                            }
                            tNoPilha *novoNoDescarte = malloc(sizeof(tNoPilha));
                            novoNoDescarte->carta = cartaDescartada->carta;
                            InsereNoPilha(descarte, novoNoDescarte);
                            descarteCont++;
                            contaCartas--;
                            free(cartaDescartada);
                        }
                    }
                    // Atualiza pontuação acumulada com os bônus
                    int bonus = contaPontos(mao, contaCartas, &recPaus, &recEspada, &recOuro, &recCopas);
                    pontuacao_acumulada += bonus;
                    printf("Pontuação atual: %d\n", pontuacao_acumulada);
                }
                break;

            case 3:  // Cumprir tarefa
                if (!FilaVazia(filatarefas)) {
                    missao = *AcessaPrimFila(filatarefas);
                    if (missao.popTurno <= turno && recPaus >= missao.needPaus && recEspada >= missao.needEspadas && recOuro >= missao.needOuro && recCopas >= missao.needCopas) {
                        recPaus -= missao.needPaus;
                        recEspada -= missao.needEspadas;
                        recOuro -= missao.needOuro;
                        recCopas -= missao.needCopas;
                        reembaralhos += missao.extraRem;
                        RemoveNoFila(filatarefas);
                        printf("Tarefa cumprida!\n");
                    } else {
                        printf("Recursos insuficientes!\n");
                    }
                }
                break;

            case 4:  // Reembaralhar
                if (reembaralhos > 0) {
                    Reembaralhar(&mao, monte, descarte);
                    PreencheMao(monte, &mao, 5);
                    reembaralhos--;
                    printf("Cartas reembaralhadas!\n");
                } else {
                    printf("Sem reembaralhamentos disponíveis!\n");
                }
                break;

            case 5:  // Finalizar turno
                printf("Turno finalizado! Pontuação acumulada: %d\n", pontuacao_acumulada);
                if (contaCartas < 5) {
                    for (i = contaCartas; i < 5; i++) {
                        tNoPilha *cartaSorteada = RemoveNoPilha(monte);
                        if (cartaSorteada) {
                            InsereNoPosLista(&mao, CriaNoLista(cartaSorteada->carta), 1);
                            monteCont--;
                            contaCartas++;
                        }
                    }
                }
                turno++;
                break;

            case 6:  // Finalizar jogo
                printf("Fim de jogo! Pontuação final: %d\n", pontuacao_acumulada);
                LiberaPilha(monte);
                LiberaPilha(descarte);
                LiberaLista(&mao);
                LiberaFila(filatarefas);
                return 0;

            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (escolha != 6);

    return 0;
}