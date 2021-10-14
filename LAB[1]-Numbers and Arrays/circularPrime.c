#include<stdio.h>
#include<math.h>

int isPrime(int n)
{
    if(n == 1) return 0;
    if(n == 2 || n == 3) return 1;
    if(n % 2 == 0 || n % 3 == 0) return 0;
    
    for(int i = 5; i * i <= n; i++)
    {
        if(n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}


int main()
{
    int n;
    scanf("%d", &n);
    if(n <= 0)
    {
        printf("-1");
        return 0;
    }
    
    int nlen = (int)log10(n) + 1;
    int powTen = pow(10, nlen-1);
    
    while(nlen--)
    {
        int check = isPrime(n);
        if(!check)
        {
            printf("0");
            return 0;
        }
        int temp = n / powTen;
        
        n = (n % powTen) * 10 + temp;
    }
    printf("1");
    
    return 0;
}