// Implementação de fila vem de https://www.geeksforgeeks.org/c/queue-in-c/
// 

typedef struct {
    int items[101];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue* q)
{
    q->front = -1;
    q->rear = 0;
}

bool isEmpty(Queue* q) { return (q->front == q->rear - 1); }

void enqueue(Queue* q, int value)
{
    q->items[q->rear] = value;
    q->rear++;
}

void dequeue(Queue* q)
{
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    q->front++;
}

int peek(Queue* q)
{
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1; // return some default value or handle
                   // error differently
    }
    return q->items[q->front + 1];
}


// FUNÇÃO PRINCIPAL
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    Queue q;
    initializeQueue(&q);

    // Vetor que define se um vértice já foi visitado
    int* vis = malloc(sizeof(int) * graphSize);
    for(int i = 0; i < graphSize; i++) vis[i] = 0;

    // Vetor para armazenar a camada de cada vértice
    int* layer = malloc(sizeof(int) * graphSize);

    for(int i = 0; i < graphSize; i++){
        if(vis[i]) continue;
        enqueue(&q, i);
        int currLayer = 0;
        layer[i] = 0;
        vis[i] = 1;

        while(!isEmpty(&q)){
            int n = peek(&q);
            dequeue(&q);
            int v;

            // Retornamos falso se encontrado uma aresta(que seria descartada na árvore) entre vértices da mesma camada
            for(v = 0; v < graphColSize[n]; v++){
                if(vis[graph[n][v]]){   
                    if (layer[n] == layer[graph[n][v]]) return false;
                    continue;
                }
                layer[graph[n][v]] = layer[n] + 1;  // Armazenada a camada do vértice novo
                vis[graph[n][v]] = 1;
                enqueue(&q, graph[n][v]);
            }
        }
    }
    return true;
}
