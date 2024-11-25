#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


typedef struct Node {
    int vertex;
    struct Node* next;
} Node;



void createAdjacencyList(Node** adjList, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int edge = rand() % 2;
            if (edge == 1) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = j;
                newNode->next = adjList[i];
                adjList[i] = newNode;

                newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = i;
                newNode->next = adjList[j];
                adjList[j] = newNode;
            }
        }
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void sortAdjacencyList(Node** adjList, int N) {
    for (int i = 0; i < N; i++) {
        int count = 0;
        Node* temp = adjList[i];
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }

        int* vertices = (int*)malloc(count * sizeof(int));
        temp = adjList[i];
        int index = 0;
        while (temp != NULL) {
            vertices[index++] = temp->vertex;
            temp = temp->next;
        }

        qsort(vertices, count, sizeof(int), compare);

        temp = adjList[i];
        index = 0;
        while (temp != NULL) {
            temp->vertex = vertices[index++];
            temp = temp->next;
        }

        free(vertices);
    }
}

void printAdjacencyList(Node** adjList, int N) {
    printf("Список смежности:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i + 1);
        Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d -> ", temp->vertex + 1);
            temp = temp->next;
        }
        printf("\n");
    }
}

void DFS(Node** adjList, int N, int* NUM, int v) {
    NUM[v] = 1;
    printf("%d ", v + 1);

    Node* temp = adjList[v];
    while (temp != NULL) {
        if (NUM[temp->vertex] == 0) {
            DFS(adjList, N, NUM, temp->vertex);
        }
        temp = temp->next;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;

    printf("Введите количество вершин в графе: ");
    scanf("%d", &N);

    Node** adjList = (Node**)malloc(N * sizeof(Node*));
    for (int i = 0; i < N; i++) {
        adjList[i] = NULL;
    }

    createAdjacencyList(adjList, N);
    sortAdjacencyList(adjList, N);
    printAdjacencyList(adjList, N);

    int* NUM = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        NUM[i] = 0;
    }
    printf("\nРезультат обхода в глубину:\n");
    for (int i = 0; i < N; i++) {
        if (NUM[i] == 0) {
            DFS(adjList, N, NUM, i);
        }
    }
}