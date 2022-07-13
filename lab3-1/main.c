#include <stdlib.h>
#include <stdio.h>

int QuickSort(int arr[], int start, int end);

int main(void) 
{
    int count = 0;

    if (!scanf("%d", &count))
    {
        return 0;
    }

    int *arr = malloc(count*sizeof(int) + 1);

    for (int i = 0; i < count; i++)
    {
        if(!scanf("%d", &arr[i]))
        {
            return 0;
        }
    }


    if(count > 1)
    {
        QuickSort(arr, 0, count-1);
    }

    for(int i = 0; i < count; i++)
    {
        printf("%d ", arr[i]);
    }

    free(arr);
    return 0;
}


int QuickSort(int arr[], int start, int end)
{   
    if (start >= end)
    {
        return 0;
    }
    
    int pivot = arr[(end-start)/2 + start];
    int left_num = start;
    int right_num = end;

    while(left_num <= right_num)
    {   
        while(arr[left_num] < pivot)
        {
            left_num++;
        }
        while(arr[right_num] > pivot)
        {
            right_num--;
        }
        if (left_num <= right_num)
        {
            int swap = arr[left_num];
            arr[left_num] = arr[right_num];
            arr[right_num] = swap;
            left_num++;
            right_num--;
        }
    }
    QuickSort(arr, start, right_num);
    QuickSort(arr, left_num, end);
    return 0;
}



