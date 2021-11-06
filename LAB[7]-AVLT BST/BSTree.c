#include<stdio.h>
#include<stdlib.h>

typedef struct node Node;
struct node
{
    int data;
    Node * left;
    Node * right;
};

typedef struct Bst BST;
struct Bst
{
    Node * root;
    int height;
};

Node * createNode(int data)
{
    Node * newnode = malloc(sizeof(Node));
    newnode -> data = data;
    newnode -> right = newnode -> left = NULL;
    return newnode;
}

BST * createBSTRoot(int data)
{
    BST * newRoot = malloc(sizeof(BST));
    newRoot -> root = createNode(data);
    newRoot -> height = 0;
    return newRoot;
}

int isElementExists(Node * temp, int e)
{
    if(temp == NULL) return 0;
    if(temp ->data == e) return 1;
    else
        if(e < temp -> data) 
            return isElementExists(temp -> left, e);
        else
            return isElementExists(temp -> right, e);
}

Node * insert(Node * root, int data)
{
    if(root == NULL)
        return createNode(data);

    if(data < root -> data)
        root -> left = insert(root -> left, data);
    else
        root -> right = insert(root -> right, data);
    return root;
}

void deleteFromBST(BST ** bst, int e)
{
    if(!isElementExists((*bst) -> root, e))
        return;

    Node * parent = NULL;
    Node * current = (*bst) -> root;

    while(current != NULL && current -> data != e)
    {
        parent = current;
        if(e < current -> data) current = current -> left;
        else current = current -> right;
    }

    if(current == NULL) return;

    // If it isa leaf node...
    if(current -> left == NULL && current -> right == NULL)
    {
        if(current != (*bst) -> root)
        {
            if(parent -> left == current)
                parent -> left = NULL;
            else parent -> right = NULL;
        }
        else
        {
            (*bst) -> root = NULL;
        }
        free(current);
    }

    // Has both right and left childs
    else if(current -> left && current -> right)
    {
        Node * temp = current;
        temp = temp -> right;

        while(temp -> left != NULL) temp = temp -> left;

        int value = temp -> data;
        deleteFromBST(&(*bst), value);
        current -> data = value;
    }

    // One child is NULL - with degree 2
    else
    {
        Node * temp = (current -> left) ? current -> left : current -> right;

        if(current != (*bst) -> root)
        {
            if(current == parent -> left)
            {
                parent -> left = temp;
            }
            else parent -> right = temp;
        }
        else (*bst) -> root = temp;
        free(current);
        
    }
}
int height(Node * temp)
{
    if(temp == NULL)
        return 0;

    int leftHeight = height(temp -> left) + 1;
    int rightHeight = height(temp -> right) + 1;

    return leftHeight > rightHeight ? leftHeight : rightHeight;
    
}
void inorderTraversal(Node * temp)
{
    if(temp == NULL) return;
    inorderTraversal(temp -> left);
    printf("%d ", temp -> data);
    inorderTraversal(temp -> right);
}
int main()
{
    BST * tree = malloc(sizeof(tree));
    tree -> root = NULL;
    
    int choice;
    scanf("%d", &choice);

    while(choice != -1)
    {
        switch (choice)
        {
        case 1:
            {
                int ele;
                scanf("%d", &ele);
                tree -> root = insert(tree -> root, ele);
                break;
            }
        case 2:
            {
                int ele;
                scanf("%d", &ele);
                deleteFromBST(&tree, ele);
                break;
            }        
        case 3:
            {
                int ele;
                scanf("%d", &ele);
                if(tree != NULL && isElementExists(tree -> root, ele))
                {
                    printf("1 ");
                    break;
                }
                printf("0 ");
                break;
            }
        case 4:
            {
                printf("%d ", height(tree -> root) - 1);
                break;
            }
        case 5:
            {
                inorderTraversal(tree -> root);
                break;
            }
        default:
            break;
        }
        scanf("%d", &choice);
    }

}