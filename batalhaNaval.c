#include <stdio.h>

#define TAM 10
#define TAM_NAVIO 3
#define NAVIO 3
#define AGUA 0

// Função para verificar se é possível posicionar o navio sem ultrapassar o tabuleiro ou sobrepor
int pode_posicionar(int tabuleiro[TAM][TAM], int linha, int coluna, int dir_linha, int dir_coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i * dir_linha;
        int c = coluna + i * dir_coluna;

        if (l < 0 || l >= TAM || c < 0 || c >= TAM) {
            return 0; // Fora dos limites
        }
        if (tabuleiro[l][c] != AGUA) {
            return 0; // Já ocupado
        }
    }
    return 1;
}

// Função para posicionar o navio na direção desejada
void posicionar_navio(int tabuleiro[TAM][TAM], int linha, int coluna, int dir_linha, int dir_coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i * dir_linha;
        int c = coluna + i * dir_coluna;
        tabuleiro[l][c] = NAVIO;
    }
}

// Função para exibir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAM][TAM]) {
    printf("   ");
    for (int c = 0; c < TAM; c++) {
        printf("%2d ", c);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Navios posicionados diretamente (linha e coluna fixos)
    // Navio 1 - Horizontal (linha 1, coluna 2 → 3 casas para direita)
    if (pode_posicionar(tabuleiro, 1, 2, 0, 1)) {
        posicionar_navio(tabuleiro, 1, 2, 0, 1);
    }

    // Navio 2 - Vertical (linha 5, coluna 4 → 3 casas para baixo)
    if (pode_posicionar(tabuleiro, 5, 4, 1, 0)) {
        posicionar_navio(tabuleiro, 5, 4, 1, 0);
    }

    // Navio 3 - Diagonal principal (linha 0, coluna 0 → diagonal \)
    if (pode_posicionar(tabuleiro, 0, 0, 1, 1)) {
        posicionar_navio(tabuleiro, 0, 0, 1, 1);
    }

    // Navio 4 - Diagonal secundária (linha 0, coluna 9 → diagonal /)
    if (pode_posicionar(tabuleiro, 0, 9, 1, -1)) {
        posicionar_navio(tabuleiro, 0, 9, 1, -1);
    }

    // Exibir o tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}