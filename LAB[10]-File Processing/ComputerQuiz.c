#include<stdio.h>
#include<stdlib.h>

// Defined MAXSIZE for the line based text storage
// Defined AS_SIZE for assertion statement text storage (TRUE / FALSE) 
// which requires only 6 at the max
#define MAXSIZE 100
#define AS_SIZE 10

/**
 * @brief Buffer Map structture
 *      It stores the Key value pairs in terms of question and userAns
 */
struct bufferMap
{
    char * question;
    char * userAnswer;
};
typedef struct bufferMap Map;

/**
 * ==========================================================================================
 * 
 *          STRING UTILITY FUNCTIONS START
 * 
 */

/**
 * @brief Converts a character to lower character
 * 
 * @param ch [ Which is the input character to the function]
 * @return returns the lower character
 */
char toLower(const char ch)
{
    if(ch >= 'A' && ch <= 'Z')
        return ('a' + (ch - 'A'));
    return ch;
}

/**
 * @brief It checks whether two strings are equal or not by comparing
 * 
 * @param test [string to which we are checking]
 * @param req  [ String that we are comparing with ]
 * @return int [ Returns 1 if both the strings are equal else 0]
 */
int stringCompare(const char * test, const char * req)
{
    char ch = toLower(test[0]);
    int index = 0;

    while(ch != '\0')
    {
        //printf("%c", ch);
        if(ch == toLower(req[index++])){
            ch = toLower(test[index]);
            continue;
        }

        return 0;
    }
    return 1;
}

/**
 * @brief returns the object reference of string
 * 
 * @param old [ Copying the existing string - old ]
 * @return char* [ Returns string object ]
 */
char * stringCopy(char * old)
{
    int i = 0;
    char * s = malloc(sizeof(char) * MAXSIZE);

    for(i = 0; old[i] != '\0'; ++i)
        s[i] = old[i];
    
    s[i] = '\0';
    return (char *) s;
}

/**
 * @brief Validates the input string with the comparator
 * 
 * @param input [ String ]
 * @param comparator [ String ]
 * @return int [ Returns 1 if it matches with the comparator else 0 ]
 */
int inputValidation(char * input, char * comparator)
{
    return stringCompare( input, comparator ) ? 1 : 0;
}
/**
 * ==========================================================================================
 */

/**
 * @brief Create a Buffer Storage object
 * 
 * @param size [ Buffer of size - size ]
 * @return Map* [ Returns the Buffer Reference ]
 */
Map * createBufferStorage(int size)
{
    Map * newBuffer = malloc(size * sizeof(Map));
    while(size--)
    {
        Map * temp  =  newBuffer;
        temp        =  malloc(sizeof(Map));
    }
    return newBuffer;

}

/**
 * @brief Frees the heap space allocated to the Buffer array
 * 
 * @param garbage 
 * @param size of the buffer array
 */
void freeBuffer(Map * garbage, int size)
{
    Map * gb = garbage;

    while(size--)
    {
        free(gb -> question);
        free(gb -> userAnswer);
        gb += sizeof(Map);
    }

}

/**
 * @brief Prints the Report Result
 * 
 * @param ca [ Correct answers count ]
 * @param buffer [ Buffer ]
 * @param n [ Actual number of questions ]
 */
void printResult(int ca, Map ** buffer, int n)
{

    printf("\n===================================\nFINAL REPORT:\n===================================");
                
    printf("\n\nTotal number of correct answers: %d", ca);

    if(n == ca) 
    {
        printf("\n\n");
        return;
    }

    Map * temp = *buffer;

    printf("\n\nWrong answers Report:\n===================================\n");

    for(int i = 0; i < n - ca; i ++)
    {
        printf("%s", temp -> question);
        printf("\nYour answer: \033[31m %s", temp -> userAnswer);

        if(temp -> userAnswer[0] - 'F' == 0 || temp -> userAnswer[0] - 'f' == 0)
            printf("\nActual answer: \033[32m TRUE\n\n");
        else
            printf("\nActual answer: \033[32m FALSE\n\n");

        temp = temp + sizeof(Map);
    }
}


/**
 * @brief Main application function of quiz utility
 * 
 * @param filename 
 * @return int [ Returns 1 if the quiz goes well else 0 if any inturrupt occurs in between
 *              Interms of wrong filename or any other]
 */
int startQuiz(char * filename)
{
    // File Processing <Opening the file and setting file pointer>
    FILE *fp = fopen(filename, "r");
    if(!fp)
    {
        printf("ERROR IN OPENING FILE %s", filename);
        exit(1);
    }
    
    // n_ques represents the number of questions present in file.
    // correctAns count is to check how many questions got correctly answered.
    int n_ques;
    int correctAns     = 0;

    Map * BufferArray  =  createBufferStorage(n_ques + 1);
    Map * bufferhead   =  BufferArray;

    /**
     * @brief If there is any text in the file or 
     *        In file if there is no required data
     *        it will return 0 for wrong 
     */
    
    if(fscanf(fp, "%d\n", &(n_ques)) == 1)
    {
        char * line  =  malloc(sizeof(char) * (MAXSIZE+1));
        /**
         * @brief System("clear") function will not work for WINDOWS operating system.
         * 
         */
        system("clear");
        // qno is to store the current question number for interactive purpose.
        int qno     =  1;
        size_t len  =  0;
        ssize_t read;
        
        while(fscanf(fp, "%[^\n] ", line) != EOF)
        {
            char * userAns       =   malloc(AS_SIZE);
            char * actualAnswer  =  malloc(AS_SIZE + 1);

            printf("\n[Question-%d] %s\n\n[True / False]: ",qno++, line);
            scanf("%s", userAns);

            while( !(inputValidation( userAns, "True" ) || inputValidation( userAns, "False" )))
            {
                printf("\n\nWrongly typed...\n\nEnter [True / False]: ");
                scanf("%s", userAns);
            }

            if(fscanf(fp, "%[^\n] ", actualAnswer) != EOF)
            {
                // Checking whether the given answer matches with the actual answer.
                int check = stringCompare(userAns, actualAnswer);

                if(!check)
                {
                    bufferhead -> question    =  stringCopy(line);
                    bufferhead -> userAnswer  =  userAns;
                    bufferhead                +=  sizeof(Map);
                    continue;
                }

                correctAns++;
            }
        }
    }
    else
        return 0;

    printResult(correctAns, &BufferArray, n_ques);
    freeBuffer(BufferArray, n_ques);
    return 1;
    
}

int main(int argc, char * argv[])
{
    if(! startQuiz(argv[1]))
    {
        printf("Entered wrong expression...");
    }
    return 0;
}
