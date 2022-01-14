#include<iostream>
using namespace std;

/**
 * @brief Creating a class for a node of linked list
 *      With "data" variable for a node and the next pointer
 *      Which points to the next node.
 */

class Node
{
    public:
        int data;
        Node * next;

        Node()
        {
            data = 0;
            next = NULL;
        }

        // Parametrised Node constructor if we call a node with 
        // the data provided it creates of that type node.
        Node(int data)
        {
            this -> data = data;
            this -> next = NULL;
        }
};

/**
 * @brief Creating the linked list class which has various functions like
 * 
 *      1] Inserting node in the front of linked list
 *      2] Removing an element from the linked list
 *      3] Finding the index of an element / data.
 *           if present then the node is going to kept front of linkedlist
 *           else the index sent to the caller funciton as "-1".
 * 
 */
class LinkedList
{
    Node * head;
    Node * tail;

    public:

        LinkedList()
        {
            head = NULL;
        }

        int isEmpty();
        void insertNode(int);   // Inserting the node data provided
        int removeNode();    // Removing the node given as input
        int findNode(int);      // Returns the index of the node found
        void printList();
};

/**
 * @brief Checks whether the linkedlist is empty or not
 * 
 * @return returns "1" if the linked list is empty else "0"
 */
int LinkedList :: isEmpty()
{
    return head == NULL ? 1 : 0;
}

/**
 * @brief Inserts node in the front
 * 
 * @param data [ Data of that node value that will be inserted front of linkedlist]
 */
void LinkedList :: insertNode(int data)
{
    Node * newnode = new Node(data);

    if(head == NULL)
    {
        head = newnode;
        return;
    }

    newnode -> next = head;
    head = newnode;
    return;
}

/**
 * @brief Removes node from the front of linkedlist
 * 
 * @return returns the deleted element.
 */
int LinkedList :: removeNode()
{
    Node * deleted_node = head;
    head = head -> next;
    int deleted_data = deleted_node -> data;
    delete deleted_node;
    return deleted_data;
}

/**
 * @brief Finds node from the linked list we have
 * 
 * @param data [ The data to be serached in the linkedlist]
 * @return int [ Returns the index of the element if present, else returns -1]
 */
int LinkedList :: findNode(int data)
{
    Node * traverse = head;
    Node * previous = head;
    if(isEmpty())
    {
        return -1;
    }
    int count = 0;

    while(traverse -> next != NULL)
    {
        if(traverse -> data == data)
            break;
        previous = traverse;
        traverse = traverse -> next;
        count++;
    }
    if(traverse -> data == data)
    {
        if(traverse != head)
        {
            previous -> next = traverse -> next;
            traverse -> next = head;
            head = traverse;
        }
        // delete traverse;
        // delete previous;
        return count;
    }
    return -1;
}

/**
 * @brief prints the entire list
 */
void LinkedList :: printList()
{
    Node * temp = head;
    while(temp != NULL)
    {
        cout << temp -> data;
        temp = temp -> next;
    }
    return;
}


int main()
{
    LinkedList list;
    // Menu driven program...

    int choice, data, index, nodeData;
    cin >> choice;

    while(choice != -1)
    {
        
        switch (choice)
        {
            case 1:
                cin >> data;
                list.insertNode(data);
                break;

            case 2:
                if(list.isEmpty())
                    cout << "LE ";
                else
                {
                    nodeData = list.removeNode();
                    cout << nodeData << " ";
                }
                break;

            case 3:
                cin >> data;
                index = list.findNode(data);
                index == -1 ? cout << "ENF " : cout << index << " ";
                break;
            case 4:
                list.printList();
                break;

            default:
                cout << "INVALID INPUT";
                break;
        }

        cin >> choice;
    }

    return 0;
}