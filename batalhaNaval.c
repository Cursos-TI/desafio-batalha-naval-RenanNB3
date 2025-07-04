#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para a função abs

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 3

// Verifica se é possível posicionar o navio
bool podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, bool diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (diagonal ? i * direcao : (direcao == 1 ? i : 0));
        int c = coluna + (diagonal ? i * direcao : (direcao == 0 ? i : 0));

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return false;
        if (tabuleiro[l][c] != 0)
            return false;
    }
    return true;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, bool diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (diagonal ? i * direcao : (direcao == 1 ? i : 0));
        int c = coluna + (diagonal ? i * direcao : (direcao == 0 ? i : 0));
        tabuleiro[l][c] = 3;
    }
}

// Gera uma matriz em forma de cone
void gerarCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= (TAMANHO_HABILIDADE - 1) / 2 - i && j <= (TAMANHO_HABILIDADE - 1) / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera uma matriz em forma de cruz
void gerarCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}

// Gera uma matriz com forma de octaedro
void gerarOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

// Adiciona a habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int l = origemLinha - offset + i;
            int c = origemColuna - offset + j;

            if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[l][c] != 3) {
                    tabuleiro[l][c] = 5;
                }
            }
        }
    }
}

// Exibe o tabuleiro no console
void mostrarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro (0=Água, 3=Navio, 5=Área atingida):\n\n");
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

    // Nível Mestre - Gerando habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplicando habilidades

    // Cone com centro em (1,2)
    aplicarHabilidade(tabuleiro, cone, 1, 2);
    
    // Cruz com centro em (5,5)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);        

     // Octaedro com centro em (7,7)
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);   

    // Mostrando o tabuleiro final
    mostrarTabuleiro(tabuleiro);

    return 0;
}
