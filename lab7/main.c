#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WHITE '0'
#define GREY '1'
#define BLACK '2'

int Depth(int stack[], char matrix[][251], int current, int node_count);
void MatrixInsert(char matrix[][251], int start, int end);
int PowTwo(int exp);
int BadNode(int* start, int* end, int node_count);
int BadInput(int nodes, int ribs);

int stack_count = 0;

int main(void) 
{
    int node_count = 0;
    int rib_count = 0;
    char matrix[2000][251] = {{0}};

    if(scanf("%d %d", &node_count, &rib_count) < 2)
    {   
        printf("Bad number of lines");
        return 0;
    }

    if(BadInput(node_count, rib_count))
    {   
        return 0;
    }

    for(int i = 0; i < rib_count; i++)
    {
        int start = 0;
        int end = 0;
        if(BadNode(&start, &end, node_count))
        {   
            return 0;
        }
        MatrixInsert(matrix, start, end);
    }

    int stack[2001] = {0};

    for(int i = 0; i < node_count; i++)
    {
        if(Depth(stack, matrix, i, node_count) == 1)
        {   
            printf("impossible to sort");
            return 0;
        }
    }
    
    for(int i = 0; i < stack_count; i++)
    {
        printf("%d ", stack[stack_count-i-1]);
    }

    return 0;
}


int Depth(int stack[], char matrix[][251], int current, int node_count)
{   
    if(matrix[current][250] == GREY)
    {
        return 1;
    }
    if(matrix[current][250] == BLACK)
    {
        return 0;
    }
    matrix[current][250] = GREY;
    for(int i = 0; i < node_count / 8 + 1; i++)
    {
        if(i == 250)
        {
            continue;
        }
        for(int j = 0; j < 8; j++)
        {   
            if((matrix[current][i] & PowTwo(j)) != 0)
            {  
                if(Depth(stack, matrix, i*8 + j, node_count))
                {
                    return 1;
                }
            }
        }
    }
    matrix[current][250] = BLACK;
    stack[stack_count] = current + 1;
    stack_count++;
    return 0;
}


void MatrixInsert(char matrix[][251], int start, int end)
{   
    matrix[start-1][(end-1) / 8] = matrix[start-1][(end-1) / 8] | PowTwo((end - 1) % 8);
}


int PowTwo(int exp)
{
    return 1<<exp;
}


int BadNode(int* start, int* end, int node_count)
{   
    if(scanf("%d %d", start, end) < 2)
    {
        printf("bad number of lines");
        return 1;
    }
    if(*start > 2000 || *end > 2000 || *start < 1 || *end < 1 || *start > node_count || *end > node_count)
    {
        printf("bad vertex");
        return 1;
    }
    return 0; 
}


int BadInput(int nodes, int ribs)
{
    if (nodes > 2000 || nodes < 0)
    {
        printf("bad number of vertices");
        return 1;
    }
    if (ribs < 0 || ribs > nodes * (nodes - 1) / 2)
    {
        printf("bad number of edges");
        return 1;
    }
    return 0;
}
