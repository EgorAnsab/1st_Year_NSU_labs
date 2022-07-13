#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>

int Split(char num[], char integer[], char fractal[]);
int Char_To_Int(char ch);
long Given_Int_To_Ten(char integer[], int start);
double Given_Fract_To_Ten(char fractal[], int start);
void Ten_Int_To_Given(long integer, int end, char integer_part[]);
int Int_To_Char(int integ);
float CharStar_To_Float(char str[]);
void Ten_Fract_To_Given(double fract, int end, char fractal_result[]);
int Bad_Input(char num[], int start, int end);
double power(int start, int exp);


int main()
{
    int start;
    int end;
    char num[20] = {0};
    
    if(!scanf("%2d", &start)){return 0;};
    if(!scanf("%2d", &end)){return 0;};
    if(!scanf("%15s", num)){return 0;};

    char *integer_part = (char*)malloc(strlen(num)*7*sizeof(char));
    char *fractal_part = (char*)malloc(strlen(num)*7*sizeof(char));

    for (unsigned int i = 0; i < strlen(num)*6; i++)
    {
        integer_part[i] = '\0';
        fractal_part[i] = '\0';
    }

    int bad = Bad_Input(num, start, end);

    if (bad)
    {
        printf("bad input\n");
        free(integer_part);
        free(fractal_part);
        return 0;
    }

    int is_fractal = Split(num, integer_part, fractal_part);
    long ten_int = Given_Int_To_Ten(integer_part, start);
    double ten_fract = Given_Fract_To_Ten(fractal_part, start);
    char fractal_result[70] = {0};
    Ten_Fract_To_Given(ten_fract, end, fractal_result);
    Ten_Int_To_Given(ten_int, end, integer_part);
    integer_part[strlen(integer_part)] = '\0';
    fractal_part[strlen(fractal_part)] = '\0';

    if (is_fractal)
    {
        printf("%s.%s\n", integer_part, fractal_result);
    }
    else
    {
        printf("%s\n", integer_part);
    }

    free(integer_part);
    free(fractal_part);

    return 0;
}



int Bad_Input(char num[], int start, int end)
{   
    int dot_count = 0;

    if (start < 2 || start > 16 || end < 2 || end > 16)
    {
        return 1;
    }

    for (unsigned int i = 0; i < strlen(num); i++)
    {   
        if (Char_To_Int(num[i]) >= start)
        {
            return 1;
        }
        if (num[i] == '.')
        {
            dot_count++;
            if (i == strlen(num) - 1)
            {
                return 1;
            }
        }
    }

    if (dot_count > 1 || num[0] == '.')
    {
        return 1;
    }

    for (unsigned int i = 0; i< strlen(num); i++)
    {
        if ((num[i] == ')') || (num[i] == '('))
        {
            return 1;
        }
    }

    return 0;
}



void Ten_Fract_To_Given(double fract, int end, char fractal_result[])
{   

    for (unsigned int i = 0; i < strlen(fractal_result); i++)
    {
        fractal_result[i] = '\0';
    }

    for (int i = 0; i < 13; i++)
    {   
        static char new_int[20] = {0};
        static char new_fract[70] = {0};
        static char converted_fract[70] = {0};
        static float new_fract_f = 0;

        new_fract_f = fract * end;
        if (new_fract_f < 0.0000000001)
        {   
            break;
        }
        sprintf(converted_fract,"%f", new_fract_f);
        Split(converted_fract, new_int, new_fract);
        fractal_result[i] = Int_To_Char(atoi(new_int));
        fract = CharStar_To_Float(new_fract);
    }
}



float CharStar_To_Float(char str[])
{
    char new[70] = {0};

    for (int i = strlen(str); i>=0; i--)
    {
        new[i+2] = str[i]; 
    }
    
    new[0] = '0';
    new[1] = '.';
    return(atof(new));
}



void Ten_Int_To_Given(long integer, int end, char integer_part[])
{   
    char new_reversed[70] = {0};
    
    while (integer != 0)
    {   
        static int k = 0;

        new_reversed[k] = Int_To_Char(integer % end);
        integer /= end;
        k++;
    }

    for (unsigned int i = 0; i < strlen(new_reversed); i++)
    {   

        integer_part[i] = new_reversed[strlen(new_reversed)-(i+1)];
        if (i == strlen(new_reversed) - 1)
        {
            integer_part[i + 1] = '\0';
        }
    }
}



double Given_Fract_To_Ten(char fractal[], int start)                         
{   
    double new_fractal = 0;

    if (start!=10)
    {
        for (unsigned int i = 0; i < strlen(fractal); i++)
        {
            new_fractal += (double)Char_To_Int(fractal[i]) / power(start, (i+1));
        }
    }
    else
    {
        new_fractal = CharStar_To_Float(fractal);
    }

    if (new_fractal>0.9999)
    {   
        return(0.9999);
    }
    else
    {   
        return(new_fractal);
    }
}





long Given_Int_To_Ten(char integer[], int start)       
{
    long result = 0;
    signed int len = strlen(integer);

    for (int i = 0; i!= len; i++)
    {
        result += Char_To_Int(integer[i]) * power(start, (len - (i+1)));
    }

    return(result);
}



int Char_To_Int(char ch)     
{   
    if (toupper(ch) > 'F')
    {
        return 0;
    }
    switch (ch)
    {   
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        case 'a':
            return 10;
        case 'b':
            return 11;
        case 'c':
            return 12;
        case 'd':
            return 13;
        case 'e':
            return 14;
        case 'f':
            return 15;
        default:
            return ch - '0';
    }
}



int Split(char num[], char integer[], char fractal[])
{   
    int is_fractal = 0;
    for (unsigned int i = 0; i != strlen(num); i++)
    {   
        if (num[i] != '.')
        { 
            if (!is_fractal)
            {
                integer[i] = num[i];
                if (i == strlen(num) - 1)
                {
                    integer[i+1] = '\0';
                }
            }
            else
            {
                fractal[i - strlen(integer) - 1] = num[i];
                if (i == strlen(num) - 1)
                {
                    fractal[i - strlen(integer)] = '\0';
                }
            }
        }
        else
        {
            is_fractal = 1;
            integer[i] = '\0';
        }
    }
    return(is_fractal);
}




int Int_To_Char(int integ)                       
{   
    if(integ > 15 || integ < 0)
    {
        return 0;
    }
    switch (integ)
    {   
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            return integ + '0';
    }
}



double power(int start, int exp)
{   
    if (exp < 0)
    {
        return 0;
    }

    double result = start;

    if (exp != 0)
    {
        for (int i = 0; i < exp - 1; i++)
        {   
            result *= start;
        }
        return result;
    }
    else
    {
        return 1.0;
    }
}

