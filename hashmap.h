
#include "stdlib.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>


typedef struct Linked_hash
{
    char* key;
    unsigned int value;
    struct Linked_hash* next;
} Linked_hash;

typedef struct bucket_t
{
    Linked_hash** buckets;
    unsigned int bucket_size;
} bucket_t;


bucket_t init_hashmap(unsigned int bucket_size);
unsigned int hash(char *str);
void push_int(bucket_t *bucket, char* key, unsigned int value);
unsigned int* get_key(bucket_t* bucket,char* key);