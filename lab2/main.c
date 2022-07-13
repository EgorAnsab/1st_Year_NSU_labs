#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int BadInput(char arr[], unsigned int len);
int GenerateNext(char arr[], unsigned int len);

int main(void) 
{   
    char arr[11] = {0};
    for(int i = 0; i < 11; i++)
    {
        char a = '0';
        if(!scanf("%c", &a))
        {
            return 0;
        }
        if(a == '\n')
        {   
            arr[i] = '\0';
            break;
        }
        if (i > 9)
        {
            printf("bad input");
            return 0;
        }
        arr[i] = a;
    }
    
    int how_much = 0;
    if(!scanf("%d", &how_much))
    {
        return 0;
    }

    unsigned int len = strlen(arr);

    if(BadInput(arr, len) || len > 10)
    {
        printf("bad input");
        return 0;
    }

    int count = 0;

    while(count != how_much)
    {   
        int check = 0;
        check = GenerateNext(arr, len);

        if (check == 1)
        {
            break;
        }

        for(unsigned int i = 0; i < len; i++)
        {
            printf("%c", arr[i]);
        }
        printf("\n");

        count++;
    }
    return EXIT_SUCCESS;
}



int BadInput(char arr[], unsigned int len)
{   
    int table[10] = {0};
    for(unsigned int i = 0; i < len; i++)
    {   
        if((int)arr[i] < 48 || (int)arr[i] > 57)
        {
            return 1;
        }
        table[(int)arr[i] - 48]++;
    }
    for(int i = 0; i < 10; i++)
    {   
        if(table[i] > 1)
        {
            return 1;
        }
    }
    return 0;
}



int GenerateNext(char arr[], unsigned int len)
{
    int less_count = -1;
    int more_count = -1;

    for(int i = (int)len - 1; i >= 0; i--)
    {
        if(arr[i] < arr[i + 1] && i != (int)len - 1)
        {
            less_count = i;
            break;
        }
    }
    if(less_count == -1)
    {
        return 1;
    }

    for(int i = (int)len - 1; i >= 0; i--)
    {
        if (arr[i] > arr[less_count])
        {
            more_count = i;
            break;
        }
    }

    int swap = arr[less_count];
    arr[less_count] = arr[more_count];
    arr[more_count] = swap;

    for(unsigned int i = less_count + 1; i < (len - less_count) / 2 + 1; i++)
    {
        int swap = arr[i];
        arr[i] = arr[len - i - less_count];
        arr[len - i - less_count] = swap;
    } 
    return 0;
}







