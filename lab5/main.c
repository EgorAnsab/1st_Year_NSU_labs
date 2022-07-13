#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct node node;

#define SIZE 256

struct node
{
	node* left;
	node* right;
	int freq;
	int is_empty;
	char c;
};

int GetArr(int arr_count[], node* arr_end); // works
void CountSymbols(int arr_count[], char str[], int symbol_count); // works
void QuickSort(node* arr, int start, int end); // works
void MakeSortedAgain(node arr[], int position, int start); //works
void FreeTree(node* current); // should work
node* MakeTree(int unique_symbol_count, node arr_end[]);
void Encode(node* tree, char str[]);
void GetCodeArr(char code_arr[][SIZE], char current_code[], node* tree, int counter, char relevant_letters[]);
char BittedCode(char code[]); //works
void MakeText(node* tree);
int GetTree(node* tree);
int MakeCodeFromChar(char code[], char current_code);

int relevant_count = 0;

int main(void) 
{	
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	char current_type = getc(stdin);
	if(current_type == 'c') //Works Like it should
	{
		char str[2510] = {0};
		if(!scanf("%2500s", str))return 0;
		int symbol_count = 0;
		symbol_count = strlen(str);
		int arr_count[SIZE] = {0};
		CountSymbols(arr_count, str, symbol_count);
		node* arr_end = malloc(sizeof(node)*SIZE*2); // maybe not enough
		int unique_symbol_count = GetArr(arr_count, arr_end);
		QuickSort(arr_end, 0, unique_symbol_count-1);
		for(int i = 0; i < unique_symbol_count; i++)
		{
			arr_end[i].is_empty = 0;
		}	
		node* tree = MakeTree(unique_symbol_count, arr_end);
		if(unique_symbol_count > 1)
		{
			Encode(tree, str);
		}
		else
		{	
			printf("%c%c", str[0], 0);
			printf("SS");
			for(int i = 0; i < symbol_count; i++)
			{
				printf("0");
			}
		}
	}
	else
	{	
		node* tree = malloc(sizeof(node));
		tree->is_empty = 1;
		if(GetTree(tree))
		{
			return 0;
		}
		printf("%c\n", tree->left->left->c); // left left - a right - a left right - is empty (error here) (problem is in making code form char)
		scanf("%d");
		MakeText(tree);
	}
	scanf("%d");
    return EXIT_SUCCESS;
}

void MakeText(node* tree) //Need to check tree accuracy somehow
{
	char current_char = 0;
	node* current = tree;
	while(1)
	{	
		if(!scanf("%c", &current_char))
		{
			return;
		}
		if(current_char == '0')
		{	
			current = current->left;
		}
		else if(current_char == '1')
		{	
			current = current->right;
		}
		if(!current->is_empty) //Never here
		{	
			printf("%c", current->c); // aaaa?
			current = tree;
		}
	}
}

int GetTree(node* tree) //WRONG!!!
{	
	if(!tree)
	{
		return 1;
	}
	char current_char = 0;
	char current_code = 0;
	while(1)
	{	
		if(scanf("%c%c", &current_char, &current_code) < 2)
		{
			return 1;
		}
		if(current_char == 'S' && current_code == 'S')
		{	
			return 0;
		}
		char code[8] = {0};
		int length = MakeCodeFromChar(code, current_code); // Crashing here
		node* current = tree;
		for(int i = 0; i < length; i++)
		{	
			if(code[i] == 1) // codes[i] - correct
			{	
				if(!current->right)
				{
					current->right = (node*)malloc(sizeof(node));
					current->right->is_empty = 1;
					current = current->right;
				}
				else
				{
					current->is_empty = 1;
					current = current->right;
				}
			}
			else
			{	
				if(!current->left)
				{
					current->left = (node*)malloc(sizeof(node));
					current->left->is_empty = 1;
					current = current->left;
				}
				else
				{	
					current->is_empty = 1;
					current = current->left;
				}
			}
		}
		current->is_empty = 0;
		current->c = current_char;
	}
	return 0;
}

int MakeCodeFromChar(char code[], char current_code) // Not working on a letter - last bit - 1 (so it thinks length is 7)
{	
	int length = 7;
	for(int i = 0; i < 8; i++)
	{
		if((current_code & (int)pow(2, i)) != 0)
		{
			break;
		}
		length--;
	}
	for(int i = 0; i < length; i++) // length of a == 7
	{
		code[i] = (current_code & (int)pow(2, 7-i)) != 0;
	}
	code[length] = '\0';
	printf("code = %c%c", code[0], code[1]);
	return length;
}

void Encode(node* tree, char str[])
{
	char code_arr[SIZE][SIZE] = {{0}};
	char current_code[SIZE] = {0};
	char relevant_letters[SIZE] = {0};
	GetCodeArr(code_arr, current_code, tree, 0, relevant_letters);
	char current = str[0];
	int counter = 1;
	for(int i = 0; i < relevant_count; i++)
	{
		printf("%c%c", relevant_letters[i], BittedCode(code_arr[(int)relevant_letters[i]]));
	}
	printf("SS");
	while(current != '\0')
	{	
		printf("%s", code_arr[(int)current]);
		current = str[counter++];
	}
	printf("\n");
}

char BittedCode(char code[]) // Wroks
{
	char res = 0;
	for(int i = 0; i < 8; i++)
	{
		if(code[i] == '\0')
		{	
			res = res | (int)pow(2, 7-i);
			break;
		}
		res = res | (int)(code[i] * pow(2, 7-i));
	}
	return res;
}

void GetCodeArr(char code_arr[][SIZE], char current_code[], node* tree, int counter, char relevant_letters[])
{
	if(tree->is_empty == 0)
	{
		strcpy(code_arr[(int)tree->c], current_code);
		code_arr[(int)tree->c][counter] = '\0';
		relevant_letters[relevant_count] = tree->c;
		relevant_count++;
		return;
	}
	current_code[counter+1] = '\0';
	current_code[counter] = '0';
	GetCodeArr(code_arr, current_code, tree->left, counter+1, relevant_letters);
	current_code[counter+1] = '\0';
	current_code[counter] = '1';
	GetCodeArr(code_arr, current_code, tree->right, counter+1, relevant_letters);
}

node* MakeTree(int unique_symbol_count, node arr_end[])
{
	int left_border = 0;
	int right_border = unique_symbol_count;
	for(int i = 0; i < unique_symbol_count - 1; i++)
	{	
		node* current = (node*)malloc(sizeof(node));
		current->is_empty = 1;
		current->left = &arr_end[left_border];
		current->right = &arr_end[left_border+1];
		current->freq = arr_end[left_border].freq + arr_end[left_border+1].freq;
		arr_end[right_border] = *current;
		left_border+=2;
		right_border++;
		MakeSortedAgain(arr_end, right_border-1, left_border);
	}
	return &arr_end[left_border];
}

void FreeTree(node* current)
{
	if(!current)
	{
		return;
	}
	FreeTree(current->left);
	FreeTree(current->right);
	free(current);
}

int GetArr(int arr_count[], node arr_end[])
{
	int count = 0;
	for(int i = 0; i < SIZE; i++)
	{
		if(arr_count[i] > 0)
		{
			arr_end[count].freq = arr_count[i];
			arr_end[count].c = (char) i; // or i+1?
			arr_end[count].is_empty = 0;
			count++;
		}
	}
	return count;
}

void CountSymbols(int arr_count[], char str[], int symbol_count)
{
	for(int i = 0; i < symbol_count; i++)
	{
		arr_count[(int)str[i]]++;
	}
}

void QuickSort(node* arr, int start, int end)
{   
    if (start >= end)
    {
        return;
    }
    
    int pivot = arr[(end-start)/2 + start].freq;
    int left_num = start;
    int right_num = end;

    while(left_num <= right_num)
    {   
        while(arr[left_num].freq < pivot)
        {
            left_num++;
        }
        while(arr[right_num].freq > pivot)
        {
            right_num--;
        }
        if (left_num <= right_num)
        {
            node swap = arr[left_num];
            arr[left_num] = arr[right_num];
            arr[right_num] = swap;
            left_num++;
            right_num--;
        }
    }
    QuickSort(arr, start, right_num);
    QuickSort(arr, left_num, end);
    return;
}

void MakeSortedAgain(node arr[], int position, int start)
{
	while(position > start && arr[position].freq <= arr[position-1].freq)
	{
		node swap = arr[position];
		arr[position] = arr[position-1];
		arr[position-1] = swap;
		position--;
	}
}
