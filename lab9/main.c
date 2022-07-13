#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MATRIX_SIZE 5000

void Deix(int* matrix, int start, int end, long long shortest[], int used[], int node_count, int parents[], int* ways);
int BadNode(int* start, int* end, long long* length, int node_count);
int BadInput(int nodes, int ribs);
void MatrixInsert(int* matrix, int start, int end, long length);

int main(void)
{   
    int node_count = 0;
    int start = 0;
    int end = 0;
    int rib_count = 0;
    int* matrix = malloc(sizeof(int) * MATRIX_SIZE * (MATRIX_SIZE + 1));
    if(scanf("%d %d %d %d", &node_count, &start, &end, &rib_count) < 4)
    {   
        free(matrix);
        printf("bad number of lines");
        return 0;
    }
    if(start > node_count || end > node_count || start < 1 || end < 1)
    {
        printf("bad vertex");
        free(matrix);
        return 0;
    }
    if(BadInput(node_count, rib_count))
    {   
        free(matrix);
        return 0;
    }
    for(int i = 0; i < rib_count; i++)
    {
        int start = 0;
        int end = 0;
        long long length = 0;
        if(BadNode(&start, &end, &length, node_count))
        {   
            free(matrix);
            return 0;
        }
        MatrixInsert(matrix, start, end, length);
    }
    start--;
    end--;
    long long shortest[MATRIX_SIZE + 1] = {0};
    int used[MATRIX_SIZE + 1] = {0};
    for(int i = 0; i < node_count; i++)
    {
        shortest[i] = LLONG_MAX;
    }
    shortest[start] = 0;
    int parents[MATRIX_SIZE + 1] = {0};
    int ways = 0;
    Deix(matrix, start, end, shortest, used, node_count, parents, &ways);
    for(int i = 0; i < node_count; i++)
    {   
        if(shortest[i] == LLONG_MAX)
        {
            printf("oo ");
        }
        else if(shortest[i] > INT_MAX)
        {
            printf("INT_MAX+ ");
        }
        else
        {
            printf("%lli ", shortest[i]);
        }
    }
    printf("\n");
    if(shortest[end] == LLONG_MAX)
    {
        printf("no path");
    }
    else if(shortest[end] > INT_MAX && ways > 1)
    {
        printf("overflow");
    }
    else
    {
        int current = end;
        printf("%d ", current + 1);
        while(1)
        {
            current = parents[current];
            printf("%d ", current + 1);
            if(current == 0)
            {
                break;
            }
        }
        printf("%d ", start + 1);
    }
    free(matrix);
    return EXIT_SUCCESS;
}

void Deix(int* matrix, int start, int end, long long shortest[], int used[], int node_count, int parents[], int* ways)
{   
    if(used[start] == 1)
    {
        return;
    }
    used[start] = 1;
    for(int i = 0; i < node_count; i++)
    {
        if(matrix[start * MATRIX_SIZE + i] != 0 && used[i] == 0)
        {   
            if(i == end)
            {
                *ways++;
            }
            if(shortest[start] + matrix[start * MATRIX_SIZE + i] < shortest[i])
            {   
                shortest[i] = matrix[start * MATRIX_SIZE + i] + shortest[start];
                parents[i] = start;
            }
        }
    }
    int new_min_node = -1;
    long long new_min = LLONG_MAX;
    for(int i = 0; i < node_count; i++)
    {
        if(used[i] == 0 && shortest[i] < new_min)
        {
            new_min = shortest[i];
            new_min_node = i;
        }
    }
    if(new_min_node != -1)
    {
        Deix(matrix, new_min_node, end, shortest, used, node_count, parents);
    }
}

int BadNode(int* start, int* end, long long* length, int node_count)
{   
    if(scanf("%d %d %lli", start, end, length) < 3)
    {
        printf("bad number of lines");
        return 1;
    }
    if(*start < 1 || *end < 1 || *start > node_count || *end > node_count)
    {
        printf("bad vertex");
        return 1;
    }
    if(*length < 0 || *length > INT_MAX)
    {
        printf("bad length");
        return 1;
    }
    return 0; 
}

int BadInput(int nodes, int ribs)
{
    if (nodes > MATRIX_SIZE || nodes < 0)
    {
        printf("bad number of vertices");
        return 1;
    }
    if (ribs < 0 || ribs > nodes * (nodes + 1) / 2)
    {
        printf("bad number of edges");
        return 1;
    }
    return 0;
}

void MatrixInsert(int* matrix, int start, int end, long length)
{   
    matrix[(start-1) * MATRIX_SIZE + (end-1)] = (int)length;
    matrix[(end-1) * MATRIX_SIZE + (start-1)] = (int)length;
}
