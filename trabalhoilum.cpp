//
// Created by joaoggn on 12/07/25.
//
#include <stdio.h>
#include <math.h>
int main() {
    int m, n;
    double R;
    int luminum = 0, totlu = 0, totpub = 0, totil = 0;

    /// Abrindo nosso arquivinho
    FILE *fp = fopen("entrada.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    /// Lendo m, n e raio
    fscanf(fp, "%d %d", &m, &n);
    fscanf(fp, "%lf", &R);

    int G[m][n], X[m][n], iluminado[m][n];

    /// Leitura da matriz G e preenchimento da matriz X pelo usuário
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &G[i][j]);

            iluminado[i][j] = 0;

            if (G[i][j] == 0) {
                X[i][j] = 0;
                printf("G[%d][%d] é 0 (obstáculo), portanto nada de luminárias.\n", i, j);
            } else {
                printf("Existe luminária na célula [%d][%d]? (1 = sim, 0 = não): ", i, j);
                scanf("%d", &X[i][j]);

                /// Validação
                if (X[i][j] != 0 && X[i][j] != 1) {
                    printf("⚠️ Valor inválido! Use 0 ou 1.\n");
                    fclose(fp);
                    return 1;
                }
                ///Contagem de luminárias ja existentes
                if (X[i][j] == 1) {
                    luminum++;
                }
            }
        }
    }

    fclose(fp); /// Fechar leitura

    /// Marcar as células iluminadas com base nas luminárias e raio R
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (X[i][j] == 1) {
                for (int u = 0; u < m; u++) {
                    for (int v = 0; v < n; v++) {
                        double dist = sqrt((i - u) * (i - u) + (j - v) * (j - v));
                        if (dist <= R) {
                            iluminado[u][v] = 1;
                        }
                    }
                }
            }
        }
    }

    /// Criar arquivo de saída
    FILE *saida = fopen("saida.txt", "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo de saída!\n");
        return 1;
    }

    /// Gerar saída visual e calcular métricas
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (X[i][j] == 1) {
                fprintf(saida, "L ");
                totlu++;
            } else if (G[i][j] == 0) {
                fprintf(saida, "0 ");
            } else if (iluminado[i][j] == 1) {
                fprintf(saida, "* ");
                totil++;
            } else {
                fprintf(saida, "1 "); // Pública não iluminada
            }

            if (G[i][j] == 1) {
                totpub++;
            }
        }
        fprintf(saida, "\n");
    }

    fclose(saida); /// Fechar arquivo de saída

    /// Calcular métricas
    float cobertura = (totpub > 0) ? (100.0 * totil / totpub) : 0;
    float eficiencia = (totlu > 0) ? (1.0 * totil / totlu) : 0;

    /// Exibir métricas no terminal
    printf("\n--- Resultados ---\n");
    printf("Total de luminárias instaladas: %d\n", totlu);
    printf("Cobertura de áreas públicas: %.0f%%\n", cobertura);
    printf("Eficiência média: %.1f células públicas por luminária\n", eficiencia);
    printf("Arquivo gerado: saida.txt\n");

    return 0;
}