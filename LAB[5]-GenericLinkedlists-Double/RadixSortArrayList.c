#include<stdio.h>
#include<stdlib.h>

typedef struct node Node;
struct node 
{
	void * data;
	Node * next;
};

struct list
{
	Node * head;
	Node * tail;
	int size;
};
typedef struct list List;

// It creates a class of list with NULL pointed and 
// Makes the size of the list as 0
List * createList()
{
	List * newlist = malloc(sizeof(List));
	newlist -> head = NULL;
	newlist -> tail = NULL;
	newlist -> size = 0;
	return newlist;
}

Node * createNode(void * data)
{
	Node * newnode = malloc(sizeof(Node));
	newnode -> data = data;
	newnode -> next = NULL;
	return newnode;
}

int isEmpty(List * temp)
{
	return temp -> size == 0 ? 1 : 0;
}

void insertFirst(List * temp, void * data)
{
	if(temp -> tail == NULL)
	{
		Node * newnode = createNode(data);
		temp -> head = newnode;
		temp -> tail = newnode;
		temp -> size = 1;
		return;
	}

	Node * newnode = createNode(data);
	newnode -> next = temp -> head;
	temp -> head = newnode;
	(temp -> size)++;

	return;
}

void insertLast(List * temp, void * data)
{
	if(temp -> tail == NULL)
	{
		Node * newnode = createNode(data);
		temp -> head = newnode;
		temp -> tail = newnode;
		temp -> size = 1;
		return;
	}

	Node * newnode = createNode(data);
	temp -> tail -> next = newnode;
	temp -> tail = newnode;
	(temp -> size)++;
	return;
}

void * deleteFirst(List * temp)
{
	void * data = temp -> head -> data;
	Node * tempnode = temp -> head;

	if( temp -> size == 1)
	{
		temp -> head = NULL;
		temp -> tail = NULL;
		temp -> size = 0;
	}
	else
	{
		temp -> head = temp -> head -> next;
		(temp -> size)--;
	}
	free(tempnode);
	return data;
}

int countDigits(int n)
{
	int count = 0;
	while(n > 0)
	{
		count ++;
		n /= 10;
	}
	return count;
}
int getMaxDigits(int n, int arr[])
{
	int max = arr[0];
	for(int i = 1; i < n; i++)
	{
		if(max < arr[i])
		{
			max = arr[i];
		}
	}
	// Max number will anyhow will have maximum number of digits
	return countDigits(max);
}
void printList(List * temp)
{
	while(temp != NULL)
	{
		printf("%d", *(int *)temp -> head ->data);
		temp -> head = temp -> head -> next;
	}
}
void radixsort(int n, int arr[])
{
	List * lists[10];
	// Array of 10 linkedlists...
	for(int i = 0; i < 10; i++)
	{
		lists[i] = createList();
	}

	//Getting maximum number of digits of the array
	int maxdigits = getMaxDigits(n, arr);
	int position = 1;
	for(int i = 0; i < maxdigits; i++)
	{
		for(int j = 0; j < n; j++)
		{
			// Here we get in which list we need to add the upgoing element
			// In the list nth list;
			int nth = (arr[j] / position) % 10;
			int *ele = malloc(sizeof(int));
			* ele = arr[j];
			insertLast(lists[nth], ele);
			
		}
		

		// Now we need to copy back the elements into the array again.
		int index = 0;
		for(int nth = 0; nth < 10; nth++)
		{
			// If the nth list is not empty copy
			while(!isEmpty(lists[nth]))
			{
				int * ele = deleteFirst(lists[nth]);
				arr[index] = *ele;
				index ++;
				free(ele);
			}
		}
		// Copying the elements is done.
		// Need to increase the position of the numbers by multiple 10
		position *= 10;
	}
	// There ends the radixsort function
	// We need to free the dynamically allocated arrays
	for(int i = 0; i < 10; i++)
	{
		free(lists[i]);
	}
}

int main()
{
	int arrlen;
	scanf("%d", &arrlen);

	if(arrlen <= 0)
	{
		printf("INVALID INPUT");
		return 0;
	}

	int array[arrlen];
	for(int i = 0; i < arrlen; i++)
	{
		scanf("%d", &array[i]);
		if(array[i] < 0)
		{
			printf("INVALID INPUT");
			return 0;
		}
	}

	radixsort(arrlen, array);
	for(int i = 0; i < arrlen; i++)
	{
		printf("%d ", array[i]);
	}
}