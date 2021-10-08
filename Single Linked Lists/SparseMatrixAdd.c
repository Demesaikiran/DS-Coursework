#include<stdio.h>
#include<stdlib.h>

struct element
{
    int row;
    int col;
    int val;
};
typedef struct element ELE;

struct node
{
    ELE * e;
    struct node * next;
};
typedef struct node NODE;

NODE * createNode(int row, int col, int val)
{
    ELE * ele = malloc(sizeof(ELE));
    ele -> row = row;
    ele -> col = col;
    ele -> val = val;
    NODE * newnode = malloc(sizeof(NODE));
    newnode -> e = ele;
    newnode -> next = NULL;

    return newnode;
}

void insertFront(NODE ** head, int row, int col, int val)
{
    NODE * newnode = createNode(row, col, val);

    if(*head == NULL)
    {
        *head = newnode;
        return;
    }
    newnode -> next = *head;
    *head = newnode;
    return;
}

void printList(NODE * travel)
{
    printf("Linked List: ");
    while(travel != NULL)
    {
        ELE * ele = travel -> e;
        printf("(%d, %d, %d) -> ", ele -> row, ele -> col, ele -> val);
        travel = travel -> next;
    }
    printf("X\n");
}

void insertLast(NODE ** head, int row, int col, int val)
{
    NODE * newnode = createNode(row, col, val);

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

void insertAtIndex(NODE ** head, int row, int col, int val, int k)
{
    NODE * newnode = createNode(row, col, val);
    if(*head == NULL)
    {
        *head = newnode;
        return;
    }

    NODE * travel = *head;
    while(--k && travel -> next != NULL)
    {
        travel = travel -> next;
    }

    newnode -> next =  travel -> next;
    travel -> next  =  newnode;
    return;
}

int validInput(int row, int col, int r, int c)
{
    return (r < 0 || r > row - 1 || c < 0 || c > col - 1) ? 0 : 1;
}

int IndexPresent(NODE * head, int row, int col)
{
    NODE * travel = head;
    int count = 0;
    while(travel == NULL)
    {
        if((travel -> e -> row == row) && (travel -> e -> col == col))
        {
            return count;
        }
        travel = travel -> next;
        count++;
    }
    return ++count;
}

void insertNext(NODE ** head1, NODE ** head2)
{
    NODE * newnode     =  createNode((*head2) -> e -> row, (*head2) -> e -> col, (*head2) -> e -> val);
    NODE * temp        =  (* head1) -> next;
    (* head1) -> next  =  newnode;
    newnode -> next    =  temp;
}

int indexPosition(NODE * node1, NODE * node2)
{
    // 0 : same index elements
    // 1 : Either Same row but greater column or Greater column
    // 2 : node1 row is greater than node2 row
    if ((node1 -> e -> row == node2 -> e -> row))
    {
        if(node1 -> e -> col == node2 -> e -> col)
            return 0;
        if(node1 -> e -> col < node2 -> e -> col)
            return 1;
        // Same row but node2 element occurs first
        return 2;
    }
    if(node1 -> e -> row < node2 -> e -> row)
        return 1;

    return 2;
}

void addSparseMatrix(NODE ** head1, NODE ** head2, int head1len, int head2len)
{
    //Edge cases
    if(head2len == 0) 
        return;
    if(head1len == 0) 
    {
        * head1 = * head2;
        return;
    }

    NODE * travel1     = * head1;
    NODE * travel1prev = NULL;
    NODE * travel2     = * head2;

    while(travel1 != NULL)
    {   
        int position = indexPosition(travel1, travel2);

        switch(position)
        {
            case 0:
            {
                travel1 -> e -> val += travel2 -> e -> val;
                travel1prev = travel1;
                travel1 = travel1 -> next;
                travel2 = travel2 -> next; 
                break;
            }
            // If same row and node2 has Bigger Column or (Bigger row)
            case 1:
            {
                travel1prev = travel1;
                travel1 = travel1 -> next;
                break;
            }
            // Occurs first than the matrix one element in list - 1
            case 2:
            {
                if(travel1prev == NULL)
                {
                    insertFront(&(*head1), travel2 -> e -> row, travel2 -> e -> col, travel2 -> e -> val);
                    travel1prev = * head1;
                }
                else
                {
                    insertNext(&travel1prev, &travel2);
                    travel1prev = travel1prev -> next;
                }
                travel1 = travel1prev -> next;
                travel2 = travel2 -> next;
                break;
            }
        }
    }
    travel1prev -> next = travel2;

}


int main()
{
    // Taking dimensions of the matrix
    int row, col;
    scanf("%d%d", &row, &col);
    // Taking number of non zero elements in both matrices
    int mat1, mat2;
    scanf("%d%d", &mat1, &mat2);
    int r, c, val;

    NODE * mat1head = NULL;
    NODE * mat2head = NULL;

    for( int i = 0; i < mat1; i++)
    {
        scanf("%d%d%d", &r, &c, &val);
        //NODE * temp = createNode(r, c, val);
        if(!validInput(row, col, r, c))
        {
            free(mat1head);
            free(mat2head);
            printf("INVALID INPUT");
            return 0;
        }
        insertLast(&mat1head, r, c, val);
    }

    for(int i = 0; i < mat2; i++)
    {
        scanf("%d%d%d", &r, &c, &val);
        if(!validInput(row, col, r, c))
        {
            free(mat1head);
            free(mat2head);
            printf("INVALID INPUT");
            return 0;
        }
        insertLast(&mat2head, r, c, val);
    }

    addSparseMatrix(&mat1head, &mat2head, mat1, mat2);

    printList(mat1head);

    if(mat1 != 0) free(mat2head);
    free(mat1head);

    return 0;

}


