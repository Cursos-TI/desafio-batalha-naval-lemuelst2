#include <stdio.h>
#include <string.h>

#define TAM 10
#define TAM_HAB 5 // tamanho das matrizes de habilidade (5x5)

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0) printf(" ~ ");     // água
            else if (tabuleiro[i][j] == 3) printf(" N "); // navio
            else if (tabuleiro[i][j] == 5) printf(" * "); // área de habilidade
        }
        printf("\n");
    }
}

// Posiciona um navio horizontal
void posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (coluna + 2 < TAM) {
        for (int i = 0; i < 3; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    }
}

// Posiciona um navio vertical
void posicionarNavioVertical(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + 2 < TAM) {
        for (int i = 0; i < 3; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

// Posiciona navio na diagonal principal (↘)
void posicionarNavioDiagonalPrincipal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + 2 < TAM && coluna + 2 < TAM) {
        for (int i = 0; i < 3; i++) {
            tabuleiro[linha + i][coluna + i] = 3;
        }
    }
}

// Posiciona navio na diagonal secundária (↙)
void posicionarNavioDiagonalSecundaria(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + 2 < TAM && coluna - 2 >= 0) {
        for (int i = 0; i < 3; i++) {
            tabuleiro[linha + i][coluna - i] = 3;
        }
    }
}

// Cria uma matriz de habilidade em cone
void criarHabilidadeCone(int habilidade[TAM_HAB][TAM_HAB]) {
    memset(habilidade, 0, sizeof(int) * TAM_HAB * TAM_HAB);

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Cria uma matriz de habilidade em cruz
void criarHabilidadeCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    memset(habilidade, 0, sizeof(int) * TAM_HAB * TAM_HAB);

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Cria uma matriz de habilidade em octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    memset(habilidade, 0, sizeof(int) * TAM_HAB * TAM_HAB);

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Aplica a matriz de habilidade no tabuleiro a partir de um ponto de origem
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linhaTabuleiro = origemLinha - offset + i;
            int colunaTabuleiro = origemColuna - offset + j;

            if (linhaTabuleiro >= 0 && linhaTabuleiro < TAM &&
                colunaTabuleiro >= 0 && colunaTabuleiro < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTabuleiro][colunaTabuleiro] != 3) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Posiciona os navios
    posicionarNavioHorizontal(tabuleiro, 0, 0);   // canto superior esquerdo
    posicionarNavioVertical(tabuleiro, 4, 4);     // meio
    posicionarNavioDiagonalPrincipal(tabuleiro, 6, 0); // diagonal ↘
    posicionarNavioDiagonalSecundaria(tabuleiro, 6, 9); // diagonal ↙

    // Matrizes de habilidades
    int habilidadeCone[TAM_HAB][TAM_HAB];
    int habilidadeCruz[TAM_HAB][TAM_HAB];
    int habilidadeOctaedro[TAM_HAB][TAM_HAB];

    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    // Aplicação das habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, 2, 5);       // centro superior
    aplicarHabilidade(tabuleiro, habilidadeCruz, 5, 5);       // meio
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 8, 8);   // canto inferior direito

    // Exibe o resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}