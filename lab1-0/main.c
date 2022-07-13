#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void make_numbered(unsigned char sample[], unsigned int ascii_table[], unsigned int sample_len);
unsigned int CompareSample(unsigned char sample[], unsigned char text[], unsigned int sample_len, unsigned int text_count, unsigned int ascii_table[]);
int get_sample(unsigned char sample[], FILE *file);
int UpdateText(unsigned char text[], FILE *file, int how_much, int sample_len);
unsigned int unsigned_len(unsigned char arr[]);



int main(void)
{  
    FILE *file = fopen("in.txt", "rt");

    unsigned char sample[18] = {0};
    unsigned char text[18] = {0};
    unsigned int ascii_table[257] = {0};

    if(!get_sample(sample, file))return 0;
    unsigned int sample_len = unsigned_len(sample);
    if (!fread(text, sizeof(unsigned char), sample_len, file))return 0;  
    make_numbered(sample, ascii_table, sample_len);

    unsigned int text_count = 0;
    int while_check = 0;

    while(!while_check) 
    {   
        int how_much = CompareSample(sample, text, sample_len, text_count, ascii_table);
        text_count += how_much;
        while_check = UpdateText(text, file, how_much, sample_len);
    }

    fclose(file); 
}



void make_numbered(unsigned char sample[], unsigned int ascii_table[], unsigned int sample_len)
{
    for (int i = 0; i < 257; i++)
    {
        ascii_table[i] = sample_len;
    }
    for (unsigned int i = sample_len - 1; i>0; i--)
    {   
        if (ascii_table[(int)sample[i-1]] == sample_len)
        {
            ascii_table[(int)sample[i-1]] = sample_len - (i);
        }
    }
}



unsigned int unsigned_len(unsigned char arr[])
{
    int k = 0;
    while (arr[k] != '\0')
    {
        k++;
    }
    return k;
}



int get_sample(unsigned char sample[], FILE *file)
{
    unsigned char c[1];
    int count = 0;
    if (!fread(c, sizeof(unsigned char), 1, file))return 0;
    while(c[0]!='\n')
    {   
        sample[count] = c[0];
        if (!fread(c, sizeof(unsigned char), 1, file))return 0;
        count++;
    }
    return 1;
}



int UpdateText(unsigned char text[], FILE *file, int how_much, int sample_len)
{
    for (int i = 0; i < sample_len - how_much+1; i++)
    {   
        text[i] = text[how_much+i];
    }
    int stop = fread(&text[sample_len - how_much], sizeof(unsigned char), how_much, file);
    if (stop != how_much)
    {
        return 10;
    }
    return 0;
}



unsigned int CompareSample(unsigned char sample[], unsigned char text[], unsigned int sample_len, unsigned int text_count, unsigned int ascii_table[])
{   
    unsigned int count = 0;
    int first_encounter = 0;

    while(sample[sample_len - count - 1] == text[sample_len - count - 1] && count<sample_len-1)
    {   
        printf("%u ", sample_len - count + text_count);
        count++;
        first_encounter++;
    }

    if (first_encounter == 0)
    {   
        printf("%u ", sample_len + text_count);
        return(ascii_table[(int)text[sample_len - count - 1]]);
    }
    else
    {   
        printf("%u ", sample_len - count + text_count);
        return(ascii_table[(int)sample[sample_len-1]]);
    }
}
