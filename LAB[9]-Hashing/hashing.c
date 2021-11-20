#include<stdio.h>
#include<stdlib.h>

typedef struct hashnode HNODE;
struct hashnode
{
    long long hash_val;
    char * data;
};


typedef struct hashtable HASH;
struct hashtable
{
    int size;
    HNODE ** value;
    
};

HNODE * create_Hash_Node(long long hvalue, char * data)
{
    HNODE * newnode = malloc(sizeof(HNODE));
    newnode -> hash_val = hvalue;
    newnode -> data = data;

    return newnode;
}

HASH * createHashtable(int size)
{
    HASH * newhash = malloc(sizeof(HASH));
    newhash -> size = size;
    newhash -> value = malloc(size * sizeof(HNODE *));

    for(int i = 0; i < size; ++i)
    {
        newhash -> value[i] = create_Hash_Node(0, NULL);
    }
    return newhash;
}

void write_to_file(HASH * table, char * filename)
{
    FILE * fp = fopen(filename, "w");

    int h_size = table -> size;
    HNODE * tempnode;

    for(int i = 0; i < h_size; ++i)
    {
        tempnode = table -> value[i];
        if(tempnode -> hash_val != 0){
            printf("%s\n", tempnode -> data);
            fprintf(fp, "%s\n", tempnode -> data);
        }
    }
    fclose(fp);
    return;
}

/**
 * @brief computing hash value to a string.
 * @brief Hash value = char * p^0 + char * p ^1 + char * p ^ 2 +....
 * 
 * @param data 
 *          data is the string passed by the calling fucntion
 * @param length 
 *          length is the size of the string
 * @return long long value <Hash value>
 */
long long compute_hash(char * data)
{
    const int p = 31;
    const int  m = 1e9+9;
    unsigned long long hash_value = 0;
    long long p_pow = 1;

    char ch = data[0];
    int i;
    for(i = 1; ch != '\0'; ++i)
    {
        ch = data[i];
        hash_value = (hash_value  + (ch - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    //printf("%lld\n", hash_value);
    return hash_value;
}

/**
 * @brief Returns 1 if the hash values and strings are same else 0
 * 
 * @param hv1 
 * @param s1 
 * @param hv2 
 * @param s2 
 * @return int (1 -> same value, 0 -> different)
 */
int compare_hash_value(long long hv1, char * s1, long long hv2, char * s2)
{
    return hv1 == hv2 && !(s1 - s2) ? 1 : 0;

}

/**
 * @brief inserting a string into the hash...
 * 
 * @param table 
 *          Hash table storing the strings with their hash value
 * @param h_value 
 * @param data 
 * @return int 
 */
int insert_into_hash(HASH ** table, long long h_value, char * data)
{
    HASH * temp = *table;
    int h_size = temp -> size;
    int modvalue = h_value % h_size;
    //printf("\nModevalue - %d", modvalue);
    HNODE * tempnode = temp -> value[modvalue];
    //printf("\nModevalue - %d", modvalue);

    if(tempnode -> hash_val == 0)
    {
        tempnode -> hash_val = h_value;
        tempnode -> data     = data;
        //printf("%s\n", data);
        return 1;
    }
    int index = modvalue;

    while(tempnode -> hash_val != 0)
    {
        if(compare_hash_value(tempnode -> hash_val, tempnode -> data, h_value, data))
        {
            return 0;
        }
        index = (index + 1) % h_size;
        tempnode = temp -> value[index];
    }

    tempnode -> hash_val = h_value;
    tempnode -> data     = data;
    return 1;
}

void printhash(HASH * temp)
{
    for(int i = 0; i < temp -> size; i++)
    {
        HNODE * node = temp -> value[i];
        //printf("\n%lld - %s\n", node ->hash_val, node ->data);
    }
}
void remove_duplicates(char * filename, char * outputfile)
{
    FILE * fp;
    fp = fopen(filename, "r");
    if(!fp)
    {
        printf("ERROR IN OPENING FILE %s", filename);
        exit(1);
    }

    size_t length = 0;
    char * line = malloc(100);
    long long hash_value = 0;
    int size = 100;
    HASH * htable = createHashtable(size);
    
    //while(getline(&line, &length, fp) != -1)
    while(fscanf(fp, "%[^\n] ", line) != EOF)
    {
        
        printf("\n%s\n",line);
        long long hash_value = compute_hash(line);
        int x = insert_into_hash(&htable, hash_value, line);
    }

    printhash(htable);

    write_to_file(htable, outputfile);
}

int main(int argc, char *argv[])
{
    remove_duplicates(argv[1], argv[2]);
    return 0;
}
