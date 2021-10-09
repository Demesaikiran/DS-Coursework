#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 100

struct node
{
    char * ele;
    struct node * next;
};
typedef struct node NODE;


NODE * createNode(char * ele)
{
    NODE * newnode = malloc(sizeof(NODE));
    newnode -> ele  = ele;
    newnode -> next = NULL;

    return newnode;
}

void insertLast(NODE ** head, char * data)
{
    NODE * newnode = createNode(data);

    if(*head == NULL)
    {
        *head = newnode;
        return;
    }

    NODE * travel = *head;
    while(travel -> next != NULL)
    {
        travel = travel -> next;
    }
    travel -> next = newnode;
    return;
}

void printList(NODE * head)
{
    while(head != NULL)
    {
        printf("%s ", head -> ele);
        head = head -> next;
    }
}

void push(NODE ** head, char * ele)
{
    //Inserting front will be the best option
    NODE * newnode = createNode(ele);
    if(*head == NULL)
    {
        *head = newnode;
        return;
    }
    NODE * temp = *head;
    *head = newnode;
    newnode -> next = temp;
    //free(temp);
}

char * pop(NODE ** head)
{   
    char * temp = (*head) -> ele;
    *head = (*head) -> next;
    return temp;
}


int precesion(char symbol)
{
    switch(symbol)
    {
        case '(':
        case ')': return 1;
        case '+':
        case '-': return 2;
        case '*':
        case '%':
        case '/': return 3;
        //case '^': return 6;
        case '#': return 0;
    }
}
int isOperator(char symbol)
{
    switch(symbol)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '(':
        case ')': return 0;
        default : return 1;
    }
}

NODE * convertInfixToPostfix(char * input)
{
    
    NODE * postfix = NULL;
    //char postfix[MAXSIZE];
    int index = 0;
    NODE * st = NULL;
    push(&st, "#");
    char * symbol = strtok(input, " ");

    while(symbol != NULL)
    {
        if(isOperator(*symbol))
        {
            insertLast(&postfix, symbol);
            //postfix[index++] = symbol;
        }

        else
        {
            if(*symbol == '(')
            {
                push(&st, symbol);
            }
            else if(*symbol == ')')
            {
                while(*(st -> ele) != '(')
                {
                    insertLast(&postfix, pop(&st));
                    //postfix[index++] = pop(&st);
                }
                char * dummy = pop(&st);
                
            }

            else
            {
                if(precesion(*symbol) > precesion(*(st -> ele)))
                {
                    push(&st, symbol);
                }
                else
                {
                    while(precesion(*symbol) <= precesion(*(st -> ele)))
                    {
                        insertLast(&postfix, pop(&st));
                        //postfix[index++] = pop(&st);
                    }
                    push(&st, symbol);
                }
            }
        }

        symbol = strtok(NULL, " ");
    }

    while(*(st -> ele) != '#')
    {
        insertLast(&postfix, pop(&st));
        //postfix[index++] = pop(&st);
    }

    return postfix;
}

int main()
{
    char infix_input[MAXSIZE];
    fgets(infix_input, MAXSIZE, stdin);
    strtok(infix_input, "\n");

    NODE * postfix = convertInfixToPostfix(infix_input);

    printList(postfix);
    free(postfix);
    return 0;

}