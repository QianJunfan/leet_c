#include <stdlib.h>

// Solution 1 - Brute Force Approach - O(n^2)
int* twoSum_brute_force(int* nums, int numsSize, int target, int* returnSize) {
    // Init.
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    // Prog.
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                
                return result;
            }
        }
    }
    
    // In case no solution is found. (though problem states there is exactly one)
    *returnSize = 0;
    free(result);
    
    return NULL;
}

// Solution 2 - Hash Table Approach - O(n)
#define HASH_SIZE 10000

typedef struct HashNode {
    int key;
    int value;
    
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode* buckets[HASH_SIZE];
} HashTable;

HashTable* init() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < HASH_SIZE; i++) {
        table -> buckets[i] = NULL;
    }
    
    return table;
}

void insert(HashTable* table, int key, int value) {
    int index = key % HASH_SIZE;
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    
    node->key   = key;
    node->value = value;
    node->next  = table -> buckets[index];
    
    table->buckets[index] = node;
}

int find(HashTable* table, int key) {
    int index = key % HASH_SIZE;
    HashNode* current = table -> buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return current -> value;
        }
        current = current -> next;
    }
    return -1;
}

void deallocate(HashTable* table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* current = table -> buckets[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current -> next;
            free(temp);
        }
    }
    free(table);
}

int* twoSum_hash_table(int* nums, int numsSize, int target, int* returnSize) {
    // Init.
    HashTable* table = init();
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    // Prog.
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complement_index = find(table, complement);
        if (complement_index != -1) {
            result[0] = complement_index;
            result[1] = i;
            deallocate(table);
            
            return result;
        }
        
        insert(table, nums[i], i);
    }
    
    // Shouldn't reach here per problem statement.
    *returnSize = 0;

    free(result);
    deallocate(table);
    
    return NULL;
}

