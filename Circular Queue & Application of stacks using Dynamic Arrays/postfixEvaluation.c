#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack
{
    int top;
    int size;
    int * data;
};

typedef struct stack STACK;

STACK * createStack(int size)
{
    STACK * st  =  malloc(sizeof(STACK));
    st -> top   =  -1;
    st -> size  =  size;
    st -> data  =  malloc(sizeof(int) * size);

    return st;
}

int * isStackEmpty(STACK * st)
{
    if(st -> top == -1)
        return NULL;
}

int * isStackFull(STACK * st)
{
    if(st -> top == st -> size -1)
        return NULL;
}

void push(STACK * st, int ele)
{
    if(!(isStackEmpty(st)))
    {
        st -> top       =  0;
        st -> data[0]   =  ele;
        return;
    }
    
    if(!(isStackFull(st)))
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

    st -> top += 1;
    st -> data[st -> top] = ele;
    return;

}   

int postfixEvaluation(char * exp)
{
    char s[2] = " ";
    char * value;
    value = strtok(exp, s);
    while(exp != NULL)
    {
        

        value = strtok(NULL, s);
    }
}



int main()
{
    STACK * st = createStack(4);
    char * exp;

    int ans = postfixEvaluation(exp);

    printf("%d", ans);

}