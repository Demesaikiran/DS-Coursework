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

NODE * createNode(void * data)
{
    NODE * newnode   =  malloc(sizeof(NODE));
    newnode -> prev  =  NULL;
    newnode -> data  =  data;
    newnode -> next  =  NULL;
    return newnode;
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

void insertAtIndex(NODE ** head, void * data, int index)
{
    NODE * newnode = createNode(data);

    if(*head == NULL)
    {
        *head = newnode;
        return;
    }
    if(index == 0)
    {
        insertFirst(&(*head), data);
        return;
    }

    NODE * temp = *head;
    while(--index)
    {
        temp = temp -> next;
    }
    if(temp -> next == NULL)
    {
        insertLast(&(*head), data);
        return;
    }
    newnode -> next         =  temp -> next;
    (temp -> next) -> prev  =  newnode;
    newnode -> prev         =  temp;
    temp -> next            =  newnode;
    return;
}

void * removeFirst(NODE ** head)
{
    if(*head == NULL) return NULL;

    NODE * node =  *head;
    *head       =  (*head) -> next;
    void *data  =  node -> data;

    free(node);
    return data;
}

void * removeLast(NODE ** head)
{
    if(*head == NULL) return NULL;

    NODE * node = NULL;

    if((*head) -> next == NULL)
    {
        node   =  *head;
        *head  =  NULL;
    }
    else
    {
        NODE * traverse = *head;
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

void * removeAtIndex(NODE ** head, int index)
{

    NODE * traverse = *head;
    NODE * delnode = NULL;
    if(index == 0)
    {
        *head = (*head) -> next;
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

void displayList(NODE * head)
{
    NODE * temp = head;    

    while(temp != NULL)
    {
        printf("%s ", (char *) temp -> data);
        temp = temp -> next;
    }
    //free(temp -> data);
    free(temp);
    return;
}

void freeList(NODE * garbage)
{
    
    while(garbage != NULL)
    {
        NODE * temp =  garbage;
        garbage = (garbage) -> next;
        free(temp);
    }
    
}

int isListEmpty(NODE ** head)
{
    return *head == NULL ? 1 : 0;
}
int main()
{
    //void * data = NULL;
    NODE * head = NULL;
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
                insertFirst(&head, e);
                nodes++;
                break;
            }

            case 2:
            {
                // Insert element e at the tail of the list
                char * e = malloc(sizeof(char) * MAXSIZE);
                scanf("%s", e);
                insertLast(&head, e);
                nodes++;
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
                insertAtIndex(&head, e, index);
                nodes++;
                break;
            }

            case 4:
            {
                // Delete element from head of the list and display
                // The deleted element
                
                void * e = removeFirst(&head);
                if(e == NULL)
                {
                    printf("LE ");
                    break;
                }
                printf("%s ", (char *) e);
                nodes--;
                break;
                
            }

            case 5:
            {
                // delete element from tail of the list and display
                // The deleted element

                void * e = removeLast(&head);
                if(e == NULL)
                {
                    printf("LE ");
                    break;
                }
                printf("%s ", (char *) e);
                nodes--;
                break;
            }

            case 6:
            {
                // delete element at index i. If linked list currently has n elements
                // Then 0 to n-1 are the valid indices for i
                
                int i;
                scanf("%d", &i);
                if(isListEmpty(&head))
                {
                    printf("LE ");
                    break;
                }
                if(i >= nodes || i < 0)
                {
                    printf("INVALID INPUT");
                    return 0;
                }

                void * e = removeAtIndex(&head, i);
                printf("%s ", (char *) e);
                nodes--;
                break;
            }

            case 7:
            {
                //Display the list from head to tail
                if(isListEmpty(&head))
                {
                    break;
                }
                displayList(head);
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

    freeList(head);
}