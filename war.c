// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para os jogadores.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// ======================================================================
// PRÁTICA: Jogo WAR em C - Nível Mestre
// OBJETIVO DESTA PARTE:
// - implementar a funcionalidade de missões estratégicas individuais para cada jogador.
// - o sistema deverá sortear uma missão de forma automática entre diversas descrições pré-definidas.
// - O ataque será resolvido por meio de uma simulação com dados aleatórios (como rolagem de dados), 
//   e o resultado alterará o controle e as tropas do território atacado.
// ======================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_MISSAO 100
#define TOTAL_TERRITORIOS 5

// Struct dos territorios
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Limpa buffer do teclado
void limparBufferEntrada() {
    int c;

    while((c = getchar()) != '\n' && c != EOF) {
    }
}

// Pausa do jogo
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBufferEntrada();
    getchar();
}

// Exibe o mapa
void exibirMapa(Territorio* mapa, int tamanho) {

    int i;

    printf("\n================ MAPA DO MUNDO ================\n");

    for(i = 0; i < tamanho; i++) {

        printf("%d. %-12s (Exercito: %-10s, Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }

    printf("================================================\n");
}

// Exibe menu de escolha do exercito
void escolherExercito(char* corJogador) {

    int opcao;

    printf("\n--- ESCOLHA SEU EXERCITO ---\n");
    printf("1 - Azul\n");
    printf("2 - Verde\n");
    printf("3 - Vermelho\n");
    printf("4 - Amarelo\n");
    printf("5 - Branco\n");

    printf("Escolha: ");
    scanf("%d", &opcao);

    switch(opcao) {

        case 1:
            strcpy(corJogador, "Azul");
            break;

        case 2:
            strcpy(corJogador, "Verde");
            break;

        case 3:
            strcpy(corJogador, "Vermelho");
            break;

        case 4:
            strcpy(corJogador, "Amarelo");
            break;

        case 5:
            strcpy(corJogador, "Branco");
            break;

        default:
            printf("\nOpcao invalida! Exercicio Azul escolhido automaticamente.\n");
            strcpy(corJogador, "Azul");
    }
}

// Sorteia missao
void atribuirMissao(char* destino,
                    char* missoes[],
                    int totalMissoes,
                    char* corJogador) {

    int sorteio;

    do {

        sorteio = rand() % totalMissoes;

    } while(
        (strcmp(corJogador, "Azul") == 0 &&
         strcmp(missoes[sorteio], "Destruir o exercito Azul") == 0)

         ||

        (strcmp(corJogador, "Verde") == 0 &&
         strcmp(missoes[sorteio], "Destruir o exercito Verde") == 0)

         ||

        (strcmp(corJogador, "Vermelho") == 0 &&
         strcmp(missoes[sorteio], "Destruir o exercito Vermelho") == 0)

         ||

        (strcmp(corJogador, "Amarelo") == 0 &&
         strcmp(missoes[sorteio], "Destruir o exercito Amarelo") == 0)

         ||

        (strcmp(corJogador, "Branco") == 0 &&
         strcmp(missoes[sorteio], "Destruir o exercito Branco") == 0)
    );

    strcpy(destino, missoes[sorteio]);
}

// Exibe missao
void exibirMissao(char* missao, char* corJogador) {

    printf("\n--- SUA MISSAO (Exercito %s) ---\n",
           corJogador);

    printf("%s\n",
           missao);
}

// Verifica se determinada cor ainda existe
int existeCor(Territorio* mapa,
              int tamanho,
              char* cor) {

    int i;

    for(i = 0; i < tamanho; i++) {

        if(strcmp(mapa[i].cor, cor) == 0) {

            return 1;
        }
    }

    return 0;
}

// Conta territorios de determinada cor
int contarTerritorios(Territorio* mapa,
                      int tamanho,
                      char* cor) {

    int i;
    int contador = 0;

    for(i = 0; i < tamanho; i++) {

        if(strcmp(mapa[i].cor, cor) == 0) {

            contador++;
        }
    }

    return contador;
}

// Verifica dominio total
int dominaTudo(Territorio* mapa,
               int tamanho,
               char* cor) {

    int i;

    for(i = 0; i < tamanho; i++) {

        if(strcmp(mapa[i].cor, cor) != 0) {

            return 0;
        }
    }

    return 1;
}

// Verifica missao
int verificarMissao(char* missao,
                    Territorio* mapa,
                    int tamanho,
                    char* corJogador) {

    if(strcmp(missao,
              "Conquistar pelo menos 3 territorios") == 0) {

        if(contarTerritorios(mapa,
                             tamanho,
                             corJogador) >= 3) {

            return 1;
        }
    }

    if(strcmp(missao,
              "Destruir o exercito Vermelho") == 0) {

        if(existeCor(mapa,
                     tamanho,
                     "Vermelho") == 0) {

            return 1;
        }
    }

    if(strcmp(missao,
              "Destruir o exercito Azul") == 0) {

        if(existeCor(mapa,
                     tamanho,
                     "Azul") == 0) {

            return 1;
        }
    }

    if(strcmp(missao,
              "Destruir o exercito Verde") == 0) {

        if(existeCor(mapa,
                     tamanho,
                     "Verde") == 0) {

            return 1;
        }
    }

    if(strcmp(missao,
              "Conquistar todos os territorios") == 0) {

        if(dominaTudo(mapa,
                      tamanho,
                      corJogador)) {

            return 1;
        }
    }

    return 0;
}

// Sistema de ataque
void atacar(Territorio* atacante,
             Territorio* defensor) {

    int dadoAtaque;
    int dadoDefesa;

    printf("\n--- RESULTADO DA BATALHA ---\n");

    // Mesmo exercito
    if(strcmp(atacante->cor,
              defensor->cor) == 0) {

        printf("Ataque invalido! Mesmo exercito.\n");

        return;
    }

    // Tropas insuficientes
    if(atacante->tropas <= 1) {

        printf("Ataque invalido! O atacante precisa ter mais de 1 tropa.\n");

        return;
    }

    dadoAtaque = rand() % 6 + 1;
    dadoDefesa = rand() % 6 + 1;

    printf("Ataque (%s): %d | Defesa (%s): %d\n",
           atacante->nome,
           dadoAtaque,
           defensor->nome,
           dadoDefesa);

    // Resultado
    if(dadoAtaque > dadoDefesa) {

        defensor->tropas--;

        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");

        // Conquista
        if(defensor->tropas <= 0) {

            strcpy(defensor->cor,
                   atacante->cor);

            defensor->tropas = 1;

            atacante->tropas--;

            printf("O territorio %s foi conquistado!\n",
                   defensor->nome);
        }

    } else {

        atacante->tropas--;

        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
    }
}

// Libera memoria
void liberarMemoria(Territorio* mapa,
                    char* missaoJogador) {

    free(mapa);
    free(missaoJogador);

    printf("\nMemoria liberada com sucesso!\n");
}

int main() {

    Territorio* mapa;

    char* missaoJogador;

    char corJogador[10];

    int opcao;

    int atacante;
    int defensor;

    int fimDeJogo = 0;

    char* missoes[] = {

        "Conquistar pelo menos 3 territorios",
        "Destruir o exercito Vermelho",
        "Destruir o exercito Azul",
        "Destruir o exercito Verde",
        "Conquistar todos os territorios"
    };

    int totalMissoes = 5;

    srand(time(NULL));

    printf("============================================\n");
    printf("           WAR - NIVEL MESTRE\n");
    printf("============================================\n");

    // Alocacao dinamica do mapa
    mapa = (Territorio*)
           calloc(TOTAL_TERRITORIOS,
                  sizeof(Territorio));

    // Alocacao da missao
    missaoJogador = (char*)
                     malloc(TAM_MISSAO *
                     sizeof(char));

    // Definicao fixa dos territorios
    mapa[0] = (Territorio) {"America", "Verde", 5};
    mapa[1] = (Territorio) {"Europa", "Azul", 3};
    mapa[2] = (Territorio) {"Asia", "Vermelho", 2};
    mapa[3] = (Territorio) {"Africa", "Amarelo", 4};
    mapa[4] = (Territorio) {"Oceania", "Branco", 1};

    // Escolha do exercito
    escolherExercito(corJogador);

    // Sorteio da missao
    atribuirMissao(missaoJogador,
                   missoes,
                   totalMissoes,
                   corJogador);

    // Loop principal
    while(fimDeJogo == 0) {

        exibirMapa(mapa,
                   TOTAL_TERRITORIOS);

        exibirMissao(missaoJogador,
                     corJogador);

        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");

        printf("Escolha sua acao: ");
        scanf("%d",
              &opcao);

        switch(opcao) {

            case 1:

                printf("\n--- FASE DE ATAQUE ---\n");

                printf("Escolha o territorio atacante (1 a 5): ");
                scanf("%d",
                      &atacante);

                printf("Escolha o territorio defensor (1 a 5): ");
                scanf("%d",
                      &defensor);

                atacante--;
                defensor--;

                // Validacoes
                if(atacante < 0 ||
                   atacante >= TOTAL_TERRITORIOS ||
                   defensor < 0 ||
                   defensor >= TOTAL_TERRITORIOS) {

                    printf("\nTerritorio invalido!\n");
                }
                else if(atacante == defensor) {

                    printf("\nUm territorio nao pode atacar ele mesmo!\n");
                }
                else {

                    atacar(&mapa[atacante],
                            &mapa[defensor]);

                    // Verifica missao automaticamente
                    if(verificarMissao(missaoJogador,
                                       mapa,
                                       TOTAL_TERRITORIOS,
                                       corJogador)) {

                        exibirMapa(mapa,
                                   TOTAL_TERRITORIOS);

                        printf("\n=========================================\n");
                        printf("          MISSAO CUMPRIDA!\n");
                        printf("=========================================\n");

                        printf("\nO Exercito %s venceu a guerra!\n",
                               corJogador);

                        printf("Missao realizada: %s\n",
                               missaoJogador);

                        fimDeJogo = 1;
                    }
                }

                if(fimDeJogo == 0) {

                    pausar();
                }

                break;

            case 2:

                if(verificarMissao(missaoJogador,
                                   mapa,
                                   TOTAL_TERRITORIOS,
                                   corJogador)) {

                    printf("\nVoce cumpriu sua missao!\n");

                    printf("O Exercito %s venceu a guerra!\n",
                           corJogador);

                    fimDeJogo = 1;
                }
                else {

                    printf("\nVoce ainda nao cumpriu sua missao. Continue lutando!\n");

                    pausar();
                }

                break;

            case 0:

                fimDeJogo = 1;

                break;

            default:

                printf("\nOpcao invalida!\n");

                pausar();
        }
    }

    liberarMemoria(mapa,
                   missaoJogador);

    return 0;
}
