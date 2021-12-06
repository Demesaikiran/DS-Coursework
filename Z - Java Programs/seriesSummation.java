import java.util.Scanner;

class seriesSummation
{
    
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            int n = sc.nextInt();

            int fact[] = new int[n+3];

            fact[0] = 1;
            for(int i = 1; i <= n; i++)
            {
                fact[i] = i * fact[i-1];
            }

            int X = sc.nextInt();
            int summation = 0;

            for(int j = 1,i = X; j <= n ; i = i * X, j++)
            {
                if(j % 2 == 0)
                {
                    summation += i / fact[j];
                }
                else
                {
                    summation -= i / fact[j];
                }
            }

            System.out.println(summation);
        }
        
    }
}