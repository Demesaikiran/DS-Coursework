/* 
*   palindrom.c
*   A program to demonstrate the given inpu string is palindrom or not using 
*   stack and queue methods
*   Deme Sai Kiran 2021
*/

#include<stdio.h>
#include<stdlib.h>

//Predirectives of sized array
#define SIZE 100

// Stack data structure blueprint
struct stack
{
    int top;
    char data[SIZE];
};

//Queue data structure blueprint
struct queue
{
    int front;
    int rear;
    char data[SIZE];
};

// Respective Function declarations
// Includes stack and Queue Operations including palindrom check
int isPalindrome(char * str);
// Stack Operations
int isStackEmpty(struct stack * st);
void push(struct stack *st, char ele);
char pop(struct stack *st);
struct stack stringToStack(char * str);

// Queue Operations
int isQueueEmpty(struct queue * st);
void enqueue(struct queue * qu, char ele);
char dequeue(struct queue * qu);
struct queue stringToQueue(char * str);


int main()
{
    char str[SIZE];

    //Getting large string as input
    fgets(str, SIZE, stdin);
    //input validation < If the input consists only the new line character then it will be palindrom and prints 1>
    if(str[0] == '\n')
    {
        printf("1");
        return 0;
    }
    // Check variable to store the correctness of the function isPalindrome
    int check = isPalindrome(str);
    if(check == 1)
    {
        printf("1");
        return 0;
    }
    printf("0");
    return 0;
}


/*
*   Functoin: isPalindrome
*   ----------------------
*   isPalindrome is afunction that deals with the checking of a input string 
*   either palindrom or not for that matter it takes input as sttring constant
*   
*   str: string constant
*/
int isPalindrome(char * str)
{
    char ch;
    struct stack st;
    struct queue qu;
    qu = stringToQueue(str);
    st = stringToStack(str);
    
    while(isStackEmpty(&st) != 1)
    {
        char stele = pop(&st);
        char quele = dequeue(&qu);
        if(stele == quele)  
        {
            continue;
        }
        return 0;
    }    
    return 1;
    
}


/*
*   Function: stringToQueue
*   -----------------------
*   stringToQueue function will take string constant as argument and 
*   stores that string into the queue data structure
*   Then it returns Queue
*
*   str: string constant
*/
struct queue stringToQueue(char * str)
{
    
    int index = 0;
    struct queue  qu;
    qu.front = -1;
    qu.rear  = -1;
    char temp;
    while(temp != '\n')
    {   
        temp = str[index++];
        enqueue(&qu, temp);
    }

    return qu;
    
}


/*
*   Function: stringToStack
*   -----------------------
*   stringToStack function will take string constant as argument and 
*   stores that string into the stack data structure
*   Then it returns Stack
*
*   str: string constant
*/
struct stack stringToStack(char * str)
{
    struct stack st;
    st.top    = -1;
    int index = 0;
    char temp = str[index];
    
    while(temp != '\n')
    {
        push(&st, temp);
        temp = str[++index];
    }
    return st;
}


/*
*   Function: isStackEmpty
*   ----------------------
*   isStackEmpty functionwill take the stack structure argument and returns
*   1 if the stack is empty else returns 0
*   
*   st: stack structure pointer
*/
int isStackEmpty(struct stack * st)
{
    return st -> top == -1 ? 1 : 0;
}


/*
*   Function: isQueueEmpty
*   ----------------------
*   isQueueEmpty functionwill take the Queue structure argument and returns
*   1 if the Queue is empty else returns 0
*   
*   Checking: if the front pointer and rear pointer are at the same location and
*   equals to -1 then the Queue will be empty, Another condition is that if the 
*   front pointer crosses the rear pointer on pop operations then the Queue is 
*   said to be empty
*   
*   st: Queue structure pointer
*/
int isQueueEmpty(struct queue * qu)
{
    return (qu -> front == -1 && qu -> rear == -1)
            ||
            (qu -> front == qu -> rear + 1) ? 1 : 0;
}

/*
*   Function: push
*   --------------------
*   stack_push function demostrates the normal stack push operation where is 
*   pushes the ele to the stack sent to the function
*
*   st  : stack structure pointer
*   ele : Elementor character that need to be pushed into the stack
*/
void push(struct stack * st, char ele)
{
    (st -> top) ++;
    st -> data[st -> top] = ele;
}


/*
*   Function: pop
*   -------------------
*   stack_pop function demonstrates the normal stack pop operation where it 
*   returns the stack top pointer character and decreases the top stack pointer
*
*   st: stack structure pointer
*   returns the character pointed bt top pointer of stack
*/
char pop(struct stack * st)
{
    if(isStackEmpty(st))
    {
        return '\0';
    }
    char ch = st -> data[st -> top];
    (st -> top)--;
    return ch;
}

/*
*   Function: enqueue
*   -----------------
*   Enqueue function demonstrates us the element insertion in the queue data
*   array on FIFO order and increases the rear pointer
*   If the Queue is empty then both top front and rear pointer increases by 1
*
*   ele: element that we are going to push into the Queue
*   qu: Queue structure pointer
*/
void enqueue(struct queue * qu, char ele)
{
    if(isQueueEmpty(qu))
    {
        (qu -> front)++;
    }
    (qu -> rear) ++;
    qu -> data[qu -> rear] = ele;
}

/*
*   Function: dequeue
*   -----------------
*   Dequeue function demonstrates us the element removal from the queue data
*   array on FIFO order and increases the front pointer
*
*   qu: Queue structure pointer
*/
char dequeue(struct queue * qu)
{
    if(isQueueEmpty(qu))
    {
        return '\0';
    }
    char ch = qu -> data[qu -> front];
    (qu -> front) ++;

    return ch;
}