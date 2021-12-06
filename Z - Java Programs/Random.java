import java.util.*;
import java.io.*;

class Random
{
    private int getMinimum(int arr[], int n)
    {
        int min = arr[0];
        for(int i = 1; i < n; i++)
            if(arr[i] < min)
                min = arr[i];
        return min;
    }

    private int getMaximum(int arr[], int n)
    {
        int max = arr[0];
        for(int i = 1; i<n; i++)
        {
            if(arr[i] > max)
                max = arr[i];
        }
        return max;
    }

    public int checkConsecutive(int arr[], int n)
    {

        if(n < 1)
            return 0;
        int min = arr[0];
        for(int i = 1; i < n; i++)
            if(arr[i] < min)
                min = arr[i];

        int max = arr[0];
        for(int i = 1; i<n; i++)
        {
            if(arr[i] > max)
                max = arr[i];
        }
        


        boolean[] visited = new boolean[max - min + 1];

        for(int i = 0; i < max - min +1; i++)
        {
            visited[arr[i] - min] = true;
        }

        for(int i = 0; i< max - min + 1; i++)
        {
            if(visited[arr[i] - min] == false)
                return 0; 
        }
        return 1;
        
    }

    public static void main(String[] args)
    {
    }
}
