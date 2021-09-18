#include<stdio.h>
#include<stdlib.h>

#define ROW 10
#define COL 5

void func1(int[ROW][COL]);
void func2(int, int[][COL]);
void func3(int row, int col, int a[row][col]);
void func4(int row, int col, int **a);
int ** create2Darray(int row, int col);
void free2DArray(int row, int col, int **a);
int main()
{
    int a[ROW][COL], i, j;

    for(i = 0; i < ROW; i++)
    {
	for(j = 0; j < COL; j++)
	{
	    a[i][j] = i;
	}
    }

    func1(a);
    printf("\n\n");
    func2(ROW, a);
    printf("\n\n");

    int r, c;
    printf("Enter dimentionas of the array");
    scanf("%d%d", &r, &c);

    int arr[r][c];
    for(i = 0; i < r; i++)
    {
	for(j = 0; j < c; j++)
	{
	    arr[i][j] = i;
	}
    }
    func3(r, c, arr);
    printf("\n\n");
    
    int **b = create2Darray(r, c);
    for(i = 0; i < r; i++)
    {
	for(j = 0; j < c; j++)
	{
	    b[i][j] = i;
	}
    }
    func4(r, c, b);
    free2DArray(r, c, b);
}

//function to create a 2D array dynamically
int ** create2Darray(int row, int col)
{
    int ** b = malloc(row * sizeof(int*));
    for(int i = 0; i < row; i++)
    {
        b[i] = malloc(col * sizeof(int));
    }
    return b;
}

//free 2D array which is created dynamically
void free2DArray(int row, int col, int **a)
{
    for(int i = 0; i < row; i++)
    {
	free(a[i]);
    }
    free(a);
}


//Passign 2D array method-1: fixed row and column sizes 
void func1(int a[ROW][COL])
{
    int i, j;
    for(i = 0; i < ROW; i++)
    {
	for(j = 0; j < COL; j++)
	{
	    printf("%d ", a[i][j]);
	}
	printf("\n");
    }

}

//Passign 2D array method-2: variable row size and fixed column size 
void func2(int row, int a[][COL])
{
    int i, j;
    for(i = 0; i < row; i++)
    {
	for(j = 0; j < COL; j++)
	{
	    printf("%d ", a[i][j]);
	}
	printf("\n");
    }

}

//Passign 2D array method-3: variable row and column size. This is supoported from C99 standard
void func3(int row, int col, int a[row][col])
{
    int i, j;
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}


//Passign 2D array method-4: passing dynamically created array 2D array
void func4(int row, int col, int **a)
{
    for(int i = 0; i < row; i++)
    {
	for(int j = 0; j < col; j++)
	{
	    printf("%d ", a[i][j]);
	}
	printf("\n");
    }
}
