#include "hashmap.h"
#define MULTIPLIER 5381



unsigned int hash(char *str)
{
    unsigned int h;
    unsigned char *p;
    h = 0;
    for (p = (unsigned char*)str; *p != '\0'; p++)
      h = MULTIPLIER * h + *p;
    return h; 
}


void push_int(bucket_t *bucket, char* key, unsigned int value) // bucket init at first the first current must have value but key is always null on the first init so no problems
{
    Linked_hash* current = bucket->buckets[hash(key)%bucket->bucket_size];
    
    if(current == NULL)
    {
        current = calloc(1,sizeof(Linked_hash));
        bucket->buckets[hash(key)%bucket->bucket_size] = current;
    }
    

    while(current != NULL)
    {
        
        if (current->key == NULL)
        {
            current->key = strdup(key);
            current->value = value;
            
            break;
            
        }
        else if(strcmp(key,current->key) == 0)
        {
            
            current->value = value;
            break;
        }
        else 
        {
            if(current->next != NULL)
            {
                current = current->next;
            }
            else
            {
                current->next = calloc(1,sizeof(Linked_hash));
                current = current-> next;
            }
        }
    }
}

unsigned int* get_key(bucket_t* bucket,char* key)
{
    Linked_hash* current = bucket->buckets[hash(key)%bucket->bucket_size];
    
    
    while(current != NULL)
    {
        
        if(strcmp(key,current->key) == 0)
        {
            
            return &(current->value);
        }
        else 
        {
            
            current = current->next;
        }
    }
    return NULL;
}

bucket_t init_hashmap(unsigned int bucket_size)
{
    return (bucket_t){calloc(bucket_size,sizeof(Linked_hash*)),bucket_size};
}
