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

int  isStackEmpty(STACK * st)
{
    if(st -> top == -1)
        return 1;
    return 0;
}

int  isStackFull(STACK * st)
{
    if(st -> top == st -> size -1)
        return 1;
    return 0;
}

int getTopElement(STACK * st)
{
    return st -> data[st -> top];
}

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
int pop(STACK * st)
{
    int ele = getTopElement(st);
    (st -> top)--;
    return ele;
}

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

int postfixEvaluation(char * exp, STACK * st)
{
    const char s[2] = " ";
    char * value;
    value = strtok(exp, s);
    
    while(value != NULL)
    {
        if(isOperator(value))
        {
            if(st -> top == 0)
            {
                st -> data[0] = calculateValue(value, 0, st -> data[0]);
            }

            else
            {
                int b = pop(st);
                int a = pop(st);
                if(b == 0 && value[0] == '/')
                {
                    printf("DIVBYZERO");
                }
                else
                {
                    push(st, calculateValue(value, a, b));
                }
            }
        }
        else
        {
            push(st, atoi(value));
        }

        value = strtok(NULL, s);
    }

    return st -> data[st -> top];
}

int main()
{
    STACK * st = createStack(4);
    char exp[100];
    fgets(exp, 100, stdin);

    int ans = postfixEvaluation(exp, st);
    printf("%d", ans);
    return 0;

}