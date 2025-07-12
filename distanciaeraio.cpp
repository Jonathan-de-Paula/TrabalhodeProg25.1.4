//
// Created by Leticia on 12/07/2025.
//
#include <stdio.h>
#include <math.h>

// Função que calcula a distância euclidiana
float distancia(float e, float f, float g, float h) {
    float valorf, valoriu, valorjv, valoriuiu, valorjvjv, valorsoma;
    valoriu = e - g;
    valorjv = f - h;
    valoriuiu =  valoriu * valoriu;
    valorjvjv = valorjv * valorjv;
    valorsoma = valoriuiu + valorjvjv;
    valorf = sqrt(valorsoma);
    //return sqrt((e - g) * (e - g) + (f - h) * (f - h));
    return valorf;
}

int main() {
    float i, j, u, v;
    float R;

    printf("Insira o valor de i: ");
    scanf("%f", &i);

    printf("Insira o valor de j: ");
    scanf("%f", &j);

    printf("Insira o valor de u: ");
    scanf("%f", &u);

    printf("Insira o valor de v: ");
    scanf("%f", &v);

    printf("Insira o valor do raio R: ");
    scanf("%f", &R);

    float d = distancia(i, j, u, v);
    printf("Distancia euclidiana : %.2f\n", d);

    if (d <= R) {
        printf("A distancia esta dentro do raio.\n");
    } else {
        printf("A distancia esta fora do raio.\n");
    }

}