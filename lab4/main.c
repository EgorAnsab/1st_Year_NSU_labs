#include <stdlib.h>
#include <stdio.h>

#define BRACKET 2
#define SIGN 1
#define NUMBER 0
#define WRONG_INPUT -1
#define END -10

int GetPriority(char sign);
int GetToken(char initial[], int *start_point, int last_type, char current[]);
int GetType(char ch);
int Calc(int a, int b, char sign, int *check);

int main(void)
{   
    char initial[2000] = {0};
    if(!fgets(initial, 2000, stdin))
    {
        return 0;
    }
    if(initial[0] == '\n' || initial[0] == '\0')
    {
        printf("syntax error");
        return 0;
    }

    char current[2000] = {0};
    int *start_point = malloc(sizeof(int));
    *start_point = 0;

    int num_stack[2000] = {0};
    int num_stack_count = 0;

    char sign_stack[2000] = {0};
    int sign_stack_count = 0;

    int current_type = WRONG_INPUT;
    int current_pos = 0;
    int next_minus = 0;
    int *check_zero = malloc(sizeof(int));

    while(1)
    {   
        *(check_zero) = 0;
        current_type = GetToken(initial, start_point, current_type, current);

        if(current_type == SIGN)
        {   
            if(current[0] == '-')
            {   
                if(current_pos == 0)
                {
                    if(GetType(initial[current_pos+1]) == NUMBER)
                    {
                        next_minus++;
                        continue;
                    }
                    else if(GetType(initial[current_pos+1]) == BRACKET)
                    {
                        num_stack[0] = 0;
                        num_stack_count++;
                        sign_stack[0] = '-';
                        sign_stack_count++;
                        continue;
                    }
                }
                else if(initial[current_pos-1] == '(')
                {
                    next_minus++;
                    continue;
                }
            }
            if (sign_stack_count == 0)
            {   
                sign_stack[sign_stack_count] = current[0];
                sign_stack_count++;
            }
            else
            {
                if(GetPriority(sign_stack[sign_stack_count-1]) < GetPriority(current[0]))
                {
                    sign_stack[sign_stack_count] = current[0];
                    sign_stack_count++;
                }
                else if(GetPriority(sign_stack[sign_stack_count-1]) == GetPriority(current[0]))
                {
                    num_stack[num_stack_count-2] = Calc(num_stack[num_stack_count-2], num_stack[num_stack_count-1], sign_stack[sign_stack_count-1], check_zero);
                    num_stack_count--;
                    sign_stack[sign_stack_count-1] = current[0];
                }
                else
                {   
                    while(sign_stack_count > 0 && GetPriority(sign_stack[sign_stack_count-1]) >= GetPriority(current[0]))
                    {
                        num_stack[num_stack_count-2] = Calc(num_stack[num_stack_count-2], num_stack[num_stack_count-1], sign_stack[sign_stack_count-1], check_zero);
                        num_stack_count--;
                        sign_stack_count--;
                    }
                    sign_stack[sign_stack_count] = current[0];
                    sign_stack_count++;
                }
            }
        }
        else if(current_type == BRACKET)
        {   
            if (current[0] == '(')
            {   
                sign_stack[sign_stack_count] = current[0];
                sign_stack_count++;
            }
            else
            {   
                while(1)
                {   
                    sign_stack_count--;
                    if (sign_stack_count < 0)
                    {   
                        printf("syntax error");
                        free(start_point);
                        free(check_zero);
                        return 0;
                    }
                    if (sign_stack[sign_stack_count] == '(')
                    {   
                        break;
                    }
                    num_stack[num_stack_count-2] = Calc(num_stack[num_stack_count-2], num_stack[num_stack_count-1], sign_stack[sign_stack_count], check_zero);
                    num_stack_count--;
                }
            }
        }
        else if(current_type == NUMBER)
        {
            num_stack[num_stack_count] = atoi(current);
            if(next_minus == 1)
            {
                num_stack[num_stack_count] = -num_stack[num_stack_count];
                next_minus = 0;
            }
            num_stack_count++;
        }
        else if(current_type == WRONG_INPUT)
        {
            printf("syntax error");
            free(start_point);
            free(check_zero);
            return 0;
        }
        else if(current_type == END)
        {   
            while(sign_stack_count != 0)
            {   
                if(sign_stack[sign_stack_count-1] == '(' || sign_stack[sign_stack_count-1] == ')')
                {
                    printf("syntax error");
                    free(start_point);
                    free(check_zero);
                    return 0;
                }
                num_stack[num_stack_count-2] = Calc(num_stack[num_stack_count-2], num_stack[num_stack_count-1], sign_stack[sign_stack_count-1], check_zero);
                num_stack_count--;
                sign_stack_count--;
            }
            if (*check_zero == 1)
            {
                printf("division by zero");
                free(start_point);
                free(check_zero);
                return 0;
            }
            break;
        }  
        current_pos = *start_point;
        if (*check_zero == 1)
        {
            printf("division by zero");
            free(start_point);
            free(check_zero);
            return 0;
        }
    }
    printf("%d", num_stack[0]);
    free(start_point);
    free(check_zero);
    return 0;
}



int GetPriority(char sign)
{
    if (sign == '+' || sign == '-')
    {
        return 1;
    }
    if (sign == '*' || sign == '/')
    {
        return 2;
    }
    return 0;
}



int GetToken(char initial[], int *start_point, int last_type, char current[])
{   
    int start = *start_point;
    *start_point += 1;
    int current_type = GetType(initial[start]);

    if (current_type == END)
    {   
        if (last_type == SIGN)
        {
            return WRONG_INPUT;
        }
        else if (last_type == BRACKET)
        {
            if(initial[start-1] == '(')
            {
                return WRONG_INPUT;
            }
        }
        return END;
    }
    else if(current_type == WRONG_INPUT)
    {
        return WRONG_INPUT;
    }
    else if(last_type == WRONG_INPUT)
    {
        if(current_type == SIGN)
        {
            if (initial[start] != '-')
            {
                return WRONG_INPUT;
            }
            current[0] = initial[start];
            current[1] = '\0';
            return 1; 
        }
        else if(current_type == BRACKET)
        {   
            if(initial[start] == '(')
            {
                current[0] = initial[start];
                current[1] = '\0';
                return BRACKET;
            }
            else
            {
                return WRONG_INPUT;
            }
        }
        else if (current_type == NUMBER)
        {   
            int count = 0;
            while(1)
            {   
                current[count] = initial[start + count];
                int next_type = GetType(initial[start + count + 1]);
                if (next_type != 0)
                {
                    current[count + 1] = '\0';
                    return 0;
                }
                count++;
                *start_point += 1;
            }
        }
    }
    else if (last_type == NUMBER)
    {
        if(current_type == SIGN)
        {
            current[0] = initial[start];
            current[1] = '\0';
            return SIGN;
        }
        else if(current_type == BRACKET)
        {
            current[0] = initial[start];
            current[1] = '\0';
            return BRACKET;
        }
    } 
    else if (last_type == SIGN)
    {
        if (current_type == SIGN)
        {
            return WRONG_INPUT;
        }
        else if (current_type == BRACKET)
        {   
            if (initial[start] == ')')
            {
                return WRONG_INPUT;
            }
            else
            {   
                current[0] = '(';
                current[1] = '\0';
                return BRACKET;
            }
        }
        else if (current_type == NUMBER)
        {   
            int count = 0;
            while(1)
            {
                current[count] = initial[start + count];
                int next_type = GetType(initial[start + count + 1]);
                if (next_type != NUMBER)
                {
                    current[count + 1] = '\0';
                    return NUMBER;
                }
                count++;
                *start_point += 1;
            }
        }
    }
    else if(last_type == BRACKET)
    {
        if (current_type == SIGN)
        {
            if(initial[start-1] == '(')
            {
                if(initial[start] != '-')
                {
                    return WRONG_INPUT;
                }
            }
            current[0] = initial[start];
            current[1] = '\0';
            return SIGN;
        }
        else if (current_type == BRACKET)
        {
            if (initial[start] != initial[start-1])
            {   
                return WRONG_INPUT;
            }
            else
            {   
                current[0] = initial[start];
                current[1] = '\0';
                return BRACKET;
            }
        }
        else if (current_type == NUMBER)
        {   
            int count = 0;
            while(1)
            {
                current[count] = initial[start + count];
                int next_type = GetType(initial[start + count + 1]);
                if (next_type != NUMBER)
                {
                    current[count + 1] = '\0';
                    return NUMBER;
                }
                count++;
                *start_point += 1;
            }
        }
    }
    return WRONG_INPUT;
}



int GetType(char ch)
{   
    if ((int) ch <= 57 && (int) ch >= 48)
    {   
        return NUMBER;
    }
    else if ((int) ch == 40 || (int) ch == 41)
    {
        return BRACKET;
    }
    else if ((int) ch == 42 || (int) ch == 43 || (int) ch == 45 || (int) ch == 47)
    {
        return SIGN;
    }
    else if(ch == '\0' || ch == '\n')
    {
        return END;
    }
    else
    {
        return WRONG_INPUT;
    }
}



int Calc(int a, int b, char sign, int *check)
{
    if(sign == '/')
    {   
        if(b == 0)
        {
            *(check) = 1;
            return 0;
        }
        return a/b;
    }
    else if(sign == '*')
    {
        return a*b;
    }
    else if(sign == '+')
    {
        return a+b;
    }
    if(sign == '-')
    {   
        return a-b;
    }
    return 0;
}
