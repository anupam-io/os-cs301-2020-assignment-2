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
    a->value = -1; // $
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
    printf("insert() called.\n");
    // Write your code here
    trie_node_t x = trie->head;
    int key_length = strlen(key);

    for(int i = 0; i<key_length; i++){
        int index = key[i] - 'a';    
        
        if(x->children[index] == NULL){
            x->children[index] = new_node();
        }
        x = x->children[index];
    }

    x->is_end = true;
    x->value = value;
}

int find(trie_t trie, char* key, int* val_ptr){
    printf("find() called.\n");
    // Write your code here
    int key_length = strlen(key);
    trie_node_t x = trie->head;
    
    for(int i = 0; i<key_length; i++){
        int index = key[i] - 'a';


        if(x->children[index]!=NULL){
            x = x->children[index];
        } else {
            return -1;
        }
    }

    if(x->is_end){ 
        x->value = *val_ptr;
        return 0;
    } else {
        return -1;
    }
} 

// Two options here:
// Either make this function or
// add another var in the node
int is_empty(trie_node_t t){
    if(!t){
        return 1;
    }
    
    for(int i = 0; i<ALP_SIZE; i++){
        if(t->children[i]){
            return 0;
        }
    }

    return 1;
}

int _rec_delete(trie_node_t t, char* key, int curr_depth){
    // returning 1 means: have deleted this node
    // returning 0 means: not deleted hence, 
    // other nodes also won't get deleted as well
    if(!t){
        return 0;
    }

    if(curr_depth == strlen(key)){
        if(t->is_end){
            t->is_end = false;
            free(t);
            return 1;
        } else {
            return 0;
        }
    }
    
    if(t->children[key[curr_depth] - 'a']){
        int res = _rec_delete(t->children[key[curr_depth] - 'a'], key, curr_depth+1);
        if(res == 0){
            return 0;
        } else {
            t->children[key[curr_depth] - 'a'] = NULL;
            if(is_empty(t)){
                free(t);
                return 1;
            } else {
                return 0;
            }
        }
    } else {
        return 0;
    }

    printf("Error occured in _rec_delete() !!! \n");
    exit(0);
    return 100;
}

void delete_kv(trie_t trie, char* key){
    // Write your code here
    if(trie->head == NULL) return;
    _rec_delete(trie->head, key, 0);

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