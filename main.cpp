#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void createG(int** G, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int edge = rand() % 2;
            G[i][j] = edge;
            G[j][i] = edge;
        }
    }

    for (int i = 0; i < N; i++) {
        G[i][i] = 0;
    }
}

void printG(int** G, int N) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

void DFS(int** G, int N, int* NUM, int v) {
    int* stack = (int*)malloc(N * sizeof(int));
    int top = -1;

    stack[++top] = v;

    while (top != -1) {
        int vec = stack[top--];
        if (NUM[vec] == 0) {
            NUM[vec] = 1;
            printf("%d ", vec + 1);
        }
        for (int i = N - 1; i >= 0; i--) {
            if (G[vec][i] == 1 && NUM[i] == 0) {
                stack[++top] = i;
            }
        }
    }
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;

    printf("Введите количество вершин в графе: ");
    scanf("%d", &N);
    int** G = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        G[i] = (int*)malloc(N * sizeof(int));
    }
    createG(G, N);
    printG(G, N);

    int* NUM = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        NUM[i] = 0;
    }

    printf("\nРезультат обхода в глубину:\n");
    for (int i = 0; i < N; i++) {
        if (NUM[i] == 0) {
            DFS(G, N, NUM, i);
        }
    }
}