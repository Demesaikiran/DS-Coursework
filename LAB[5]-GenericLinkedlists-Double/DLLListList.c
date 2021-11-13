#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 50
typedef struct node NODE;
struct node
{
    NODE * prev;
    void * data;
    NODE * next;
};

typedef struct list LIST;
struct list
{
    NODE * head;
    NODE * tail;
    int size;
};

NODE * createNode(void * data)
{
    NODE * newnode   =  malloc(sizeof(NODE));
    newnode -> prev  =  NULL;
    newnode -> data  =  data;
    newnode -> next  =  NULL;
    return newnode;
}

LIST * createList()
{
    LIST * listnode = malloc(sizeof(LIST));
    listnode -> head = NULL;
    listnode -> tail = NULL;
    listnode -> size = 0;
    return listnode;
}
void insertFirst(NODE ** head, void * data)
{
    NODE * newnode = createNode(data);
    if(*head == NULL)
    {
        *head = newnode;
        return;
    }

    (*head) -> prev   =  newnode;
    newnode -> next   =  *head;
    *head             =  newnode;

    return;
}

void insertLast(NODE ** head, void * data)
{
    NODE * newnode = createNode(data);

    if(*head == NULL)
    {
        *head = newnode;
        return;
    }

    NODE * temp = *head;

    while(temp -> next != NULL)
    {
        temp = temp -> next;
    }
    temp -> next     =  newnode;
    newnode -> prev  =  temp;
    return;
}

void insertAtIndex(LIST ** _list, void * data, int index)
{
    NODE * newnode = createNode(data);

    if(isListEmpty(&(*_list)))
    {
        (*_list) -> head = newnode;
        return;
    }
    if(index == 0)
    {
        insertFirst(&(*_list), data);
        return;
    }

    NODE * temp = (*_list) -> head;
    while(--index)
    {
        temp = temp -> next;
    }
    if(temp -> next == NULL)
    {
        insertLast(&(*_list), data);
        return;
    }
    newnode -> next         =  temp -> next;
    (temp -> next) -> prev  =  newnode;
    newnode -> prev         =  temp;
    temp -> next            =  newnode;
    return;
}

void * removeFirst(LIST ** _list)
{
    if(isListEmpty(&(*_list))) return NULL;

    NODE * node       =  (*_list) -> head;
    (*_list) -> head  =  (*_list) -> head -> next;
    void *data        =  node -> data;

    free(node);
    return data;
}

void * removeLast(LIST ** _list)
{
    if(isListEmpty(&(*_list))) return NULL;

    NODE * node = NULL;

    if((*_list) -> head -> next == NULL)
    {
        node   =  (*_list) -> head;
        (*_list) -> head  =  NULL;
    }
    else
    {
        NODE * traverse = *_list;
        while(traverse -> next -> next != NULL)
        {
            traverse = traverse -> next;
        }

        node              =  traverse -> next;
        traverse -> next  =  NULL;
    }
    void * data = node -> data;
    free(node);
    return data;
}

void * removeAtIndex(LIST ** _list, int index)
{

    NODE * traverse = (*_list) -> head;
    NODE * delnode = NULL;
    if(index == 0)
    {
        (*_list) -> head = (*_list) -> head -> next;
        delnode = traverse;
        
    }
    else
    {
        while(--index)
        {
            traverse = traverse -> next;
        }

        delnode           =  traverse -> next;
        traverse -> next  =  traverse -> next -> next;

        //If the removing element is last node...
        if(traverse -> next != NULL)
            (traverse -> next) -> prev  =  traverse; 
    }

    void * data = delnode -> data;
    free(delnode);
    return data;
}

void displayList(LIST * mylist)
{
    NODE * temp = mylist -> head;    

    while(temp != NULL)
    {
        printf("%s ", (char *) temp -> data);
        temp = temp -> next;
    }
    //free(temp -> data);
    free(temp);
    return;
}

void freeList(LIST * garbage)
{
    
    while(garbage != NULL)
    {
        NODE * temp =  garbage -> head;
        garbage = (garbage) -> head -> next;
        free(temp);
    }
    free(garbage);
    
}

int isListEmpty(LIST ** garb)
{
    return (*garb) -> size == 0 ? 1 : 0;
}

int main()
{
    //void * data = NULL;
    //NODE * head = NULL;
    LIST * mylist = createList();
    int nodes = 0;

    int choice;
    scanf("%d", &choice);
    while(choice != -1)
    {
        switch(choice)
        {
            case 1:
            {
                //Insert element e at the head of the list
                char * e = malloc(sizeof(char) * MAXSIZE);
                scanf("%s", e);
                insertFirst(&mylist, e);
                mylist -> size ++;
                break;
            }

            case 2:
            {
                // Insert element e at the tail of the list
                char * e = malloc(sizeof(char) * MAXSIZE);
                scanf("%s", e);
                insertLast(&mylist, e);
                mylist -> size++;
                break;
            }

            case 3:
            {
                // Insert element e at the index i. starts from 0.
                // If linekd list currently has n elements then 0 to n are the valid
                // indices for i

                int index;
                scanf("%d", &index);
                if(index > nodes || index < 0)
                {
                    printf("INVALID INPUT");
                    return 0;
                }
                char * e = malloc(sizeof(char) * MAXSIZE);
                scanf("%s", e);
                insertAtIndex(&mylist, e, index);
                mylist -> size++;
                break;
            }

            case 4:
            {
                // Delete element from head of the list and display
                // The deleted element
                
                void * e = removeFirst(&mylist);
                if(e == NULL)
                {
                    printf("LE ");
                    break;
                }
                printf("%s ", (char *) e);
                mylist -> size--;
                break;
                
            }

            case 5:
            {
                // delete element from tail of the list and display
                // The deleted element

                void * e = removeLast(&mylist);
                if(e == NULL)
                {
                    printf("LE ");
                    break;
                }
                printf("%s ", (char *) e);
                mylist -> size--;
                break;
            }

            case 6:
            {
                // delete element at index i. If linked list currently has n elements
                // Then 0 to n-1 are the valid indices for i
                
                int i;
                scanf("%d", &i);
                if(isListEmpty(&mylist))
                {
                    printf("LE ");
                    break;
                }
                if(i >= nodes || i < 0)
                {
                    printf("INVALID INPUT");
                    return 0;
                }

                void * e = removeAtIndex(&mylist, i);
                printf("%s ", (char *) e);
                mylist -> size--;
                break;
            }

            case 7:
            {
                //Display the list from head to tail
                if(isListEmpty(&mylist))
                {
                    break;
                }
                displayList(mylist);
                break;
            }

            default:
            {
                printf("INVALID INPUT");
                return 0;
            }
        }
        scanf("%d", &choice);
    }

    freeList(mylist);
}