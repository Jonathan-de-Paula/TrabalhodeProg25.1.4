#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//mensagens de erro =P -john
void errorMessage(int a)
{
    if (a == 1)
    {
        printf("A matriz está fora do limite do mapa.");
    }
    if (a == 2)
    {
        printf("A matriz deve conter somente 1s e 0s");
    }
    if (a == 3)
    {
        printf("placeholder");
    }
}

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int inBoard(int x3, int y3, int m, int n)
{
    if (x3 >= 0 && x3 < m && y3 >= 0 && y3 < n)
    {
        return 1;
    }
    else
    {
        errorMessage(1);
        return 0;
    }
}
int qtdteoiluminada (int linhalu, int colunalu, double R, int m, int n, int G[m][n], int iluminacao[m][n])
{int countlumin = 0; //ver se é melhor arrendondar pra baixo ou para cima;
if (G[m][n] == 1){ //ve se e um local publico sem obstaculo
    for (int i = linhalu-(int)R; i <= linhalu+(int)R; i++) //pega a posição onde ele esta + e - o raio para achar as partes afetadas
    {
        for (int j = colunalu-(int)R; j <= colunalu+(int)R; j++)
        {
            if (inBoard(i,j))
            {
                if ((G[i][j] == 1) && (iluminacao[i][j] == 0))
                {
                    float dist = distance(linhalu,colunalu,i,j);
                    if (dist <= R)
                    {
                        countlumin++; //contador de quantas posições da matriz serao acessas se colocar uma luz ali para depois acharmos o maior para minimizar as luzes
                    }
                }
            }
        }
    }
}
    return countlumin;
}
void iluminar(int linhalu, int colunalu, double R, int m, int n, int G[m][n],int iluminacao[m][n])
{
    for (int i = linhalu-(int)R; i <= linhalu+(int)R; i++)
    {
        for (int j = colunalu-(int)R; j <= colunalu+(int)R; j++)
        {
            if (inBoard(i,j)) // ve se ta na matriz
            {
                if (G[i][j] == 1) //ve se e um local publico (sem obstaculo)
                {
                    float dist = distance(linhalu,colunalu,i,j); //puxa a funçao distancia
                    if (dist <= R)
                    {
                         iluminacao[m][n]= 1; // colocamos uma luminaria onde antes foi apenas testado
                    }
                }
            }
        }
    }
}
int elementossemluz( int m, int n, int G[m][n],int iluminacao[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((G[i][j] == 1) && (iluminacao[i][j]==0))
            {
              return 1;
            }

        }
   }
    return 0;
}
////proxima parte funções métricas!! fui dar uma descansada :) (leti!)

