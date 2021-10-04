/*
*   StackPostFix.c 
*   --------------
*   This program demonstrates us how the postfix expression is getting evaluated
*   using stack and how stack is increasing its size by twice
*   
*   Deme Sai Kiran 2021
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
*   Stack Blueprint with top pointer, size of stack and the data pointer which 
*   Which points to the array of size mentioned
*
*/
struct stack
{
    int top;
    int size;
    int * data;
};
//Creating STACK def type struct stack
typedef struct stack STACK;

/*
*   Function: createStack
*   ---------------------
*   This function demonstrates us how the stack with given size creates and 
*   returns the stack to the called function
*
*   size: It is the size of the stack that is first started with(container - 4)
*/
STACK * createStack(int size)
{
    STACK * st  =  malloc(sizeof(STACK));
    st -> top   =  -1;
    st -> size  =  size;
    st -> data  =  malloc(sizeof(int) * size);

    return st;
}

/*
*   Function: isStackEmpty
*   ------------------
*   isStackEmpty function demonstrates us either the stack is empty or not and
*   returns 1 if the queue is empty where top will be -1 else returns 0
*   
*   st: It is the pointer to the type STACK
*/
int  isStackEmpty(STACK * st)
{
    if(st -> top == -1)
        return 1;
    return 0;
}

/*
*   Funciton: isStackFull
*   -----------------
*   isStackFull demonstrates us that it returns the value 1 if the stack is full
*   By checking top variable comparing with size - 1 else returns 0
*
*/
int  isStackFull(STACK * st)
{
    if(st -> top == st -> size -1)
        return 1;
    return 0;
}


/*
*   Function: getTopElement
*   -----------------------
*   getTopElement demonstrates us that it returns the integer from the stack
*   Where top variable is pointing to the stack.
*
*/
int getTopElement(STACK * st)
{
    return st -> data[st -> top];
}


/*
*   Function: push
*   --------------
*   push function demonstrates us that pushing and element ele onto the stack
*   It also demonstrates us the at how to double the size of stack memory
*   dynamically.
*
*   ele: It is an element that we need to push on to the stack.
*/

void push(STACK * st, int ele)
{
    if(isStackEmpty(st))
    {
        st -> top       =  0;
        st -> data[0]   =  ele;
        return;
    }
    
    if(isStackFull(st))
    {
        int * d     =  st -> data;
        int size    =  st -> size;
        st -> data  =  malloc(sizeof(int) * 2 * size);
        st -> size  =  size * 2;

        for(int i = 0; i < size; i++)
        {
            st -> data[i] = d[i];
        }

        st -> top              =  size;
        st -> data[st -> top]  =  ele;
        free(d);
        return;
    }

    ++(st -> top);
    st -> data[st -> top] = ele;
    return;

}


/*
*   Funciton: pop
*   -------------
*   Pop funciton demonstrates us that deleting an element from the stack using
*   LIFO mechanism
*
*/
int pop(STACK * st)
{
    int ele = getTopElement(st);
    (st -> top)--;
    return ele;
}


/*
*   Funciton: calculateValue
*   ------------------------
*   calculateValue demonstrates us that the arithmetic operation of two elements
*   a and b with operator denoting with op
*
*   op: string constant with an operator inside
*   a, b: integers where we are going to find the arithmetic operation b/w them
*
*/

int calculateValue(char * op, int a, int b)
{
    switch(op[0])
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}


/*
*   Function: isOperator:
*   --------------------
*   isOperator function demonstrates us that returning 1 if the input is an
*   arithmetic operator (+, -, *, /) else returns 0;
*
*   temp: string constant which may contain operator or an integer
*/
int  isOperator(char * temp)
{
    switch(temp[0])
    {
        case '+':
        case '-':
        case '*':
        case '/':
            return 1;
        default:
            return 0;
    }
}


/*
*   Funciton: postfixEvaluation
*   ---------------------------
*   postfixEvaluation function demonstrates us finding value of the expression
*   present in postfix condition and returns the value.
*
*   exp: postfix expression (string) which we need to solve
*/
int postfixEvaluation(char * exp, STACK * st)
{
    const char s[2] = " \n";
    char * value;
    // strtok takes data by data with the delimeter provided - s
    value = strtok(exp, s);
    
    // If we exhaust the value of expression then it stores NULL
    // Which acts as breaking point
    while(value != NULL)
    {
        if(isOperator(value))
        {
            // data[0] because the arithmetic operator will be of size one
            // We can compare with only one char value.
            if(st -> top == 0)
            {
                st -> data[0] = calculateValue(value, 0, st -> data[0]);
            }

            else
            {
                int b = pop(st);
                int a = pop(st);
                
                // Dividing by zero evaluation
                if(b == 0 && value[0] == '/')
                {
                    printf("DIVBYZERO");
                    exit(1);
                }
                else
                {
                    push(st, calculateValue(value, a, b));
                }
            }
        }
        else
        {
            // Converting the string value to integer
            push(st, atoi(value));
        }

        value = strtok(NULL, s);
    }

    return st -> data[st -> top];
}

int main()
{
    // Creating stack of size 4 integers
    STACK * st = createStack(4);
    char exp[100];
    fgets(exp, 100, stdin);

    int ans = postfixEvaluation(exp, st);
    printf("%d", ans);
    return 0;

}