#include <stdlib.h>
#include <stdio.h>

typedef struct node node;

int GetHeight(node* current);
int BalanceCounter(node* current);
void ResetHeight(node* current);
node* RightRotation(node* current);
node* LeftRotation(node* current);
node* BigRightRotation(node* current);
node* BigLeftRotation(node* current);
node* InsertNode(node* current, int value, node* nodes, int counter);
node* Rebalance(node* current);

struct node
{
    int value;
    int height;
    node* left;
    node* right;
};

int main(void)
{
    int amount = 0;
    if(!scanf("%d", &amount))return 0;

    if(amount == 0)
    {
        printf("0");
        return EXIT_SUCCESS;
    }

    node* nodes = malloc(sizeof(node) * amount);
    int current = 0;
    node* head = NULL;

    for(int i = 0; i < amount; i++)
    {   
        if(!scanf("%d", &current))return 0;
        head = InsertNode(head, current, nodes, i);
    }
    printf("%d\n", GetHeight(head));
    free(nodes);
    return EXIT_SUCCESS;
}

int BalanceCounter(node* current)
{   
    if(current == NULL)
    {
        return 0;
    }
    int balance = GetHeight(current->left) - GetHeight(current->right);
    return balance;
}

int GetHeight(node* current)
{
    if(current == NULL)
    {
        return 0;
    }
    return current->height;
}

void ResetHeight(node* current)
{
    int left_height = GetHeight(current->left);
    int right_height = GetHeight(current->right);
    if(left_height > right_height)
    {
        current->height = left_height + 1;
    }
    else
    {
        current->height = right_height + 1;
    }
}

node* RightRotation(node* current)
{
    node* new_head = current->left;
    current->left = new_head->right;
    new_head->right = current;
    ResetHeight(current);
    ResetHeight(new_head);
    return new_head;
}

node* LeftRotation(node* current)
{
    node* new_head = current->right;
    current->right = new_head->left;
    new_head->left = current;
    ResetHeight(current);
    ResetHeight(new_head);
    return new_head;
}

node* BigRightRotation(node* current)
{
    current->left = LeftRotation(current->left);
    current = RightRotation(current);
    return current;
}

node* BigLeftRotation(node* current)
{
    current->right = RightRotation(current->right);
    current = LeftRotation(current);
    return current;
}

node* InsertNode(node* current, int value, node* nodes, int counter)
{
    if(current == NULL) 
    {
        nodes[counter].value = value;
        nodes[counter].height = 1;
        nodes[counter].left = NULL;
        nodes[counter].right = NULL;
        return &nodes[counter];
    }
    if(value < current->value)
    {
        current->left = InsertNode(current->left, value, nodes, counter);
    }
    else
    {   
        current->right = InsertNode(current->right, value, nodes, counter);
    }
    return Rebalance(current);
}

node* Rebalance(node* current)
{
    ResetHeight(current);
    int current_balance = BalanceCounter(current);
    if(current_balance > 1)
    {   
        if(BalanceCounter(current->left) >= 0)
        {
            current = RightRotation(current);
        }
        else
        {   
            current = BigRightRotation(current);
        }
        return current;
    }
    else if(current_balance < -1)
    {   
        if(BalanceCounter(current->right) <= 0)
        {   
            current = LeftRotation(current);
        }
        else
        {   
            current = BigLeftRotation(current);
        }
        return current;
    }
    return current;
}
