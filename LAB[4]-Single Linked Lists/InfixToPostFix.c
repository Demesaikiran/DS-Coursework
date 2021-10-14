#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 100

/*
*   node structure
*   --------------
*   A node data structure with a string constant
*/
struct node
{
    char * ele;
    struct node * next;
};
typedef struct node NODE;

/*
*   Function: createNode
*   --------------------
*   Creates a node using the NODE structure
*
*   INPUT:
*   ele : creates a node with the string constant element
*   inside it
* 
*   OUTPUT:
*   Address of the created node
*/
NODE * createNode(char * ele)
{
    NODE * newnode = malloc(sizeof(NODE));
    newnode -> ele  = ele;
    newnode -> next = NULL;

    return newnode;
}

/*
*   Function: insertLast
*   --------------------
*   Creates a node with the data given and inserts that node to the
*   last of the linkedlist
*
*   INPUT:
*   head : Reference of the linedlist
*   data : The data which we create a node and insert
*/
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

/*
*   Function: printList
*   -------------------
*   Traverse to the entrie linkedlist and prints the data
*
*   INPUT:
*   head : address of the linkedlist head pointer
*/
void printList(NODE * head)
{
    while(head != NULL)
    {
        printf("%s ", head -> ele);
        head = head -> next;
    }
}

/*
*   Function: push
*   --------------
*   It acts like the stack push and it adds node to the head pointer
*   Underground work is inserting a node first in a linkedlist
*
*   INPUT:
*   head : Reference of the linedlist
*   ele : The data which we create a node and insert
*/
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

/*
*   Function: pop
*   -------------
*   Pops the head pointed element
*
*   INPUT:
*   head : Reference to the linkedlist
*
*   OUTPUT:
*   Returns data of the node poppedout
*/
char * pop(NODE ** head)
{   
    NODE * garb = *head;
    char * temp = (*head) -> ele;
    *head = (*head) -> next;
    free(garb);
    return temp;
}

/*
*   Funciton: precision
*   -------------------
*   It abstracts the scenario of precision with respect to other
*
*   INPUT:
*   symbol : character
*
*   OUTPUT:
*   Its precision defined value
*/
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

/*
*   Function: isOperator
*   --------------------
*   It checks whether it is a operator or not
*
*   INPUT:
*   symbol : a character
*
*   OUTPUT:
*   Returns 0 if it is operator else returns 0
*/
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

/*
*   Function: convertInfixToPostfix
*   -------------------------------
*   It converts the infix expression to postfix expression using stack methods 
*   but implementing using linkedlist
*
*   INPUT:
*   input : String constant infix expression
*   
*   OUTPUT:
*   Returns the postfix expression in terms of linkedlist node
*/
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

/*
*   Function : freeList
*   -------------------
*   Removes the memory allocated to the linkedlist
*
*   INPUT:
*   garbage : Address of the linkedlist list head 
*
*/
void freeList(NODE * garbage)
{
    
    while(garbage != NULL)
    {
        NODE * temp = garbage;
        garbage = garbage -> next;
        //free(temp -> ele);
        free(temp); 
    }
    
}
int main()
{
    char infix_input[MAXSIZE];
    fgets(infix_input, MAXSIZE, stdin);
    strtok(infix_input, "\n");

    NODE * postfix = convertInfixToPostfix(infix_input);

    printList(postfix);
    freeList(postfix);
    return 0;

}