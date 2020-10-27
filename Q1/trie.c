#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"


// trie_t
// trie_t_node



trie_node_t new_node(){
    printf("new_node() called.\n");
    _trie_node_t* a = (_trie_node_t*)malloc(sizeof(_trie_node_t));
    a->is_end = false;
    a->value = 0; // $
    for(int i = 0; i<ALP_SIZE; i++){
        a->children[i] = NULL;
    }
    return a;
}

trie_t init_trie(void){
    // Write zyour code here
    trie_t a = (trie_t)malloc(sizeof(_trie_t));
    a->head = new_node(0);
    return a;
}

void insert(trie_t trie, char* key, int value){
    printf("insert called.\n");
    // Write your code here
    trie_node_t x = trie->head;
    int key_length = strlen(key);

    for(int i = 0; i<key_length; i++){
        int index = key[i] - 'a';    
        trie_node_t a = x->children[index];
        
        if(x->children[index] == NULL){
            x->children[index] = new_node();
        }
        x = x->children[index];
    }

    x->value = value;
}

int find(trie_t trie, char* key, int* val_ptr){
    // Write your code here
    int key_length = strlen(key);
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