#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MATRIX_SIZE 5000

typedef struct edge
{
	int first;
	int second;
} edge;

int BadNumber(int node_count, int rib_count);
int PrimmAlgo(int* matrix, edge* carcass, int* used, int node_count);
int GetMatrix(int* matrix, int node_count, int rib_count);
int BadNumber(int node_count, int rib_count);

int main(void) 
{
	int node_count = 0;
	int rib_count = 0;
	if(scanf("%d %d", &node_count, &rib_count) < 2)
	{	
		printf("bad number of lines");
		return 0;
	}
	if(BadNumber(node_count, rib_count))
	{	
		return 0;
	}

	int* matrix = calloc(node_count * node_count, sizeof(int));
 	if(!GetMatrix(matrix, node_count, rib_count))
 	{	
 		free(matrix);
 		return 0;
 	}

	edge carcass[MATRIX_SIZE] = {0};
	int used[MATRIX_SIZE] = {0};
	if(PrimmAlgo(matrix, carcass, used, node_count))
	{
		for(int i = 0; i < node_count - 1; i++)
		{
			printf("%d %d\n", carcass[i].first, carcass[i].second);
		}
	}
	else
	{	
		free(matrix);
		return 0;
	}
	free(matrix);
    return 0;
}

int PrimmAlgo(int* matrix, edge* carcass, int* used, int node_count)
{
	int* MinNode = (int*)malloc(node_count * sizeof(int));
	int* MinDist = (int*)malloc(node_count * sizeof(int));
	int carcass_count = 0;
	used[0] = 1;

	for(int i = 0; i < node_count; i++)
	{
		if(matrix[i])
		{
			MinNode[i] = 0;
			MinDist[i] = matrix[i];
		}
		else
		{
			MinNode[i] = -1;
			MinDist[i] = -1;
		}
	}

	for(int i = 0; i < node_count - 1; i++)
	{
		int next = -1;
		for(int j = 0; j < node_count; j++)
		{	
			if(used[j] == 0 && (next == -1 || MinDist[next] == -1 || ((MinDist[j] != -1) && (MinDist[j] < MinDist[next]))))
			{
				next = j;
			}
		}
		if(MinDist[next] == -1)
		{
			printf("no spanning tree");
			free(MinDist);
			free(MinNode);
			return 0;
		}
		carcass[carcass_count].first = MinNode[next] + 1;
		carcass[carcass_count].second = next + 1;
		carcass_count++;
		used[next] = 1;
		for(int j = 0; j < node_count; j++)
		{	
			if(matrix[(node_count * next) + j] != 0 && (MinDist[j] == -1 || matrix[(node_count * next) + j] < MinDist[j]))
			{
				MinDist[j] = matrix[(node_count * next) + j];
				MinNode[j] = next;
			}
		}
	}
	free(MinDist);
	free(MinNode);
	return 1;
}

int GetMatrix(int* matrix, int node_count, int rib_count)
{
	int start;
	int end;
	long long length;
	for(int i = 0; i < rib_count; i++)
	{
		if (scanf("%d %d %lld", &start, &end, &length) < 3)
		{	
			printf("bad number of lines");
			return 0;
		}
		if (start > node_count || start < 1 || end > node_count || end < 1)
		{
			printf("bad vertex");
			return 0;
		}
		if (length < 0 || length > INT_MAX)
		{
			printf("bad length");
			return 0;
		}
		if (start == end)
		{
			printf("no spanning tree");
			return 0;
		}
		start--;
		end--;
		matrix[(start * node_count) + end] = length;
		matrix[(end * node_count) + start] = length;
	}
	return 1;
}

int BadNumber(int node_count, int rib_count)
{
	if (node_count > 5000 || node_count < 0)
	{
		printf("bad number of vertices");
		return 1;
	}
	if (rib_count < 0 || rib_count > node_count * (node_count + 1) / 2)
	{
		printf("bad number of edges");
		return 1;
	}
	if(rib_count < node_count - 1 || node_count == 0)
	{
		printf("no spanning tree");
		return 1;
	}
	return 0;
}
