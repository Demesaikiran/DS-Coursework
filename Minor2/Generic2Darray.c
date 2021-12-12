#include<stdio.h>
#include<stdlib.h>


void * createMatrix(int row, int col)
{
    void ** newmatrix = malloc(row * sizeof(void *));
    for(int i = 0; i < col; i++)
    {
        newmatrix[i] = malloc(col * sizeof(void));
    }
    return newmatrix;
}

int main()
{
    char ** cmatrix = createMatrix(3, 3);
    int ** imatrix  = createMatrix(3, 3);
    cmatrix[1][1] = 'c';
    imatrix[0][0] = 1;

    printf("%c %d", cmatrix[1][1], imatrix[0][0]);
}