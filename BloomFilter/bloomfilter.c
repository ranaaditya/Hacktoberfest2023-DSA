#include <stdio.h>
#include <string.h>

#define FILTER_SIZE 1000

// Our bloom filter
char bloomFilter[FILTER_SIZE];

// Two simple hash functions
unsigned int hash1(const char* str) {
    unsigned int hash = 0;
    int c;
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash % FILTER_SIZE;
}

unsigned int hash2(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % FILTER_SIZE;
}

void addToFilter(const char* str) {
    bloomFilter[hash1(str)] = 1;
    bloomFilter[hash2(str)] = 1;
}

int lookupInFilter(const char* str) {
    return bloomFilter[hash1(str)] & bloomFilter[hash2(str)];
}

int main() {
    memset(bloomFilter, 0, FILTER_SIZE);

    addToFilter("Hello, World!");
    addToFilter("Testing");
    addToFilter("Bloom Filter");

    printf("Hello, World!: %d\n", lookupInFilter("Hello, World!"));
    printf("Testing: %d\n", lookupInFilter("Testing"));
    printf("Bloom Filter: %d\n", lookupInFilter("Bloom Filter"));
    printf("Not in filter: %d\n", lookupInFilter("Not in filter"));

    return 0;
}
