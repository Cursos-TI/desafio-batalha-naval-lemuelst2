#include <stdio.h>

// Constantes para dimensões
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

int main() {
    // ------------------- INICIALIZAÇÃO DO TABULEIRO -------------------
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água (valor 0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // ------------------- POSICIONAMENTO DOS NAVIOS -------------------

    // Navio Horizontal
    int navioHorizontal[TAMANHO_NAVIO] = {3, 3, 3};
    int linhaH = 2;   // Linha inicial do navio horizontal
    int colunaH = 4;  // Coluna inicial

    // Validação: verificar se cabe horizontalmente no tabuleiro
    if (colunaH + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
        }
    } else {
        printf("Erro: Navio horizontal não cabe no tabuleiro!\n");
        return 1;
    }

    // Navio Vertical
    int navioVertical[TAMANHO_NAVIO] = {3, 3, 3};
    int linhaV = 5;   // Linha inicial do navio vertical
    int colunaV = 7;  // Coluna inicial

    // Validação: verificar se cabe verticalmente no tabuleiro e não sobrepõe outro navio
    if (linhaV + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
            }
        } else {
            printf("Erro: Navio vertical sobrepõe outro navio!\n");
            return 1;
        }

    } else {
        printf("Erro: Navio vertical não cabe no tabuleiro!\n");
        return 1;
    }

    // ------------------- EXIBIÇÃO DO TABULEIRO -------------------
    printf("Tabuleiro Batalha Naval (0 = água, 3 = navio):\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}