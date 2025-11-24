#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_CIDADES 1000
#define MAX_LOCAIS 50
#define INF 1e18

typedef struct {
    int x, y;
} Local;

typedef struct {
    char nome[16];
    int num_locais;
    Local locais[MAX_LOCAIS];
} Cidade;

Cidade cidades[MAX_CIDADES];
int adj[MAX_CIDADES][MAX_CIDADES];
int grau[MAX_CIDADES];
int n;
int mapa_nome_indice[MAX_CIDADES];
char nomes[MAX_CIDADES][16];

double dp[MAX_CIDADES][MAX_LOCAIS];

// Função para calcular distância euclidiana
double distancia(Local a, Local b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

// Função para buscar o índice da cidade pelo nome
int indiceCidade(char *nome) {
    for(int i = 0; i < n; i++) {
        if(strcmp(nomes[i], nome) == 0) return i;
    }
    return -1;
}

// DP sobre árvore
void dfs(int u, int pai) {
    for(int i = 0; i < cidades[u].num_locais; i++) dp[u][i] = 0;

    for(int j = 0; j < grau[u]; j++) {
        int v = adj[u][j];
        if(v == pai) continue;
        dfs(v, u);

        double novo_dp[MAX_LOCAIS];
        for(int i = 0; i < cidades[u].num_locais; i++) {
            novo_dp[i] = 0;
            double soma = 0;
            double melhor = INF;
            for(int k = 0; k < cidades[v].num_locais; k++) {
                double custo = dp[v][k] + distancia(cidades[u].locais[i], cidades[v].locais[k]);
                if(custo < melhor) melhor = custo;
            }
            novo_dp[i] = dp[u][i] + melhor;
        }
        for(int i = 0; i < cidades[u].num_locais; i++) dp[u][i] = novo_dp[i];
    }
}

int main() {
    while(scanf("%d", &n) && n) {
        // Inicializa
        for(int i = 0; i < n; i++) grau[i] = 0;

        for(int i = 0; i < n; i++) {
            scanf("%s %d", nomes[i], &cidades[i].num_locais);
            for(int j = 0; j < cidades[i].num_locais; j++) {
                scanf("%d %d", &cidades[i].locais[j].x, &cidades[i].locais[j].y);
            }
        }

        // Limpa adjacência
        for(int i = 0; i < n; i++) grau[i] = 0;

        // Lê conexões
        for(int i = 0; i < n-1; i++) {
            char nome1[16], nome2[16];
            scanf("%s %s", nome1, nome2);
            int u = indiceCidade(nome1);
            int v = indiceCidade(nome2);
            adj[u][grau[u]++] = v;
            adj[v][grau[v]++] = u;
        }

        // Executa DP começando da cidade 0
        dfs(0, -1);

        // Obtém melhor resposta
        double resposta = INF;
        for(int i = 0; i < cidades[0].num_locais; i++)
            if(dp[0][i] < resposta) resposta = dp[0][i];

        printf("%.1lf\n", resposta);
    }
    return 0;
}
