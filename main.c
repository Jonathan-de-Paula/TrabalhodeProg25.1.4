#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024


// função para calcular a distância euclidiana
double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int yesConfirm(char word[]) {
    if ((strcmp(word, "sim") == 0) || (strcmp(word, "SIM") == 0) || (strcmp(word, "Sim") == 0) || (
            strcmp(word, "S") == 0) || (strcmp(word, "s") == 0)) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int m, n, efficiencyMode;
    double R;
    int Contagem_luminárias_existentes = 0, Contagem_células_iluminadas = 0, Contagem_células = 0;
    char yesOrNo[BUFFER_SIZE];

    /// Abrindo nosso arquivo
    FILE *fp = fopen("entrada.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    /// Lendo m, n e raio do arquivo entrada.txt
    fscanf(fp, "%d %d", &m, &n);
    fscanf(fp, "%lf", &R);

    printf("Deseja que o posicionamento priorize eficiencia a totalidade? (S/N)\n> ");
    fgets(yesOrNo, BUFFER_SIZE, stdin);
    yesOrNo[strcspn(yesOrNo, "\n")] = '\0'; // remove '\n' do final
    efficiencyMode = yesConfirm(yesOrNo);
    // Remove o '\n' do final

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
                /// Ver se a matriz está incorreta
                return 1;
            }
            X[i][j] = 0;
            iluminado[i][j] = 0;
            if (G[i][j] == 1) {
                Contagem_células_iluminadas++;
                ///Adiciona +1 na contagem de areas publicas
            }
        }
    }

    fclose(fp); /// Fechar leitura

    /// algoritmo para colocar luminárias automaticamente:
    /// essa parte pode ser complexa.
    /// o código vai utilizar dados como o raio, local iluminado e area publica
    /// e realizar um loop que vai testar qual lugar a luminaria vai ser mais eficiente
    while (1) {
        int melhor_i = -1, melhor_j = -1, melhor_impacto = 0;

        /// Analisa todas as posições possíveis para colocar luminária
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (G[i][j] == 0) continue; // Nada de poste no obstáculo

                int impacto = 0;

                /// Conta quantas células públicas essa posição iluminaria
                for (int u = 0; u < m; u++) {
                    for (int v = 0; v < n; v++) {
                        double dist = distance(i, j, u, v);
                        if ((dist <= R) && (G[u][v] == 1) && (iluminado[u][v] == 0)) {
                            impacto++;
                        }
                    }
                }
                if (efficiencyMode == 0) {
                    /// Guarda a melhor posição até agora
                    if (impacto > melhor_impacto) {
                        melhor_impacto = impacto;
                        melhor_i = i;
                        melhor_j = j;
                    }
                }
                if (efficiencyMode == 1) {
                    if (impacto > melhor_impacto && impacto > 1) {
                        melhor_impacto = impacto;
                        melhor_i = i;
                        melhor_j = j;
                    }
                }
            }
        }

        /// Se nenhuma posição pode nós ajudar mais, o loop é encerrado
        if (melhor_impacto == 0) break;

        /// Instala uma luminária na melhor posição
        X[melhor_i][melhor_j] = 1;
        Contagem_luminárias_existentes++;

        /// Marcar as células já iluminadas com base nas luminárias supracriadas e no raio R
        for (int u = 0; u < m; u++) {
            for (int v = 0; v < n; v++) {
                double dist = distance(melhor_i, melhor_j, u, v);
                if (dist <= R && G[u][v] == 1 && iluminado[u][v] == 0) {
                    iluminado[u][v] = 1;
                    Contagem_células++;
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
                fprintf(saida, "L "); /// Luminaria existente
            } else if (G[i][j] == 0) {
                fprintf(saida, "0 ");
            } else if (iluminado[i][j] == 1) {
                /// Célula iluminada
                fprintf(saida, "* ");
            } else {
                fprintf(saida, "1 "); /// Pública não iluminada
            }
        }
        fprintf(saida, "\n");
    }

    fclose(saida); /// Fechar arquivo de saída

    /// Calcular métricas
    /// a sintaxe abaixo funciona semelhante a um IF seguido de um ELSE
    float cobertura = (Contagem_células_iluminadas > 0) ? (100.0f * Contagem_células / Contagem_células_iluminadas) : 0;
    float eficiencia = (Contagem_luminárias_existentes > 0)
                           ? ((float) Contagem_células / Contagem_luminárias_existentes)
                           : 0;

    /// Exibir métricas no terminal
    printf("\n--- Resultados ---\n");
    printf("Total de luminarias instaladas: %d\n", Contagem_luminárias_existentes);
    printf("Cobertura de areas publicas: %.0f%%\n", cobertura);
    printf("Eficiencia media: %.1f celulas publicas por luminaria\n", eficiencia);
    printf("Arquivo gerado: saida.txt\n");

    return 0;
}
