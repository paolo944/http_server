#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 2

typedef void (*FunctionPointer)(int, const char *buffer);

typedef struct {
    char *key;
    FunctionPointer function;
} HashEntry;

typedef struct {
    HashEntry *entries[TABLE_SIZE];
} HashTable;

unsigned int hashFunction(const char *key);

void initializeHashTable(HashTable *table);

void insert(HashTable *table, const char *key, FunctionPointer function);

FunctionPointer getFunction(HashTable *table, const char *key);

void freeHashTable(HashTable *table);

#endif