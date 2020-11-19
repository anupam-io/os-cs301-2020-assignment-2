#ifndef TRIE_C
#define TRIE_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "trie.h"

#ifndef _NO_HOH_LOCK_TRIE
// HOH_LOCK_TRIE
// temporarily same as st and s_lock
    #define r_lock(x) ;
    #define w_lock(x) ;
    #define unlock(x) ;

#endif

#ifdef _NO_HOH_LOCK_TRIE
    #ifdef _S_LOCK_TRIE
    // S_LOCK_TRIE AS WELL AS ST_TRIE
        #define r_lock(x) pthread_mutex_lock(&x->s_lock)
        #define w_lock(x) pthread_mutex_lock(&x->s_lock)
        #define unlock(x) pthread_mutex_unlock(&x->s_lock)
    #endif

    #ifndef _S_LOCK_TRIE
    // RW_LOCK_TRIE
        #define r_lock(x) pthread_rwlock_rdlock(&x->rw_lock)
        #define w_lock(x) pthread_rwlock_wrlock(&x->rw_lock)
        #define unlock(x) pthread_rwlock_unlock(&x->rw_lock)
    #endif
#endif

trie_node_t new_node(){
    // printf("new_node() called.\n");
    
    trie_node_t a = (trie_node_t)malloc(sizeof(_trie_node_t));
    a->is_end = false;
    a->value = 0;

    #ifndef _NO_HOH_LOCK_TRIE
        pthread_mutex_init(&a->node_lock, NULL);
    #endif 

    for(int i = 0; i<ALP_SIZE; i++){
        a->children[i] = NULL;
    }

    return a;
}

trie_t init_trie(void){
    // printf("init_trie() called.\n");
    
    trie_t a = (trie_t)malloc(sizeof(_trie_t));
    a->head = new_node();
    
    #ifdef _S_LOCK_TRIE
        pthread_mutex_init(&a->s_lock, NULL);
    #endif
    #ifdef _NO_HOH_LOCK_TRIE
        #ifndef _S_LOCK_TRIE     
            pthread_rwlock_init(&a->s_lock, NULL);
        #endif
    #endif
    return a;
}

void insert(trie_t trie, char* key, int value){
    // printf("insert() called.\n");
    w_lock(trie);

    trie_node_t x = trie->head;
    
    for(int i = 0; i<strlen(key); i++){
        if(x->children[key[i] - 'a'] == NULL){
            x->children[key[i] - 'a'] = new_node();
        }
        x = x->children[key[i] - 'a'];
    }

    x->is_end = true;
    x->value = value;

    unlock(trie);
}

int find(trie_t trie, char* key, int* val_ptr){
    // printf("find() called.\n");
    r_lock(trie);

    trie_node_t x = trie->head;

    for(int i = 0; i<strlen(key); i++){
        int index = key[i] - 'a';


        if(x->children[index]){
            x = x->children[index];
        } else {
            unlock(trie);
            return -1;
        }
    }


    if(x->is_end){ 
        *val_ptr = x->value;
        unlock(trie);
        return 0;
    } else {
        unlock(trie);
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

    if(curr_depth == strlen(key)){
        if(t->is_end){
            t->is_end = false;
            t->value = 0;

            if(is_empty(t)){
                free(t);
                t = NULL;

                // printf("Last call at depth: %d\n", curr_depth);
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    
    if(t->children[key[curr_depth] - 'a']){
        int res = _rec_delete(t->children[key[curr_depth] - 'a'], key, curr_depth+1);

        if(res == 0){
            // printf("Call @ depth: %d direct returning\n", curr_depth);
            return 0;
        } else {
            t->children[key[curr_depth] - 'a'] = NULL;

            if(!t->is_end && is_empty(t)){
                free(t);
                t = NULL;

                // printf("Call @ depth: %d NODE DELETED.\n", curr_depth);
                return 1;
            } else {
                
                // printf("Call @ depth: %d returning without deleting as node has other children.\n ", curr_depth);
                return 0;
            }
        }
    }

    return 0;
}

void delete_kv(trie_t trie, char* key){
    // printf("delete_kv() called.\n");
    w_lock(trie);
    _rec_delete(trie->head, key, 0);
    unlock(trie);
}

void _rec_auto_comp(trie_node_t t, char* curr_prefix, int curr_depth, char** list, int *total_words) 
{ 
    if(!t) return;

    // printf("_rec_auto_comp() called at %d.\ns", curr_depth);
    // found a string in Trie with the given prefix 
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
} 

char** keys_with_prefix(trie_t trie, char* prefix){
    // printf("keys_with_prefix() called for prefix: %s\n", prefix);
    r_lock(trie);

    const int MAX_LENGTH = 1000;
    char** list = (char**)malloc(MAX_LENGTH*sizeof(char*));

    int total_words = 0;
    list[0] = NULL;

    trie_node_t t = trie->head;

    for(int i = 0; i<strlen(prefix); i++){
        if(t->children[prefix[i] - 'a']){
            // going down the trie
            t = t->children[prefix[i] - 'a'];
        } else {
            // no words found with given prefix
            return list;
        }
    }

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
    _rec_delete_node(trie->head);

    free(trie);
    trie = NULL;
}

#endif