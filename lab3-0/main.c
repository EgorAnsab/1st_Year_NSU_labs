#include <stdlib.h>
#include <stdio.h>


void MakeHeap(int arr[], int how_much);
int MakeHeapLocal(int arr[], int knot, int how_much);
int Swap(int arr[], int knot, int how_much);


int main(void)
{
    int heap_count = 0;

    if (!scanf("%d", &heap_count))
    {
        return 0;
    }

    int a = heap_count;

    int *arr = malloc(sizeof(int)*heap_count + 1);

    for(int i = 0; i < heap_count; i++)
    {
        if(!scanf("%d", &arr[i]))
        {
            return 0;
        }
    }

    MakeHeap(arr, heap_count);

    while(heap_count > 0)
    {   
        if (heap_count == a)
        {   
            int swap = arr[0];
            arr[0] = arr[heap_count - 1];
            arr[heap_count - 1] = swap;
            heap_count--;
        }
        else
        {   
            MakeHeapLocal(arr, 0, heap_count);
            int swap = arr[0];
            arr[0] = arr[heap_count - 1];
            arr[heap_count - 1] = swap;
            heap_count--;
        }
    }

    for(int i = 0; i < a; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return EXIT_SUCCESS;
}



int MakeHeapLocal(int arr[], int knot, int how_much)
{   
    if((knot + 1) * 2 > how_much)
    {
        return 0;
    }
    int new_knot = Swap(arr, knot, how_much);
    if(new_knot != 0 && new_knot != knot)
    {
        MakeHeapLocal(arr, new_knot, how_much);
    }
    else
    {
        return 1;
    }
    return 0;
}



void MakeHeap(int arr[], int how_much)
{
    for(int i = how_much / 2; i >= 0; i--)
    {   
        int new = Swap(arr, i, how_much);
        if (new != 0)
        {   
            MakeHeapLocal(arr, new, how_much);
        }
    }
}



int Swap(int arr[], int knot, int how_much)
{
    knot++;

    if(knot * 2 > how_much)
    {
        return 0;
    }

    if(knot * 2 + 1 > how_much)
    {
        if(arr[knot-1] < arr[knot * 2 - 1])
        {
            int swap = arr[knot-1];
            arr[knot-1] = arr[knot * 2 - 1];
            arr[knot * 2 - 1] = swap;
            return(knot * 2 - 1);
        }
    }
    else
    {
        if(arr[knot * 2 - 1] > arr[knot * 2] && arr[knot * 2 - 1] > arr[knot - 1])
        {
            int swap = arr[knot -1 ];
            arr[knot - 1] = arr[knot * 2 - 1];
            arr[knot * 2 - 1] = swap; 
            return(knot * 2 - 1);
        }
        else if(arr[knot * 2] > arr[knot * 2 - 1] && arr[knot * 2] > arr[knot - 1])
        {
            int swap = arr[knot - 1];
            arr[knot - 1] = arr[knot * 2];
            arr[knot * 2] = swap;
            return(knot * 2);
        }
    }
    return 0;
}
