#include<stdio.h>
#include<stdlib.h>

struct indices
{
    int rInd;
    int cInd;
};

int checkMinInRow(int i, int j, int row, int col, int** mat)
{
    int min = mat[i][j];
    
    for(int k = 0; k < col; k++)
    {
        if(mat[i][k] < min) return 0;
    }
    return 1;
}

struct indices findIndices(int row, int col, int** mat)
{
    struct indices ans;
    
    for(int j = 0; j < col; j++)
    {
        int max = mat[0][j];
        ans.rInd = 0;
        ans.cInd = j;
        
        for(int i = 0; i < row; i++)
        {
            if(mat[i][j] >= max)
            {
                max = mat[i][j];
                ans.rInd = i;
                ans.cInd = j;
            }
        }
        
        if(checkMinInRow(ans.rInd, ans.cInd, row, col, mat)) return ans;
    }
    
    ans.rInd = -2;
    ans.cInd = -2;
    
    return ans;
}


int ** create2Darray(int row, int col)
{
    int ** b =  (int **)malloc(row * sizeof(int *));
    for(int i = 0; i < row; i++)
    {
        b[i] = (int *) malloc(col * sizeof(int));
    }
    
    return b;
}

int main()
{
    int row, col;
    
    scanf("%d%d", &row, &col);
    
    if(row <= 0 || col <= 0)
    {
        printf("-2");
        return 0;
    }
    
    int **mat = create2Darray(row, col);
    
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            scanf("%d", &mat[i][j]);
            
    struct indices index = findIndices(row, col, mat);
    
    if(index.rInd == -2)
        printf("-1");
    else
        printf("%d %d", index.rInd, index.cInd);
        
    return 0;
        
            
    
}
