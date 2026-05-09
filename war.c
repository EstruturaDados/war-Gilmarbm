// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// ======================================================================
// PRÁTICA: Jogo WAR em C - Nível Aventureiro
// OBJETIVO DESTA PARTE:
// - implementar a funcionalidade de ataque entre territórios
// - o sistema deverá permitir que um jogador selecione um território como atacante, e outro como defensor
// - O ataque será resolvido por meio de uma simulação com dados aleatórios (como rolagem de dados), 
//   e o resultado alterará o controle e as tropas do território atacado
// ======================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funcao para limpar buffer
void limparBufferEntrada() {
    int c;

    while((c = getchar()) != '\n' && c != EOF) {
    }
}

// Funcao para pausar o jogo
void pausar() {
    printf("\nPressione Enter para continuar para o proximo turno...");
    limparBufferEntrada();
    getchar();
}

// Funcao para cadastrar territorios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {

    int i;

    for(i = 0; i < quantidade; i++) {

        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Nome do territorio: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Funcao para exibir o mapa
void exibirMapa(Territorio* mapa, int quantidade) {

    int i;

    printf("\n        MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("============================================\n\n");

    for(i = 0; i < quantidade; i++) {

        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }

    printf("\n");
}

// Funcao para verificar vencedor
int verificarVencedor(Territorio* mapa, int quantidade) {

    int i;

    for(i = 1; i < quantidade; i++) {

        if(strcmp(mapa[i].cor, mapa[0].cor) != 0) {

            return 0;
        }
    }

    return 1;
}

// Funcao de batalha
void atacar(Territorio* atacante,
             Territorio* defensor) {

    int dadoAtacante;
    int dadoDefensor;

    printf("\n--- RESULTADO DA BATALHA ---\n");

    // Verifica se eh o mesmo exercito
    if(strcmp(atacante->cor, defensor->cor) == 0) {

        printf("Ataque invalido! Nao pode atacar territorio do mesmo exercito.\n");

        return;
    }

    // Verifica tropas suficientes
    if(atacante->tropas <= 1) {

        printf("Ataque invalido! O atacante precisa ter mais de 1 tropa.\n");

        return;
    }

    // Dados aleatorios
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("O atacante %s rolou um dado e tirou: %d\n",
           atacante->nome,
           dadoAtacante);

    printf("O defensor %s rolou um dado e tirou: %d\n",
           defensor->nome,
           dadoDefensor);

    // Resultado da batalha
    if(dadoAtacante > dadoDefensor) {

        defensor->tropas--;

        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");

        // Conquista do territorio
        if(defensor->tropas <= 0) {

            strcpy(defensor->cor,
                   atacante->cor);

            defensor->tropas = 1;

            atacante->tropas--;

            printf("O territorio %s foi conquistado pelo Exercito %s!\n",
                   defensor->nome,
                   defensor->cor);
        }

    }
    else {

        atacante->tropas--;

        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
    }
}

// Funcao para liberar memoria
void liberarMemoria(Territorio* mapa) {

    free(mapa);

    printf("\nMemoria liberada com sucesso!\n");
}

int main() {

    Territorio* mapa;

    int quantidade;

    int atacante;
    int defensor;

    int fimDeJogo = 0;

    srand(time(NULL));

    printf("============================================\n");
    printf("        JOGO WAR - NIVEL AVENTUREIRO\n");
    printf("============================================\n");

    // Quantidade de territorios
    printf("\nQuantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);

    // Validacao
    if(quantidade < 2) {

        printf("\nQuantidade invalida!\n");

        return 1;
    }

    // Alocacao dinamica
    mapa = (Territorio*)
           calloc(quantidade,
           sizeof(Territorio));

    // Verifica erro
    if(mapa == NULL) {

        printf("\nErro ao alocar memoria!\n");

        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa,
                         quantidade);

    // Loop principal
    while(fimDeJogo == 0) {

        exibirMapa(mapa,
                   quantidade);

        printf("--- FASE DE ATAQUE ---\n");

        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ",
               quantidade);

        scanf("%d",
              &atacante);

        // Sair do jogo
        if(atacante == 0) {

            break;
        }

        printf("Escolha o territorio defensor (1 a %d): ",
               quantidade);

        scanf("%d",
              &defensor);

        // Ajuste indices
        atacante--;
        defensor--;

        // Validacoes
        if(atacante < 0 ||
           atacante >= quantidade ||
           defensor < 0 ||
           defensor >= quantidade) {

            printf("\nTerritorio invalido!\n");
        }
        else if(atacante == defensor) {

            printf("\nUm territorio nao pode atacar ele mesmo!\n");
        }
        else {

            atacar(&mapa[atacante],
                    &mapa[defensor]);

            // Verifica vencedor
            if(verificarVencedor(mapa,
                                 quantidade)) {

                exibirMapa(mapa,
                           quantidade);

                printf("\n=====================================\n");
                printf("           FIM DA GUERRA\n");
                printf("=====================================\n");

                printf("\nO Exercito %s dominou todos os territorios!\n",
                       mapa[0].cor);

                printf("VITORIA TOTAL DO EXERCITO %s!\n",
                       mapa[0].cor);

                fimDeJogo = 1;
            }
        }

        // Pausa do turno
        if(fimDeJogo == 0) {

            pausar();
        }
    }

    // Libera memoria
    liberarMemoria(mapa);

    return 0;
}