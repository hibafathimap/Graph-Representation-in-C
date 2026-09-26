#include <stdio.h>
#include <stdlib.h>

#define N 6

char vertices[N] = {'A', 'B', 'C', 'D', 'E', 'F'};
int matrix[N][N] = {0};

struct Node {
    int vertex;
    struct Node *next;
};

struct Node *adj[N] = {NULL};

/* Insert a vertex in alphabetical order */
void insertSorted(int u, int v)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    struct Node **p = &adj[u];

    newNode->vertex = v;

    while (*p != NULL && (*p)->vertex < v)
        p = &(*p)->next;

    newNode->next = *p;
    *p = newNode;
}

/* Add an undirected edge */
void addEdge(int u, int v)
{
    matrix[u][v] = 1;
    matrix[v][u] = 1;

    insertSorted(u, v);
    insertSorted(v, u);
}

/* Display adjacency matrix */
void displayMatrix(void)
{
    int i, j;

    printf("\nADJACENCY MATRIX\n  ");
    for (i = 0; i < N; i++)
        printf("%c ", vertices[i]);

    printf("\n");

    for (i = 0; i < N; i++) {
        printf("%c ", vertices[i]);

        for (j = 0; j < N; j++)
            printf("%d ", matrix[i][j]);

        printf("\n");
    }
}

/* Display adjacency list */
void displayList(void)
{
    int i;
    struct Node *p;

    printf("\nADJACENCY LIST\n");

    for (i = 0; i < N; i++) {
        printf("%c -> ", vertices[i]);

        p = adj[i];

        while (p != NULL) {
            printf("%c -> ", vertices[p->vertex]);
            p = p->next;
        }

        printf("NULL\n");
    }
}

/* BFS using adjacency matrix */
void bfsMatrix(int start)
{
    int visited[N] = {0};
    int queue[N], front = 0, rear = 0;
    int i, u;

    visited[start] = 1;
    queue[rear++] = start;

    printf("MATRIX BFS: ");

    while (front < rear) {
        u = queue[front++];
        printf("%c ", vertices[u]);

        for (i = 0; i < N; i++) {
            if (matrix[u][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");
}

/* DFS using adjacency matrix */
void dfsMatrixUtil(int u, int visited[])
{
    int i;

    visited[u] = 1;
    printf("%c ", vertices[u]);

    for (i = 0; i < N; i++) {
        if (matrix[u][i] && !visited[i])
            dfsMatrixUtil(i, visited);
    }
}

void dfsMatrix(int start)
{
    int visited[N] = {0};

    printf("MATRIX DFS: ");
    dfsMatrixUtil(start, visited);
    printf("\n");
}

/* BFS using adjacency list */
void bfsList(int start)
{
    int visited[N] = {0};
    int queue[N], front = 0, rear = 0;
    int u;
    struct Node *p;

    visited[start] = 1;
    queue[rear++] = start;

    printf("LIST BFS: ");

    while (front < rear) {
        u = queue[front++];
        printf("%c ", vertices[u]);

        p = adj[u];

        while (p != NULL) {
            if (!visited[p->vertex]) {
                visited[p->vertex] = 1;
                queue[rear++] = p->vertex;
            }
            p = p->next;
        }
    }

    printf("\n");
}

/* DFS using adjacency list */
void dfsListUtil(int u, int visited[])
{
    struct Node *p;

    visited[u] = 1;
    printf("%c ", vertices[u]);

    p = adj[u];

    while (p != NULL) {
        if (!visited[p->vertex])
            dfsListUtil(p->vertex, visited);

        p = p->next;
    }
}

void dfsList(int start)
{
    int visited[N] = {0};

    printf("LIST DFS: ");
    dfsListUtil(start, visited);
    printf("\n");
}

/* Search for a vertex label */
int searchVertex(char target, int *count)
{
    int i;

    *count = 0;

    for (i = 0; i < N; i++) {
        (*count)++;

        if (vertices[i] == target)
            return i;
    }

    return -1;
}

int main(void)
{
    int count, result;
    int i;

    addEdge(0, 1);  /* A-B */
    addEdge(0, 2);  /* A-C */
    addEdge(1, 3);  /* B-D */
    addEdge(1, 4);  /* B-E */
    addEdge(2, 5);  /* C-F */
    addEdge(4, 5);  /* E-F */

    displayMatrix();
    displayList();

    printf("\nGRAPH TRAVERSAL\n");
    bfsMatrix(0);
    dfsMatrix(0);
    bfsList(0);
    dfsList(0);

    printf("\nSEARCH FOR E\n");

    result = searchVertex('E', &count);
    printf("Matrix: %s, comparisons = %d\n",
           result != -1 ? "Found" : "Not found", count);

    result = searchVertex('E', &count);
    printf("List: %s, comparisons = %d\n",
           result != -1 ? "Found" : "Not found", count);

    for (i = 0; i < N; i++) {
        struct Node *p = adj[i];

        while (p != NULL) {
            struct Node *temp = p;
            p = p->next;
            free(temp);
        }
    }

    return 0;
}
