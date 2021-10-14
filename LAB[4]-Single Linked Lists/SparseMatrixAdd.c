#include<stdio.h>
#include<stdlib.h>

// Matrix element Structure
struct element
{
    int row;
    int col;
    int val;
};
typedef struct element ELE;

// Linked list node Structure
struct node
{
    ELE * e;
    struct node * next;
};
typedef struct node NODE;

/*
*   Function: createNode
*   --------------------
*   Creates the Linkedlist node with given details
*   
*   INPUT:
*   row : row index value of element
*   col : column index value of element
*   val : value at [row][column] of a matrix element
*
*   OUTPUT:
*   Address of created Node
*/
NODE * createNode(int row, int col, int val)
{
    ELE * ele        =  malloc(sizeof(ELE));
    ele -> row       =  row;
    ele -> col       =  col;
    ele -> val       =  val;
    NODE * newnode   =  malloc(sizeof(NODE));
    newnode -> e     =  ele;
    newnode -> next  =  NULL;

    return newnode;
}

/*
*   Function: insertFront
*   ---------------------
*   Inserts linkedlist node with the attributes given to the front of linked list
*
*   INPUT:
*   head : Linked list reference
*/
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

/*
*   Function: printList
*   -------------------
*   Prints the linkedlist indicating the attribute values 
*   row, column, value
*   
*   INPUT:
*   travel : Linkedlist copy
*/
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

/*
*   Function: insertLast
*   --------------------
*   Adds the node with the values row, column, value to the end of the list
*   
*   INPUT:
*   head          : linkedlist reference
*   row, col, val : matrix indexed value
*/
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

/*
*   Function: insertAtIndex
*   -----------------------
*   inserts a node wit hvalues row, col, val at kth index
*   of linkedlist
*   
*   INPUT:
*   head          : linedlist reference
*   row, col, val : matrix indexed value
*   k             : kth position in likedlist- considering 0 index based
*/
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

/*
*   Function: validNonZeroElements
*   ------------------------------
*   Validates the input whether number of non -zero elements exceeding
*   the total number of elements (row * col)
*   
*   INPUT:
*   row, col : Number of rows and Number of columns of a matrix
*   m1, m2   : Number of non zero elements in matrix-1 and matrix-2
*
*   OUTPUT:
*   Outputs 1 if number of non zero elements entered <= actual # of elements
*   Outputs 0 if number of non zero elements entered > actual # of elements
*/
int validNonZeroElements(int row, int col, int m1, int m2)
{
    return (row * col < m1 || row * col < m2 ) ? 0 : 1;
}

/*
*   Function: validInput
*   --------------------
*   Validates the entered row, column, input with the first
*   given matrix dimensions row and col
*
*   INPUT:
*   row, col : first input from user that matrix dimensions are row X column
*   r, c     : Step input from the user to add it in the linked list
*
*   OUTPUT:
*   Returns 1 if input r lies between 0 and row - 1 including 0 and lly for column
*   Else returns 0
*/
int validInput(int row, int col, int r, int c)
{
    return (r < 0 || r > row - 1 || c < 0 || c > col - 1) ? 0 : 1;
}

/*
*   Funciton: createMatrix
*   ----------------------
*   It creates the linkedlist of row, col, value nodes and adds it to the last
*   
*   INPUT:
*   head     : matrix reference
*   row, col : The generic row and column given by the user
*   size     : Number of non zero elements need to insert into the list
*/
int createMatrix(NODE ** head, int size, int row, int col)
{
    int r, c, val;
    for(int current = 0; current < size; current++)
    {
        scanf("%d%d%d", &r, &c, &val);
        if(!(validInput(row, col, r, c)))
        {
            return 0;
        }
        insertLast(&(*head), r, c, val);
    }
    return 1;
}

/*
*   Function: IndexPresent
*   ----------------------
*   Returns the index at which the same index present in matrix - 2
*
*   INPUT:
*   head : matrix - 2 linkedlist copy
*   row, col : matrix - 1 linkedlist element index
*
*   OUTPUT:
*   Returns the index( Using Var count)
*   Else it returns the count greater than the non zero elements
*   Which represents searching index is not present in matrix - 2
*/
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

/*
*   Function: insertNext
*   --------------------
*   Inserts the pointed node of matrix-2 with same value of it to the next of pointed node
*   of matrix -1 linedlist
*
*   INPUT:
*   head1 : Reference of matrix - 1 from pointed place
*   head2 : Reference of matrix - 2 from pointed place
*/
void insertNext(NODE ** head1, NODE ** head2)
{
    ELE * element      =  (*head2) -> e;
    NODE * newnode     =  createNode(element -> row, element -> col, element -> val);
    NODE * temp        =  (* head1) -> next;
    (* head1) -> next  =  newnode;
    newnode -> next    =  temp;
    free(element);
}

/*
*   Function: indexPosition
*   -----------------------
*   It defines whether the matrix - 2 node index and matrix - 1 node index is same 
*   or smaller index and greater index than other
*
*   INPUT:
*   node1 : matrix - 1 pointed node copy
*   node2 : matrix - 2 pointed node copy
*
*   OUTPUT:
*   0 : same index elements
*   1 : Either Same row but greater column or Greater column
*   2 : node1 row is greater than node2 row
*/
int indexPosition(NODE * node1, NODE * node2)
{
    //Edge cases
    if(node1 == NULL) return 2;
    if(node2 == NULL) return 1;

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


void copyList(NODE ** node, NODE * reference)
{
    ELE *temp = NULL;
    while(reference != NULL)
    {
        temp      = reference -> e;
        insertLast(&(*node), temp -> row, temp -> col, temp -> val);
        reference = reference -> next;
    }
}
/*
*   Function: addSparseMatrix
*   -------------------------
*   Adds the two matrices matrix - 1 and matrix - 2 
*
*   INPUT:
*   head1    : matrix - 1 reference
*   head2    : matrix - 2 reference
*   head1len : Number of non-zero elements in matrix - 1
*   head2len : Number of non-zero elements in matrix - 2
*
*   OUTPUT:
*   Returns added linkedlist to the called function
*/
NODE * addSparseMatrix(NODE * head1, NODE * head2, int head1len, int head2len)
{
    NODE * resMatrix = NULL;
    ELE * tempEle   = NULL;
    //Edge cases
    if(head2len == 0) 
    {
        copyList(&resMatrix, head1);
        return resMatrix;
    }
    if(head1len == 0) 
    {
        copyList(&resMatrix, head2);
        return resMatrix;
    }

    NODE * travel1     =  head1;
    NODE * travel2     =  head2;

    while(travel1 != NULL || travel2 != NULL)
    {   
        int position = indexPosition(travel1, travel2);

        switch(position)
        {
            case 0:
            {
                tempEle = travel1 -> e;
                insertLast(&resMatrix, tempEle -> row, tempEle -> col, tempEle -> val + travel2 -> e -> val);
                travel1 =  travel1 -> next;
                travel2 =  travel2 -> next; 
                break;
            }
            // If same row and node2 has Bigger Column or (Bigger row)
            case 1:
            {
                tempEle = travel1 -> e;
                insertLast(&resMatrix, tempEle -> row, tempEle -> col, tempEle -> val);
                travel1      =  travel1 -> next;
                break;
            }
            // Occurs first than the matrix one element in list - 1
            case 2:
            {
                tempEle = travel2 -> e;
                insertLast(&resMatrix, tempEle -> row, tempEle -> col, tempEle -> val);
                travel2 = travel2 -> next;
                break;
            }
        }
    }

    return resMatrix;

}

/*
*   Function: printans
*   ------------------
*   It just prints the added matrix to the terminal / output
*
*   INPUT:
*   output   : matrix copy
*   row, col : number of rows and columns of a matrix
*/
void printans(NODE * output, int row , int col)
{

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(output != NULL && output -> e -> row == i && output -> e -> col == j)
            {
                printf("%d ",output -> e -> val);
                output = output -> next;
                continue;
            }
            printf("0 ");
        }
    }
}

/*
*   Function: freeList
*   ------------------
*   Removes the memory allocated to the linked  lists
*   INPUT : 
*   node - Address of the linkedlist
*/
void freeList(NODE * node)
{
    
    while(node != NULL)
    {
        NODE * temp =  node;
        ELE * tempEle = node -> e;
        node = (node) -> next;
        free(temp);
        free(tempEle);
    }
}

int main()
{
    // Taking dimensions of the matrix
    int row, col;
    scanf("%d%d", &row, &col);
    // Taking number of non zero elements in both matrices
    int mat1, mat2;
    scanf("%d%d", &mat1, &mat2);

    if(!validNonZeroElements(row, col, mat1, mat2))
    {
        printf("INVALID INPUT");
        return 0;
    }
    int r, c, val;

    NODE * mat1head = NULL;
    NODE * mat2head = NULL;

    int vi1 = createMatrix(&mat1head, mat1, row, col);
    int vi2 = createMatrix(&mat2head, mat2, row, col);

    if(!vi1 || !vi2)
    {
        printf("INVALID INPUT");
        free(mat1head);
        free(mat2head);
        return 0;
    }
    
    NODE * result = addSparseMatrix(mat1head, mat2head, mat1, mat2);


    printans(result, row, col);
    freeList(mat1head);
    freeList(mat2head);
    freeList(result);
    return 0;
}