#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "trie.h"

#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock

trie_node_t new_node(){
    // printf("new_node() called.\n");
    
    trie_node_t a = (trie_node_t)malloc(sizeof(_trie_node_t));
    a->is_end = false;
    a->value = 0;
    pthread_mutex_init(&a->node_lock, NULL);
    // a->node_lock = PTHREAD_MUTEX_INITIALIZER;

    for(int i = 0; i<ALP_SIZE; i++){
        a->children[i] = NULL;
    }

    return a;
}

trie_t init_trie(void){
    // printf("init_trie() called.\n");
    
    trie_t a = (trie_t)malloc(sizeof(_trie_t));
    a->head = new_node();
    return a;
}

void insert(trie_t trie, char* key, int value){
    // printf("insert() called.\n");
    
    trie_node_t x = trie->head;
    lock(&x->node_lock);
    
    for(int i = 0; i<strlen(key); i++){
        if(x->children[key[i] - 'a'] == NULL){
            x->children[key[i] - 'a'] = new_node();
        }

        unlock(&x->node_lock);
        x = x->children[key[i] - 'a'];
        lock(&x->node_lock);
    }

    x->is_end = true;
    x->value = value;

    unlock(&x->node_lock);
}

int find(trie_t trie, char* key, int* val_ptr){
    // printf("find() called.\n");

    trie_node_t x = trie->head;
    lock(&x->node_lock);

    for(int i = 0; i<strlen(key); i++){
        int index = key[i] - 'a';


        if(x->children[index]){
            unlock(&x->node_lock);
            x = x->children[index];
            lock(&x->node_lock);
        } else {
            unlock(&x->node_lock);
            return -1;
        }
    }


    if(x->is_end){ 
        *val_ptr = x->value;
        unlock(&x->node_lock);
        return 0;
    } else {
        unlock(&x->node_lock);
        return -1;
    }
}

// Two options here:
// Either make this function or
// add another var in the node
int is_empty(trie_node_t t){
    for(int i = 0; i<ALP_SIZE; i++){
        if(t->children[i]){
            return 0;
        }
    }
    return 1;
}

int _rec_delete(trie_node_t t, char* key, int curr_depth){
    // printf("_rec_delete() called, curr_depth: %d\n", curr_depth);
    // returning 1 means: have deleted this node
    // returning 0 means: not deleted hence, 
    // other nodes also won't get deleted as well
    if(!t){
        return 0;
    }

    lock(&t->node_lock);
    if(curr_depth == strlen(key)){
        if(t->is_end){
            t->is_end = false;
            t->value = 0;

            if(is_empty(t)){
                unlock(&t->node_lock);
                free(t);
                t = NULL;

                // printf("Last call at depth: %d\n", curr_depth);
                return 1;
            } else {
                unlock(&t->node_lock);
                return 0;
            }
        } else {
            unlock(&t->node_lock);
            return 0;
        }
    }
    
    if(t->children[key[curr_depth] - 'a']){
        int res = _rec_delete(t->children[key[curr_depth] - 'a'], key, curr_depth+1);

        if(res == 0){
            // printf("Call @ depth: %d direct returning\n", curr_depth);
            unlock(&t->node_lock);
            return 0;
        } else {
            t->children[key[curr_depth] - 'a'] = NULL;

            if(!t->is_end && is_empty(t)){
                unlock(&t->node_lock);
                free(t);
                t = NULL;

                // printf("Call @ depth: %d NODE DELETED.\n", curr_depth);
                return 1;
            } else {
                unlock(&t->node_lock);
                
                // printf("Call @ depth: %d returning without deleting as node has other children.\n ", curr_depth);
                return 0;
            }
        }
    }

    unlock(&t->node_lock);
    return 0;
}

void delete_kv(trie_t trie, char* key){
    // printf("delete_kv() called.\n");
    _rec_delete(trie->head, key, 0);
}

void _rec_auto_comp(trie_node_t t, char* curr_prefix, int curr_depth, char** list, int *total_words) 
{ 
    if(!t) return;

    // printf("_rec_auto_comp() called at %d.\ns", curr_depth);
    // found a string in Trie with the given prefix 
    lock(&t->node_lock);
    if (t->is_end)
    { 
        // insert currPrefix into the list
        *total_words = (*total_words)+1;
        list[*total_words - 1] = (char*)malloc((strlen(curr_prefix)+1)*sizeof(curr_prefix[0]));
        strcpy(list[*total_words-1], curr_prefix);

        list[*total_words] = NULL;
    } 
  

    // if no further children down below
    if (is_empty(t)){
        unlock(&t->node_lock);
        return;
    } 

    for (int i = 0; i < ALP_SIZE; i++) 
    { 
        if (t->children[i]) 
        { 
            // append current character to curr_prefix string
            curr_prefix[curr_depth] = 'a'+ i;     
            curr_prefix[curr_depth+1] = '\0'; 
        

            // do the recursion for this
            _rec_auto_comp(t->children[i], curr_prefix, curr_depth+1, list, total_words);

            // remove last character 
            curr_prefix[curr_depth] = '\0'; 
        } 
    } 

    unlock(&t->node_lock);
} 

char** keys_with_prefix(trie_t trie, char* prefix){
    // printf("keys_with_prefix() called for prefix: %s\n", prefix);
 
    const int MAX_LENGTH = 1000;
    char** list = (char**)malloc(MAX_LENGTH*sizeof(char*));

    int total_words = 0;
    list[0] = NULL;

    trie_node_t t = trie->head;
    lock(&t->node_lock);

    for(int i = 0; i<strlen(prefix); i++){
        if(t->children[prefix[i] - 'a']){
            // going down the trie
            unlock(&t->node_lock);
            t = t->children[prefix[i] - 'a'];
            lock(&t->node_lock);
        } else {
            unlock(&t->node_lock);
            // no words found with given prefix
            return list;
        }
    }
    unlock(&t->node_lock);

    // now from this node, find all words and add prefix in the starting
    char* _prefix = malloc(100*sizeof(char));
    strcpy(_prefix, prefix);


    // hope this function works correctly
    _rec_auto_comp(t, _prefix, strlen(_prefix), list, &total_words);

    // printf("returning list from keys_with_prefix(),\ntotal words returning: %d\n", total_words);
    return list;
}

void _rec_delete_node(trie_node_t t){
    if(!t){
        return;
    }

    lock(&t->node_lock);
    if(t->is_end){
        unlock(&t->node_lock);
        free(t);
        t = NULL;
        return;
    } 

    for(int i = 0; i<ALP_SIZE; i++){
        if(t->children[i]){
            _rec_delete_node(t->children[i]);
        }
    }
    unlock(&t->node_lock);
}

void delete_trie(trie_t trie){
    _rec_delete_node(trie->head);

    free(trie);
    trie = NULL;
}