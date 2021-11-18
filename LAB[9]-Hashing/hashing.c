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
    HNODE * tempnode = table -> value[0];

    for(int i = 0; i < h_size; ++i)
    {
        if(tempnode -> hash_val != 0)
            fprintf(fp, "%s\n", tempnode -> data);

        tempnode = table -> value[i];
    }
    return;
}

long long compute_hash(char * data, int length)
{
    int p = 31;
    int m = 100;
    unsigned long long hash_value = 0;
    long long p_pow = 1;

    char ch;

    for(int i = 0; i < length; ++i)
    {
        ch = data[i];
        hash_value = (hash_value + (ch - 'a' + 1) * p_pow) % m;
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
 * @brief 
 * 
 * @param table 
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

    int index = (modvalue + 1) % h_size;
    HNODE * tempnode = temp -> value[index];
    while(tempnode -> hash_val != 0)
    {
        if(compare_hash_value(tempnode -> hash_val, tempnode -> data, h_value, data))
        {
            return 0;
        }
        index = (index + 1) % h_size;
        //tempnode = temp -> value[index];
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
        printf("\n%lld - %s\n", node ->hash_val, node ->data);
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
    ssize_t read;
    char * line = NULL;
    long long hash_value = 0;
    int size = 100;
    HASH * htable = createHashtable(size);
    
    while((read = getline(&line, &length, fp)) != -1)
    {
        
        long long hash_value = compute_hash(line, (int)length);
        printf("\n%lld\n",hash_value);
        int x = insert_into_hash(&htable, hash_value, line);
    }

    printhash(htable);

    //write_to_file(htable, outputfile);
}

int main(int argc, char *argv[])
{
    remove_duplicates(argv[1], argv[2]);
    return 0;
}
