#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct node {
	int vertex;
	struct node* next;
};

struct Graph {
	int numVertices;
	struct node** adjLists;
};

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

struct Graph* sortAdjacencyList(struct Graph* graph) {
	int N = graph->numVertices;
	for (int i = 0; i < N; i++) {
		int count = 0;
		struct node* temp = graph->adjLists[i];
		while (temp != NULL) {
			count++;
			temp = temp->next;
		}

		int* vertices = (int*)malloc(count * sizeof(int));
		temp = graph->adjLists[i];;
		int index = 0;
		while (temp != NULL) {
			vertices[index++] = temp->vertex;
			temp = temp->next;
		}

		qsort(vertices, count, sizeof(int), compare);

		temp = graph->adjLists[i];
		index = 0;
		while (temp != NULL) {
			temp->vertex = vertices[index++];
			temp = temp->next;
		}

		free(vertices);
	}
	return graph;
}

struct node* createNode(int v) {
	struct node* newNode = (node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createAGraph(int vertices) {
	struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;

	graph->adjLists = (node**)malloc(vertices * sizeof(struct node*));

	for (int i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
	}

	return graph;
}

void addEdge(struct Graph* graph, int s, int d) {
	struct node* temp = graph->adjLists[s];
	while (temp) {
		if (temp->vertex == d) {
			return; 
		}
		temp = temp->next;
	}

	struct node* newNode = createNode(d);
	newNode->next = graph->adjLists[s];
	graph->adjLists[s] = newNode;

	temp = graph->adjLists[d];
	while (temp) {
		if (temp->vertex == s) {
			return;
		}
		temp = temp->next;
	}

	newNode = createNode(s);
	newNode->next = graph->adjLists[d];
	graph->adjLists[d] = newNode;
}


struct Graph* edges(int** G, int size) {
	struct Graph* graph = createAGraph(size);

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (G[i][j] == 1) {
				addEdge(graph, i, j);
			}
		}
	}
	sortAdjacencyList(graph);
	return graph;
}

void printGraph(struct Graph* graph) {
	for (int v = 0; v < graph->numVertices; v++) {
		struct node* temp = graph->adjLists[v];
		printf("\nVertex %d: ", v+1);
		while (temp) {
			printf("%d -> ", temp->vertex + 1);
			temp = temp->next;
		}
		printf("\n");
	}
	printf("\n");
}



int** createG(int size) {
	int** G = NULL;
	G = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		G[i] = (int*)malloc(size * sizeof(int));
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			G[i][j] = rand() % 2;
			if (i == j) G[i][j] = 0;
			G[j][i] = G[i][j];
		}
	}
	return G;
}

void printG(int** G, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}



void DFS_mat(int** G, int N, int* NUM, int v) {
    NUM[v] = 1;
    printf("%d ", v+1);

    for (int i = 0; i < N; i++) {
        if (G[v][i] == 1 && NUM[i] == 0) {
            DFS_mat(G, N, NUM, i);
        }
    }
}

void DFS_mat_st(int** G, int N, int* NUM, int v) {
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

void DFS_adj(struct Graph* graph, int N, int* NUM, int v) {
    NUM[v] = 1;
    printf("%d ", v + 1);

    struct node* temp = graph->adjLists[v];
    while (temp != NULL) {
        if (NUM[temp->vertex] == 0) {
            DFS_adj(graph, N, NUM, temp->vertex);
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

	int** G1 = NULL;
	G1 = createG(N);
	printf("Матрица смежности:\n");
	printG(G1, N);

	int* NUM = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) {
		NUM[i] = 0;
	}
	printf("Результат обхода в глубину (матрица):\n");
	for (int i = 0; i < N; i++) {
		if (NUM[i] == 0) {
			DFS_mat(G1, N, NUM, i);
		}
	}

	for (int i = 0; i < N; i++) {
		NUM[i] = 0;
	}
	printf("\nРезультат обхода в глубину (матрица, стек):\n");
	for (int i = 0; i < N; i++) {
		if (NUM[i] == 0) {
			DFS_mat_st(G1, N, NUM, i);
		}
	}

	printf("\nСписок смежности:");
	struct Graph* graph1 = edges(G1, N);
	printGraph(graph1);


    for (int i = 0; i < N; i++) {
        NUM[i] = 0;
    }
    printf("Результат обхода в глубину (список смежности):\n");
    for (int i = 0; i < N; i++) {
        if (NUM[i] == 0) {
            DFS_adj(graph1, N, NUM, i);
        }
    }
	printf("\n");
}
//совм часть с матрицей и списком смежности, т.е спис смеж формир по матр и формир обх по матр, потом 
//