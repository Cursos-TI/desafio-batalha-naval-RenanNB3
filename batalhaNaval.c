#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Verifica se é possível posicionar o navio
bool podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, bool diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (diagonal ? i * direcao : (direcao == 1 ? i : 0));
        int c = coluna + (diagonal ? i * direcao : (direcao == 0 ? i : 0));

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) return false;
        if (tabuleiro[l][c] != 0) return false;
    }
    return true;
}

// Posicionando o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, bool diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (diagonal ? i * direcao : (direcao == 1 ? i : 0));
        int c = coluna + (diagonal ? i * direcao : (direcao == 0 ? i : 0));
        tabuleiro[l][c] = 3;
    }
}

// Mostrando o tabuleiro
void mostrarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro Batalha Naval (0 = Água, 3 = Navio):\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};
    // Nível Novato - Posicionamento dos Navios
    // Tamanho dos Navios
    int navio1[TAMANHO_NAVIO] = {3, 3, 3}; 
    int navio2[TAMANHO_NAVIO] = {3, 3, 3};

    // Coordenadas dos Navios
    int linhaNavio1 = 2;
    int colunaNavio1 = 4;
    int linhaNavio2 = 5;
    int colunaNavio2 = 7;

    // Navio 1 - horizontal
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaNavio1][colunaNavio1 + i] = navio1[i];
    }

    // Navio 2 - vertical
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaNavio2 + i][colunaNavio2] = navio2[i];
    }
    mostrarTabuleiro(tabuleiro);

    // Nível Aventureiro - Posicionamento Diagonal

    // Navio 3 - Diagonal Principal
    int linha3 = 0, coluna3 = 0;
    if (podePosicionar(tabuleiro, linha3, coluna3, 1, true)) {
        posicionarNavio(tabuleiro, linha3, coluna3, 1, true);
    }

    // Navio 4 - Diagonal Secundária
    int linha4 = 2, coluna4 = 9;
    if (podePosicionar(tabuleiro, linha4, coluna4, -1, true)) {
        posicionarNavio(tabuleiro, linha4, coluna4, -1, true);
    }

    // Exibindo tabuleiro nível aventureiro
    mostrarTabuleiro(tabuleiro);

    return 0;
}
