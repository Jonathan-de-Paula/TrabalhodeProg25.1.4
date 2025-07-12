#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int m, n;
    printf("Digite o numero de linhas: ");
    scanf("%d", &m);
    printf("Digite o numero de colunas: ");
    scanf("%d", &n);
    int matriz[m][n];
    printf("Digite os elementos da matriz:\n");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            matriz[i][j] = rand() % 2; 
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
}}