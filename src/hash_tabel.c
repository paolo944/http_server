#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"

unsigned int hashFunction(const char *key)
{
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % TABLE_SIZE;
}

void initializeHashTable(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->entries[i] = NULL;
    }
}

void insert(HashTable *table, const char *key, FunctionPointer function)
{
    unsigned int index = hashFunction(key);
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int newIndex = (index + i) % TABLE_SIZE;

        if (table->entries[newIndex] == NULL) {
            table->entries[newIndex] = (HashEntry *)malloc(sizeof(HashEntry));
            table->entries[newIndex]->key = strdup(key);
            table->entries[newIndex]->function = function;
            return;
        } else if (strcmp(table->entries[newIndex]->key, key) == 0) {
            table->entries[newIndex]->function = function;
            return;
        }
    }

    printf("Erreur : Table de hachage pleine !\n");
}

FunctionPointer getFunction(HashTable *table, const char *key)
{
    unsigned int index = hashFunction(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int newIndex = (index + i) % TABLE_SIZE;

        if (table->entries[newIndex] == NULL) {
            return NULL;  // La clé n'existe pas
        } else if (strcmp(table->entries[newIndex]->key, key) == 0) {
            return table->entries[newIndex]->function;
        }
    }

    return NULL;
}

void freeHashTable(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->entries[i]) {
            free(table->entries[i]->key);
            free(table->entries[i]);
        }
    }
}
