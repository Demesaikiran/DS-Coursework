#include<stdio.h>
#include<stdlib.h>

/**
 * @brief Hashnode in the hashtable.
 * 
 */
typedef struct hashnode HNODE;
struct hashnode
{
    long long hash_val;
    char * data;
};

/**
 * @brief Hashtable with the array of hashnodes.
 * 
 */
typedef struct hashtable HASH;
struct hashtable
{
    int size;
    HNODE ** value;
    
};

/**
 * @brief Create a Hash Node object
 * 
 * @param hvalue 
 *          Hash value
 * @param data 
 *          Data is the text which we store in the file
 * @return HNODE* 
 *          Returning the Hash node object reference.
 */
HNODE * create_Hash_Node(long long hvalue, char * data)
{
    HNODE * newnode = malloc(sizeof(HNODE));
    newnode -> hash_val = hvalue;
    newnode -> data = data;

    return newnode;
}

/**
 * @brief Create a Hashtable object
 * 
 * @param size 
 *          Hash table size
 * @return HASH* 
 *          Returns the hashtable object reference.
 */
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

/**
 * @brief Removing the hashtable entries from the heap memory
 * 
 * @param garbage 
 *          Hahstable reference
 */
void freeHash(HASH * garbage)
{
    for(int i = 0; i < garbage -> size; i++)
    {
        HNODE * node = garbage -> value[i];
        free(node);
        //printf("\n%lld - %s\n", node ->hash_val, node ->data);
    }
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
    HNODE * tempnode = temp -> value[modvalue];

    if(tempnode -> hash_val == 0)
    {
        tempnode -> hash_val = h_value;
        tempnode -> data     = data;
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

/**
 * @brief It removes the duplicates in the file and writes if it is unique or removes if it is duplicate
 * 
 * @param filename 
 *          It is the file where duplicates are present
 * @param outputfile 
 *          Writing output file where only unique text is present
 */
void remove_duplicates(char * filename, char * outputfile)
{
    FILE * fp, *fout;
    fp = fopen(filename, "r");
    fout = fopen(outputfile, "w+");
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
    
    while(getline(&line, &length, fp) != -1)
    //while(fscanf(fp, "%[^\n] ", line) != EOF)
    {
		
        long long hash_value = compute_hash(line);
        int x = insert_into_hash(&htable, hash_value, line);
        if(x == 0) continue;
        fprintf(fout, "%s", line);
    }
    freeHash(htable);

}

int main(int argc, char *argv[])
{
    remove_duplicates(argv[1], argv[2]);
    return 0;
}