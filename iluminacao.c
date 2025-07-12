#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int m, n;
    float R;
    printf("Digite o numero de linhas:");
    scanf("%d", &m);
    printf("Digite o numero de colunas: ");
    scanf("%d", &n);
    printf("Digite o valor do R: ");
    scanf("%f", &R);
    printf("Digite os elementos da matriz:\n");
    printf("%d %d \n", m, n);
    printf("%.1f \n",R);
    int matriz[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = rand() % 2;
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}
