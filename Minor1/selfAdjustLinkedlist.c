#include<stdio.h>
#include<stdlib.h>

/*
*   Linkedlist node structure
*
*/
struct node
{
    int data;
    struct node *next;
};
//Defining datatype of type struct node
typedef struct node NODE;

/*
*   Function: createNewNode
*   -----------------------
*   It creates a node with the given element and returns
*
*   INPUT:
*   ele : element of a node which we need to create
*
*   OUTPUT:
*   returns the node of the list with the given element
*/
NODE * createNewNode(int ele)
{
    NODE * newnode = malloc(sizeof(NODE));
    newnode -> data = ele;
    newnode -> next = NULL;

    return newnode;
}

/*
*   Function: insertEle
*   -------------------
*   It takes care of inserting the given element at the front of the 
*   linkedlist
*
*   INPUT: 
*   head : linkedlist reference
*   ele  : The element which we need to insert at the front.
*/
void insertEle(NODE ** head, int ele)
{
    NODE * newnode = createNewNode(ele);
    if(*head == NULL)
    {
        *head = newnode;
        return;
    }
    /* Code for insert Last
        //NODE * temp = *head;
        //while(temp -> next != NULL)
        //{
        //    temp = temp -> next;
        //}
        //temp -> next = newnode;
    */
    NODE * temp      =  *head;
    *head            =  newnode;
    (*head) -> next  =  temp;
    return;
}

/*
*   Function: removeEle
*   -------------------
*   Removes the element from the front of the linkedlist
*   
*   **head : linkedlist reference
*   
*   OUTPUT:
*   Returns the removed element
*/
int removeEle(NODE ** head)
{
    int data  =  (*head) -> data;
    NODE * temp = *head;
    *head     =  (*head) -> next;
    free(temp);
    return data;
}

/*
*   Function: findElePos
*   --------------------
*   It finds the element ele in the linkedlist
*
*   INPUT:
*   *head : copy of the linkedlist head node
*   ele   : Elemenet ele for which we find the position
*
*   OUTPUT:
*   returns the index/position of the element ele if it exits
*   Else returns -1 which indicates not present
*/
int findElePos(NODE *head, int ele)
{
    int index = -1;
    if(head == NULL)
    {
        return index;
    }

    NODE *temp = head;
    while(temp != NULL)
    {
        index++;
        if(temp -> data == ele)
        {
            return index;
        }
        temp = temp -> next;
    }
    return -1;
}

/*
*   Function: changePosition
*   ------------------------
*   It changes the element position from the found index to first
*   To access later within least amount of time.
*
*   INPUT:
*   **head = linkedlist head node reference
*   index  = index of the element ele
*   ele    = element which we work on
*/

void changePosition(NODE ** head, int index, int ele)
{
    //Edge case...
    if(index == 0)
        return;
    NODE * trav = *head;
    NODE * prev = *head;
    while(index--)
    {   
        prev = trav;
        trav = trav -> next;
    }
    prev -> next      = trav -> next;
    NODE * newnode    =  createNewNode(ele);
    NODE * temp       =  *head;
    *head             =  newnode;
    (*head) -> next   =  temp;

    return;
    
}

/*
*   Function: printList
*   -------------------
*   It just prints the elements present in the linkedlist
*/
void printList(NODE * head)
{
    while(head != NULL)
    {
        printf("\n\n%d  ", head -> data);
        head = head -> next;
    }

}

/*
*   Funciton: freeLinkedList
*   ------------------------
*   It frees the space allocated dynamically using heap memory
*   It frees node by node
*   
*   INPUT :
*   node* = linkedlist head node copy
*/
void freeLinkedList(NODE * node)
{
    while(node != NULL)
    {
        NODE * temp =  node;
        node = node -> next;
        free(temp);
    }
}

int main()
{
    NODE * linkedlist = NULL;
    int choice;
    scanf("%d", &choice);

    while(choice != -1)
    {
        int ele;
        switch(choice)
        {
            case 1:
            {
                scanf("%d", &ele);
                insertEle(&linkedlist, ele);
                break;
            }
            case 2:
            {
                if(linkedlist == NULL)
                {
                    printf("LE ");
                    break;
                }
                printf("%d ", removeEle(&linkedlist));
                break;
            }
            
            case 3:
            {
                scanf("%d", &ele);
                int eleIndex = findElePos(linkedlist, ele);
                if(eleIndex == -1)
                {
                    printf("ENF ");
                    break;
                }
                printf("%d ", eleIndex);
                changePosition(&linkedlist, eleIndex, ele);
                break;
            }
            /*
            Out of interest
            case 4:
            {
                printList(linkedlist);
                break;
            }
            */
            
        }
        scanf("%d", &choice);
    }
    freeLinkedList(linkedlist);
    return 0;
}