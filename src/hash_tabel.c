#include <stdlib.h>
#include "hash_table.h"
#include <math.h>

unsigned int hashFunction(const char *key)
{
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++; // Une simple fonction de hachage
    }
    return hash % TABLE_SIZE;
}

void insert(HashTable *table, const char *key, FunctionPointer function)
{
    unsigned int index = hashFunction(key);

    HashEntry *entry = (HashEntry *)malloc(sizeof(HashEntry));
    entry->key = strdup(key);
    entry->function = function;
    
    table->entries[index] = entry;
}

FunctionPointer getFunction(HashTable *table, const char *key)
{
    unsigned int index = hashFunction(key);
    if (table->entries[index] && strcmp(table->entries[index]->key, key) == 0) {
        return table->entries[index]->function;
    }
    return NULL;
}