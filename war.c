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
// PRÁTICA: Jogo WAR em C - Nível Novato
// OBJETIVO DESTA PARTE:
// Criar uma struct chamada Territorio que armazenará informações como nome, cor do exército
// e quantidade de tropas. O sistema permitirá o cadastro de 5 territórios e exibirá seus
// dados logo após o preenchimento.
//
// ======================================================================

#include <stdio.h>
#include <string.h>

// Criacao da struct Territorio
// Ela armazena:
// nome do territorio
// cor do exercito
// quantidade de tropas

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {

    // Vetor para armazenar 5 territorios
    struct Territorio territorios[5];

    int i;

    printf("========================================================\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
    printf("========================================================\n\n");

    // Cadastro dos territorios
    for(i = 0; i < 5; i++) {

        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        // Entrada do nome
        printf("Nome do Territorio: ");
        scanf("%s", territorios[i].nome);

        // Entrada da cor do exercito
        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%s", territorios[i].cor);

        // Entrada do numero de tropas
        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    printf("Cadastro inicial concluido com sucesso!\n\n");

    // Exibicao dos dados cadastrados
    printf("========================================\n");
    printf("        MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("========================================\n\n");

    // Percorre o vetor exibindo os dados
    for(i = 0; i < 5; i++) {

        printf("TERRITORIO %d:\n", i + 1);

        printf(" - Nome: %s\n", territorios[i].nome);

        printf(" - Dominado por: Exercito %s\n", territorios[i].cor);

        printf(" - Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}