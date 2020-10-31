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
            t = NULL;
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
                t = NULL;

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

void _rec_auto_comp(trie_node_t root, char* curr_prefix, int curr_depth, char** list, int *total_words) 
{ 
    printf("_rec_auto_comp() called at %d.\n", curr_depth);
    // found a string in Trie with the given prefix 
    if (root->is_end) 
    { 
        // insert currPrefix into the list
        *total_words = (*total_words)+1;
        list[*total_words - 1] = (char*)malloc(strlen(curr_prefix)*sizeof(curr_prefix[0]));
        strcpy(list[*total_words-1], curr_prefix);

        list[*total_words] = NULL;
    } 
  

    // if no further children down below
    if (is_empty(root)){
        return;
    } 

    for (int i = 0; i < ALP_SIZE; i++) 
    { 
        if (root->children[i]) 
        { 
            // append current character to curr_prefix string
            curr_prefix[curr_depth] = 'a'+ i;     
            curr_prefix[curr_depth+1] = '\0'; 
        

            // do the recursion for this
            _rec_auto_comp(root->children[i], curr_prefix, curr_depth+1, list, total_words);

            // remove last character 
            curr_prefix[curr_depth] = '\0'; 
        } 
    } 
} 

char** keys_with_prefix(trie_t trie, char* prefix){
    const int MAX_LENGTH = 1000;
 
    printf("keys_with_prefix() called for prefix: %s\n", prefix);
    char** list = calloc(MAX_LENGTH, sizeof(char*)); 
    int total_words = 0;
    list[0] = NULL;
    
    trie_node_t t = trie->head;

    for(int l = 0; l<strlen(prefix); l++){
        if(t->children[prefix[l] - 'a']){
            // going down the trie
            t = t->children[prefix[l] - 'a'];
        } else {
            // no words found with given prefix
            return list;
        }
    }

    // now from this node, find all words and add prefix in the starting
    char* _prefix = calloc(MAX_LENGTH, sizeof(char));
    strcpy(_prefix, prefix);


    _rec_auto_comp(t, _prefix, strlen(_prefix), list, &total_words);
    // hope the above function works correctly

    printf("returning list from keys_with_prefix(),\ntotal words returning: %d\n", total_words);
    return list;
}

void _rec_delete_node(trie_node_t t){
    if(!t){
        return;
    }

    if(t->is_end){
        free(t);
        t = NULL;
        return;
    } 

    for(int i = 0; i<ALP_SIZE; i++){
        if(t->children[i]){
            _rec_delete_node(t->children[i]);
        }
    }
}

void delete_trie(trie_t trie){
    // Write your code here
    _rec_delete_node(trie->head);
    free(trie);
    trie = NULL;
}