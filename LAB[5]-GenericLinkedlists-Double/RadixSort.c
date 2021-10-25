#include<stdio.h>
#include<stdlib.h>

typedef struct node NODE;
struct node
{
    void * data;
    NODE * next;
};

NODE * createnewNode(void * ele)
{
    NODE * newnode = malloc(sizeof(NODE));
    newnode -> data = ele;
    newnode -> next = NULL;
    return newnode;
}

void insertFront(NODE ** list, void * ele)
{
    NODE * newnode = createnewNode(ele);
    if(*list == NULL)
    {
        *list = newnode;
    }
    else
    {
        newnode -> next = *list;
        *list = newnode;
    }
    return;

}

void insertLast(NODE ** list, void * ele)
{
    NODE * newnode = createnewNode(ele);
    if(*list == NULL)
    {
        *list = newnode;
    }
    else
    {
        NODE * temp = *list;
        while(temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = newnode;
    }
    return;
}

void displayList(NODE * list)
{
    while(list != NULL)
    {
        printf("%d ", *((int *) list -> data)); 
        list = list -> next;
    }
    return;
}

int createList(NODE ** list, int size)
{
    if(size <= 0) return 0;
    for(int i = 0; i < size; i++)
    {
        int * ele = malloc(sizeof(int));
        scanf("%d", ele);
        if(*ele < 0) return 0;
        insertLast(&(*list), ele);
    }
    return 1;
}

void freeList(NODE * list)
{
    while(list != NULL)
    {
        NODE * temp  =  list;
        list         =  list -> next;
        free(temp);
    }
    return;
}


int LargeSizedDigit(NODE * list)
{
    int max = *((int *)list -> data);
    while(list != NULL)
    {
        if(*((int *)list -> data) > max)
        {
            max = *((int *)list -> data);
        }
        list = list -> next;
    }

    int digitCount = 0;
    while(max != 0)
    {
        digitCount++;
        max /= 10;
    }
    return (digitCount);

}

int digitAtLocation(void* number, int loc)
{
    int a = *((int *) number);
    int digit, count;

    for(int i = 1; i <= loc; i++)
    {
        digit = a % 10;
        a = a / 10;
    }
    return digit;
}

void radixSort(NODE ** list, int size)
{
    NODE * front[10], *end[10], *temp;
    int digit;

    int numLen = LargeSizedDigit(*list);

    for(int i = 1; i <= numLen; i++)
    {
        // Making the entries to NULL for further calculations after a repetition
        for(int traverse = 0; traverse <= 9; traverse++)
        {
            front[traverse] = NULL;
            end[traverse]   = NULL;
        }

        for(temp = *list; temp != NULL; temp = temp -> next)
        {
            digit = digitAtLocation(temp -> data, i);
            printf("%d\n", digit);

            if(front[digit] == NULL)
                front[digit] = temp;
            else
                end[digit] -> next = temp;
            
            end[digit] = temp;
        }

        // Getting the starting node from the front array pointer
        // Traversing till we get NULL

        int travel = 0;
        while(front[travel] == NULL)
            travel++;

        *list = front[travel];
        while(travel < 9)
        {
            if(end[travel + 1] != NULL)
                end[travel] -> next = front[travel + 1];
            
            else
                end[travel + 1] = end[travel];
            travel++;
        }

        // Ending the list with NULL
        end[travel] -> next = NULL;
    }
}

int main()
{
    NODE * list = NULL;
    int count, limit;

    int listlen;
    scanf("%d", &listlen);
    int status = createList(&list, listlen);
    if(status != 1)
    {
        printf("INVALID INPUT");
        return 0;
    }
    radixSort(&list, listlen);
    displayList(list);
    freeList(list);
}
