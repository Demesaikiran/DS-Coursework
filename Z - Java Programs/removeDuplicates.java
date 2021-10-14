import java.util.*;
import java.io.*;

public class removeDuplicates {
    
    public String removeDuplicate(String input1)
    {
        int len = input1.length();

        String result = "";

        for(int i = 0; i< len; i++)
        {
            int j;
            for(j = 0; j < i; j++)
            {
                if(input1.charAt(j) == input1.charAt(i))
                    break;
            }

            if(j == i)
            {
                result += input1.charAt(i);
            }
        }
        return result;
    }
}
