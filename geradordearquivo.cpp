//
// Created by Leticia on 12/07/2025.
//
#include <stdio.h>
#include <math.h>

int main(){
    int m, n;
    float R;
    FILE *fp;
    fp = fopen("matrizeszes.txt", "w"); /// Abrir o arquivo para escrita

    if (fp == NULL) {
        printf("Error opening file");
        return 0; ///
    }
    printf("Digite o numero de linhas: ");
    scanf("%d", &m);
    printf("Digite o numero de colunas: ");
    scanf("%d", &n);
    int matrix[m][n];
    printf("Digite o valor do R: ");
    scanf("%f", &R);
    printf("Digite os elementos da matriz:\n");
    fprintf(fp, "%d %d \n", m, n);
    fprintf(fp, "%.1f \n",R);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 2; /// Gera números pseudo aleatorios entre 0 e 1
            fprintf(fp,"%d ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp); /// Fechar o arquivo
    printf("Matriz escrita no arquivo com sucesso!\n");
}