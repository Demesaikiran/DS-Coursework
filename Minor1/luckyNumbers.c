#include<stdio.h>
#include<stdlib.h>

/*
*   Function: LuckyNumbers
*   ----------------------
*   It generates the lucky numbers as mentioned
*   
*   INPUT:
*   *arr = array reference
*   size = size fo the array.
*
*   OUTPUT:
*   Returns the size of the array after operations
*/
int luckyNumbers(int *arr, int size)
{
    int deli = 1;

    while(deli < size)
    {
        for(int i = deli; i < size; i += deli)
        {
            for(int j = i; j < size - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            size--;
        }
        deli ++;
    }

    return size;
}

/*
*   Function: printLuckyNumbers
*   ---------------------------
*   It prints the elements in the given array
*
*   INPUT:
*   arr[] = array copy
*   n     = size of the array
*/
void printArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

int main()
{
    int arrlen;
    scanf("%d", &arrlen);

    if(arrlen < 0)
    {
        printf("INVALID INPUT");
        return 0;
    }

    int arr[arrlen];

    for(int i = 0; i < arrlen; i++)
    {
        arr[i] = i + 1;
    }

    arrlen = luckyNumbers(arr, arrlen);
    printArray(arr, arrlen);
    return 0;

}