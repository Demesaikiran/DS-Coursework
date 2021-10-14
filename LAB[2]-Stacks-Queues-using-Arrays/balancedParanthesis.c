#include<stdio.h>
#include<stdlib.h>

#define SIZE 100
struct stack
{
    int top;
    char data[SIZE];
};

int isStackEmpty(struct stack * st);
void push(struct stack *st, char ele);
void pop(struct stack * st);
int checkBalancedParanthesis(struct stack * st);


int main()
{
    struct stack st;
    st.top = -1;

    //Getting large string as input
    fgets(st.data, SIZE, stdin);
    //input validation
    if(st.data[0] == '\n')
    {
        printf("1");
        return 0;
    }

    int cbp = checkBalancedParanthesis(&st);
    if(cbp == 1)
    {
        printf("1");
        return 0;
    }
    printf("0");
    return 0;

}

/*
* Function: checkBalancedParanthesis
* ------------------------------------
*  It checks whether it has equal number of closing and opening braces
*  Returns 1 if the condition satisfied
*  Else it returns zero
*
*  st: stack pointer
*/
int checkBalancedParanthesis(struct stack * st)
{
    int i=0;
    char ch;
    do
    {
        ch = st -> data [i++];
        if(ch == '{')
        {
            if(st -> data[st -> top] == '}')
            {
                pop(st);
            }
            else
            {
                push(st, '{');
            }
            continue;
        }
        if(ch == '}')
        {
            if(st -> data[st -> top] == '{')
            {
                pop(st);
            }
            else
            {
                push(st, '}');
            }
        }
    } while (ch != '\n');

    return isStackEmpty(st);
    
}
/* 
 ---------------This code is for paired paranthesis-------------------
int checkBalancedParanthesis(struct stack * st)
{
    int i=0;
    char ch;
    do
    {
        ch = st -> data[i++];
        if(ch == '{')
        {
            push(st, '{');
            continue;
        }
        if(ch == '}')
        {
            if(isStackEmpty(st))
            {
                return 0;
            }
            pop(st);
        }
        
    }
    while(ch != '\n');
    
    return isStackEmpty(st);
}
*/

/*
* Function: isStackEmpty
* -----------------------
*  It justs takes the stack as an argumanet and checks whether it is empty or not
*  It returns the value '1' if the stack is empty and 
*  0 if it is not empty
*
*  st: stack pointer
*/
int isStackEmpty(struct stack *st)
{
    printf("%d", st -> top);
    if(st -> top == -1)
    {
        return 1;
    }
    return 0;
}

/*
* Funtion: push
* ------------------
*  It pushes the element to the stack passed by the user 
*  
*  st: Stack where we try to push the element
*  ele: The element which we wanted to push to the stack
*/
void push(struct stack * st, char ele)
{
    //Incrementing the top variale of stack and 
    //assigning element to the data of top pointed index
    (st -> top)++;
    st -> data[st -> top] = ele;
}

/*
* Function: pop
* -------------------
*  It pops out the element that is top of stack and returns also decreases the top pointer
* 
*  st: Stack where we try to pop the top most element
*/
void pop(struct stack * st)
{
    // In one single expression we are decreasing the top variable and 
    // also sending the top element to the called function
    (st -> top)--;
    //return ( );
}

