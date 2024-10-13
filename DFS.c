#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

struct Node* createNode(int data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0; // Initialize all vertices as not visited
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}


void DFSRecursive(struct Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjLists[vertex];
    while (temp) {
        int connectedVertex = temp->data;
        if (!graph->visited[connectedVertex]) {
            DFSRecursive(graph, connectedVertex);
        }
        temp = temp->next;
    }
}


void DFSIterative(struct Graph* graph, int startVertex) {
    int stack[100], top = -1;
    stack[++top] = startVertex;
    graph->visited[startVertex] = 1;

    while (top != -1) {
        int vertex = stack[top--];
        printf("%d ", vertex);

        struct Node* temp = graph->adjLists[vertex];
        while (temp) {
            int connectedVertex = temp->data;
            if (!graph->visited[connectedVertex]) {
                stack[++top] = connectedVertex;
                graph->visited[connectedVertex] = 1;
            }
            temp = temp->next;
        }
    }
}


int main() {
    int vertices = 5;
    struct Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("DFS Recursive: ");
    DFSRecursive(graph, 0);

    for (int i = 0; i < vertices; i++) {
        graph->visited[i] = 0;
    }

    printf("\nDFS Iterative: ");
    DFSIterative(graph, 0);

    return 0;
}
