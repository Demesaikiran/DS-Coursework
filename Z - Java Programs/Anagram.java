import java.util.*;
import java.io.*;

public class Anagram {
    
    public String isAnagram(String input1, String input2)
    {
        String s1 = input1.replaceAll("\\s", "");
        String s2 = input2.replaceAll("\\s", "");

        String status = "yes";
        if(s1.length() != s2.length())
            status = "no";

        else{
            char[] Arrays1 = s1.toLowerCase().toCharArray();
            char[] Arrays2 = s2.toLowerCase().toCharArray();

            Arrays.sort(Arrays1);
            Arrays.sort(Arrays2);

            if(Arrays.equals(Arrays1, Arrays2))
            {
                status = "yes";
            }
            else{
                status = "no";
            }
        }

        return status;
    }
}
