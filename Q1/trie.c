#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

trie_t init_trie(void){
    // Write your code here
    return (trie_t*)malloc(sizeof(trie_t));
} 

void insert(trie_t trie, char* key, int value){
    // Write your code here
    
}

int find(trie_t trie,char* key, int* val_ptr){
    // Write your code here
    return -1;
} 

void delete_kv(trie_t trie, char* key){
    // Write your code here
}

char** keys_with_prefix(trie_t trie, char* prefix){
    // Write your code here
    char** list = malloc(sizeof(char*));
    list[0] = NULL;
    return list;
}

void delete_trie(trie_t trie){
    // Write your code here
}