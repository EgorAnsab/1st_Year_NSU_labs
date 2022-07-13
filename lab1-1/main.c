#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int HashCount(unsigned char str[], int last_hash, int sample_len, char last_first_letter);
int Power(int num, int i);
unsigned int GetSample(unsigned char sample[]);
int UpdateText(unsigned char text[], int how_much, int sample_len);
int SampleHashCount(unsigned char str[], int sample_len);


int main(void)
{  
    unsigned char sample[18] = {0};
    unsigned char text[36] = {0};

    unsigned int sample_len = GetSample(sample);

    int sample_hash = SampleHashCount(sample, sample_len);

    if (fread(text, 1, sample_len, stdin) < sample_len)
    {   
        printf("0");
        return 0;
    }
    
    printf("%d ", sample_hash);

    int text_hash = 0;
    int text_count = 1;
    unsigned char last_first_letter = '0';

    while(1) 
    {   
        text_hash = HashCount(text, text_hash, sample_len, last_first_letter);
        if (sample_hash == text_hash)
        {   
            int count = 0;
            for(unsigned int i = 0; i < sample_len; i++)
            {   
                count++;
                printf("%d ", text_count);
                text_count++;
                if (text[i] != sample[i])
                {   
                    break;
                }
            }
            text_count -= count;
        }

        last_first_letter = text[0];

        int check = UpdateText(text, 1, sample_len);
        
        if (check > 0)
        {
            break;
        }
        text_count++;
    }
    return 0;
}



int SampleHashCount(unsigned char str[], int sample_len)
{
    int hash = 0;
    for(int i = 0; i < sample_len; i++)
    {   
        hash += ((int)str[i] % 3) * Power(3, i);
    }
    return hash;
}


int HashCount(unsigned char str[], int last_hash, int sample_len, char last_first_letter)
{   
    int hash = 0;
    if (last_hash == 0)
    {   
        for(int i = 0; i < sample_len; i++)
        {   
            hash += ((int)str[i] % 3) * Power(3, i);
        }
        return hash;
    }
    else
    {   
        hash = last_hash;
        hash -= (int)last_first_letter % 3;
        hash /= 3;
        hash += ((int)str[sample_len-1] % 3) * Power(3, sample_len - 1);
        return hash;
    }
}


int Power(int num, int i)
{   
    if (i > 0)
    {    
        int sum = 1;
        for (int j = 0; j < i; j++)
        {
            sum*=num;
        }
        return sum;
    }
    if (i == 0)
    {
        return 1;
    }
    return 0;
}



unsigned int GetSample(unsigned char sample[])
{
    unsigned char temp;
    unsigned int count = 0;
    while (fscanf(stdin, "%c", &temp))
    {
        if (temp == '\n')
        {
            break;
        }
        sample[count] = temp;
        count++;
    }
    return count;
}



int UpdateText(unsigned char text[], int how_much, int sample_len)
{   
    if (how_much == 0)
    {
        return 0;
    }
    for (int i = 0; i < sample_len - how_much+1; i++)
    {   
        text[i] = text[how_much+i];
    }
    int stop = fread(&text[sample_len - how_much], 1, how_much, stdin);
    if (stop != how_much)
    {
        return 10;
    }
    return 0;
}
