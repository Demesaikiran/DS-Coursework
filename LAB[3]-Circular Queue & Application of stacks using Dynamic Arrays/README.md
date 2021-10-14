# Circular Queue and Apps of Stack (Dynamic arrays)
## Circular Queue:

Write an efficient and scallable implementation of dynamically growing Circular Queue using Arrays.

The Circular queue should have the following features:
1. The queue is to hold integer elements.
2. Intial maximum size of the queue to be 4 elements.
3. Everytime the queue is full the queue size to be doubled using dynamic memory allocation.
4. It should have the following functions
    - createQueue() - Dynamically create queue
    -enqueue(Q, e) - inserts element e into the queue
    -dequeue(Q) - Removes and retruns element from the queue using FIFO machanism
    -getFront(Q) - returns the element at the front, element will not be removed from the queue
    
5. If dequeue(Q) or getFront(Q) is called when queue is empty, then print the message "QE"
6. If enqueue(Q, e) is called when queue is full for the current limit, print the message "QF QSD" and then double the queue size and insert the element e into the queue.

Once you implement the Circular Queue function, write a menu driven main() test function to test functions of the queue.
The test function acts based on the user inputs. Inputs would be as follows:
1 x - enqueue intreger x onto the queue
2   - dequeue the queue and print the element removed from the queue
3   - print the front element of the queue
-1  - stop

Sample Input-1: 1 10 1 200 1 40 1 80 1 17 2 2 2 2 2 2 1 20 1 30 1 2 1 -12 1 -200 1 30 1 50 1 70 1 80 -1

Output: QF QSD 10 200 40 80 17 QE QF QSD



Sample Input-2: 2 3 1 11 1 -1 1 1 1 111 1 1111 3 2 3 2 3 2 3 2 3 2 3 2 -1

Output: QE QE QF QSD 11 11 -1 -1 1 1 111 111 1111 1111 QE QE

<br />

## PostFix Evaluation:

Implement an efficient and scalable stack using arrays.
The stack should have the following features:
1. Initial size of the stack is 4 element
2. Stack in meant to hold integer values
3. Stack has the following functions:
    -createStack() - creates a stack dynamically
    -push(S, e) - push element e onto the stack
    -pop(S) - delete element from the stack using LIFO mechanism
    -getTop(S) - returns the top element of the stack
4. If push(S, e) is called when stack is full, stack size to be doubled and memory to be reallocated.
5. If there is division by zero display "DIVBYZERO"

Now write a test function main() which evaluates a post-fix expression. Only binary operators +, -, * and / (integer division) to be used in the post-fix expression.

Sample Input-1: 10 20 30 + +

Output: 60

Sample Input-2: 10 20 30 / -

Output: 10

<br />

## Replacing Recursion With Stack:

The function f(a, b) is defined for positive integers a, b as follows:
f(a, b) = 1 if b ≤ a or b ≥ 8; otherwise f(a, b) = 1 + f(a, g(b)) + f(b, a + 4),
where g(b) = 3b + 1 if b is odd and g(b) = b/2 if b is even.

Write a C program to evaluate f(a, b) without using recursion.
Any recursive problem can be solved using a stack in an iterative manner.

You need to implement stack using arrays.
The stack should have the following features:
1. Initial size of the stack is 100 element
2. Stack has the following functions:
    -createStack() - creates a stack dynamically
    -push(S, e) - push element e onto the stack
    -pop(S) - delete element from the stack using LIFO mechanism
    -getTop(S) - returns the top element of the stack
    -isEmpty(S) - return 1 if stack is empty, 0 otherwise

You understand the problem and decide what information you need to store on the stack.

If user enters 0 or negative numbers for a or b print -1 to indicate its invalid input.

Sample Input/Output:

Input-1: 5 6

Output: 3

Input-2: 1 6

Output: 9

Input-3: 0 6

Output: -1