#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define BLACK 2;
#define GREY 1;
#define WHITE 0;

typedef struct connect_component connect_component;
typedef struct rib rib;

struct rib
{
	int length;
	int first;
	int second;
};

struct connect_component
{
	connect_component* next;
	int value;
	connect_component* part_of;
};

int BadNumber(int node_count, int rib_count);
int GetRib(rib* current, int node_count);
void SortRibs(rib array[], int low, int high);
int partition(rib array[], int low, int high);
void swap(rib *a, rib *b);

int main(void) 
{
	int node_count = 0;
	int rib_count = 0;
	if(scanf("%d %d", &node_count, &rib_count) < 2)
	{	
		printf("bad number of lines");
		return 0;
	}
	rib* rib_arr = malloc(sizeof(rib) * rib_count);
	connect_component* component_arr = malloc(sizeof(connect_component) * node_count);
	for(int i = 0; i < node_count; i++)
	{
		component_arr[i].value = i+1;
	}
	if (BadNumber(node_count, rib_count))
	{	
		free(rib_arr);
		free(component_arr);
		return 0;
	}
	for(int i = 0; i < rib_count; i++)
	{
		if (!GetRib(&rib_arr[i], node_count))
		{
			free(rib_arr);
			free(component_arr);
			return 0;
		}
	}
	SortRibs(rib_arr, 0, rib_count - 1);
	int karkas_count = 0;
	int firsts[5000] = {0};
	int seconds[5000]= {0};
	for(int i = 0; i < rib_count; i++)
	{	
		int first = rib_arr[i].first;
		int second = rib_arr[i].second;
		connect_component* current_f = &component_arr[first-1];
		connect_component* current_s = &component_arr[second-1];
		while(1)
		{	
			if(current_f->part_of != NULL)
			{	
				connect_component* temp = current_f->part_of;
				int check = 0;
				while(1)
				{	
					if(temp->value == second)
					{
						check = 1;
						break;
					}
					if(temp->next == NULL)
					{
						break;
					}
					temp = temp->next;
				}
				if(check == 1)
				{
					break;
				}
				temp->next = &component_arr[second-1];
				component_arr[second-1].part_of = temp->part_of;
				firsts[karkas_count] = first;
				seconds[karkas_count] = second;
				karkas_count++;
				break;
			}
			if(current_s->part_of != NULL)
			{	
				connect_component* temp = current_s->part_of;
				int check = 0;
				while(1)
				{	
					if(temp->value == first)
					{
						check = 1;
						break;
					}
					if(temp->next == NULL)
					{
						break;
					}
					temp = temp->next;
				}
				if(check == 1)
				{
					break;
				}
				temp->next = &component_arr[first-1];
				component_arr[first-1].part_of = temp->part_of;
				firsts[karkas_count] = first;
				seconds[karkas_count] = second;
				karkas_count++;
				break;
			}
			if (current_f->next == NULL)
			{	
				current_f->next = &component_arr[second-1];
				component_arr[second-1].part_of = current_f;
				component_arr[first-1].part_of = &component_arr[first-1];
				firsts[karkas_count] = first;
				seconds[karkas_count] = second;
				karkas_count++;
				break;
			}
			if (current_f->next->value == second)
			{
				break;
			}	
			current_f = current_f->next;
		}
	}
	if (karkas_count != node_count - 1)
	{
		printf("no spanning tree\n");
	}

	else
	{
		for(int i = 0; i < karkas_count; i++)
		{
			printf("%d %d\n", firsts[i], seconds[i]);
		}
	}
	free(rib_arr);
	free(component_arr);
    return EXIT_SUCCESS;
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
	return 0;
}

int GetRib(rib* current, int node_count)
{	
	int start;
	int end;
	long long length;
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
	current->first = start;
	current->second = end;
	current->length = length;
	return 1;
}

void SortRibs(rib array[], int low, int high)
{	
    if (low < high)
   	{
    	int pi = partition(array, low, high);
    	SortRibs(array, low, pi - 1);
    	SortRibs(array, pi + 1, high);
  	}
}

void swap(rib *a, rib *b)
{
  rib t = *a;
  *a = *b;
  *b = t;
}

int partition(rib array[], int low, int high) 
{
	int pivot = array[high].length;
  	int i = (low - 1);
  	for (int j = low; j < high; j++)
 	{
    	if (array[j].length <= pivot) 
    	{
      		i++;
      		swap(&array[i], &array[j]);
   		}
	}
	swap(&array[i + 1], &array[high]);
	return (i + 1);
}
