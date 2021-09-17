#include<stdio.h>

int isPrime(int N)
{
    if(N == 1) return 0;
    if(N == 2) return 1;
    if(N % 2 == 0 || N % 3 == 0) return 0;
    
    for(int i = 5; i * i <= N; i++)
    {
        if(N % i == 0 || N % (i + 2) == 0) return 0;
    }
    
    return 1;
}
int main()
{
    int n;
    printf("Enter the number n: ");
    scanf("%d", &n);
    
    if(n <= 0)
    {
        printf("-1");
        return 0;
    }
    
    else
    {
        if(isPrime(n))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    return 0;
}