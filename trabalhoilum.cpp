//
// Created by joaoggn on 12/07/25.
//
#include <stdio.h>
#include <math.h>
int main() {
    int m, n;
    double radius;
    int totlu = 0, totpub = 0, totil = 0;
    /// Totlu: Contagem de luminárias ja existentes
    /// Totil: Contagem células publicas iluminadas
    /// Totpub: Contagem células publicas

    /// Abrindo nosso arquivinho
    FILE *fp = fopen("entrada.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    /// Lendo m, n e raio do arquivo entrada.txt
    fscanf(fp, "%d %d", &m, &n);
    fscanf(fp, "%lf", &radius);

    int R = ceil(radius);

    int G[m][n], X[m][n], iluminado[m][n];
    /// G: Matriz que indica os espaços públicos e os obstaculos
    /// X: Matriz que indica se o espaço publico tem poste ou não
    /// iluminado: Matriz que indica as celúlas iluminadas

    /// Leitura da matriz G e preenchimento da matriz X
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &G[i][j]);
            if (G[i][j] != 1 && G[i][j] != 0) {
                printf("Matriz inválida");
                /// Ver se o safado ta tentando nos enganar
                return 1;
            }
            X[i][j] = 0;
            iluminado[i][j] = 0;
            if (G[i][j] == 1) {
                totpub++;
                ///Adiciona +1 na contagem de areas publicas
            }
        }
    }

    fclose(fp); /// Fechar leitura

    /// Bendito algoritmo para colocar luminárias automaticamente. Dando uma resumida de leve essa parte é levemente
    /// mais complexa,  Basicamente essa parte do código
    /// vai pegar dados como o raio, local iluminado e area publica, realiza um loop que vai testando qual lugar a luminaria vai ser mais eficiente
    while (1) {
        int melhor_i = -1, melhor_j = -1, melhor_impacto = 0;

        /// Analisa todas as posições possíveis para colocar luminária
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (G[i][j] == 0) continue; // Nada de poste no obstáculo

                int impacto = 0;

                /// Conta quantas células públicas essa posição iluminaria
                for (int u = 0; u < m ; u++) {
                    for (int v = 0; v < n ; v++) {
                        double dist = sqrt((i - u) * (i - u) + (j - v) * (j - v));
                        if ((dist <= R) && (G[u][v] == 1) && (iluminado[u][v] == 0)) {
                            impacto++;
                        }
                    }
                }

                /// Guarda a melhor posição até agora (impacto? EVA reference???)
                if (impacto > melhor_impacto) {
                    melhor_impacto = impacto;
                    melhor_i = i;
                    melhor_j = j;
                }
            }
        }

        /// Se nenhuma posição pode ajudar mais, paramos
        if (melhor_impacto == 0) break;

        /// Instala uma luminária na melhor posição
        X[melhor_i][melhor_j] = 1;
        totlu++;

        /// Marcar as células já iluminadas com base nas luminárias supracriadas (pai sabe palavras difíceis kkkk) e raio R
        for (int u = 0; u < m; u++) {
            for (int v = 0; v < n; v++) {
                double dist = sqrt((melhor_i - u) * (melhor_i - u) + (melhor_j - v) * (melhor_j - v));
                if (dist <= R && G[u][v] == 1 && iluminado[u][v] == 0) {
                    iluminado[u][v] = 1;
                    totil++;
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
                fprintf(saida, "L "); /// Luminaria existindo só na resenha
            } else if (G[i][j] == 0) {
                fprintf(saida, "0 ");
            } else if (iluminado[i][j] == 1) { /// Célula iluminada
                fprintf(saida, "* ");
            } else {
                fprintf(saida, "1 "); /// Pública não iluminada
            }
        }
        fprintf(saida, "\n");
    }

    fclose(saida); /// Fechar arquivo de saída

    /// Calcular métricas
    float cobertura = (totpub > 0) ? (100.0f * totil / totpub) : 0;
    float eficiencia = (totlu > 0) ? ((float)totil / totlu) : 0;

    /// Exibir métricas no terminal
    printf("\n--- Resultados ---\n");
    printf("Total de luminarias instaladas: %d\n", totlu);
    printf("Cobertura de areas publicas: %.0f%%\n", cobertura);
    printf("Eficiencia media: %.1f celulas publicas por luminaria\n", eficiencia);
    printf("Arquivo gerado: saida.txt\n");

    return 0;
}
