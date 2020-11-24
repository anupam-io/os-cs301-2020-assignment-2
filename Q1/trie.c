#ifndef TRIE_C
#define TRIE_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "trie.h"

void r_lock(trie_t x){
    #ifndef _NO_HOH_LOCK_TRIE
        ;
    #else
        #ifdef _S_LOCK_TRIE
            pthread_mutex_lock(&x->s_lock);
        #else
            pthread_rwlock_rdlock(&x->rw_lock);
        #endif
    #endif
}

void w_lock(trie_t x){
    #ifndef _NO_HOH_LOCK_TRIE
        ;
    #else
        #ifdef _S_LOCK_TRIE
            pthread_mutex_lock(&x->s_lock);
        #else
            pthread_rwlock_wrlock(&x->rw_lock);
        #endif
    #endif
}
void unlock(trie_t x){
    #ifndef _NO_HOH_LOCK_TRIE
        ;
    #else
        #ifdef _S_LOCK_TRIE
            pthread_mutex_unlock(&x->s_lock);
        #else
            pthread_rwlock_unlock(&x->rw_lock);
        #endif
    #endif   
}


/*
#ifndef _NO_HOH_LOCK_TRIE
// HOH_LOCK_TRIE
    #define r_lock(x) ;
    #define w_lock(x) ;
    #define unlock(x) ;
#else
    #ifdef _S_LOCK_TRIE
    // S_LOCK_TRIE AS WELL AS ST_TRIE
        #define r_lock(x) pthread_mutex_lock(&x->s_lock)
        #define w_lock(x) pthread_mutex_lock(&x->s_lock)
        #define unlock(x) pthread_mutex_unlock(&x->s_lock)
    #else
    // RW_LOCK_TRIE
        #define r_lock(x) pthread_rwlock_rdlock(&x-rw_lock)
        #define w_lock(x) pthread_rwlock_wrlock(&x->rw_lock)
        #define unlock(x) pthread_rwlock_unlock(&x->rw_lock)
    #endif
#endif
*/






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
    #ifndef _NO_HOH_LOCK_TRIE
        printf("*\n*\n*\n*\n*\nHOH_LOCK_TRIE\n*\n*\n*\n*\n*\n");
    #else
        #ifdef _S_LOCK_TRIE
            printf("*\n*\n*\n*\n*\nS_LOCK_TRIE\n*\n*\n*\n*\n*\n");
        #else
            printf("*\n*\n*\n*\n*\nRW_LOCK_TRIE\n*\n*\n*\n*\n*\n");
        #endif
    #endif



    trie_t a = (trie_t)malloc(sizeof(_trie_t));
    a->head = new_node();
    

    #ifdef _S_LOCK_TRIE
        pthread_mutex_init(&a->s_lock, NULL);
    #endif

    #ifdef _NO_HOH_LOCK_TRIE
        #ifndef _S_LOCK_TRIE
            pthread_rwlock_init(&a->rw_lock, NULL);
        #endif
    #endif

    return a;
}

void insert(trie_t trie, char* key, int value){
    // printf("insert() called.\n");
    w_lock(trie);

    #ifndef _NO_HOH_LOCK_TRIE
        pthread_mutex_t *l1, *l2;
        l1 = l2 = NULL;
        l2 = &trie->head->node_lock;
        pthread_mutex_lock(&(*l2));   
    #endif

    trie_node_t x = trie->head;
    
    for(int i = 0; i<strlen(key); i++){
        if(x->children[key[i] - 'a'] == NULL){
            x->children[key[i] - 'a'] = new_node();
        }
        x = x->children[key[i] - 'a'];

        #ifndef _NO_HOH_LOCK_TRIE
            if(l1){
                pthread_mutex_unlock(&(*l1));
            }
            l1 = l2;
            l2 = &x->node_lock;
            pthread_mutex_lock(&(*l2));
        #endif
    }

    x->is_end = true;
    x->value = value;

    #ifndef _NO_HOH_LOCK_TRIE
        if(l1){ pthread_mutex_unlock(&(*l1)); }
        if(l2){ pthread_mutex_unlock(&(*l2)); }
    #endif

    unlock(trie);
}

int find(trie_t trie, char* key, int* val_ptr){
    // printf("find() called.\n");
    r_lock(trie);
    int ret = 70;

    #ifndef _NO_HOH_LOCK_TRIE
        pthread_mutex_t *l1, *l2;
        l1 = l2 = NULL;
        l2 = &trie->head->node_lock;
        pthread_mutex_lock(&(*l2));   
    #endif

    trie_node_t x = trie->head;

    for(int i = 0; i<strlen(key); i++){
        int index = key[i] - 'a';


        if(x->children[index]){
            x = x->children[index];    
        } else {
            ret = -1;
            break;
        }


        #ifndef _NO_HOH_LOCK_TRIE
            if(l1){
                pthread_mutex_unlock(&(*l1));
            }
            l1 = l2;
            l2 = &x->node_lock;
            pthread_mutex_lock(&(*l2));
        #endif
    }

    if(ret == 70){
        if(x->is_end){ 
            *val_ptr = x->value;
            ret = 0;
        } else {
            ret = -1;
        }
    }

    #ifndef _NO_HOH_LOCK_TRIE
        if(l1){ pthread_mutex_unlock(&(*l1)); }
        if(l2){ pthread_mutex_unlock(&(*l2)); }
    #endif

    unlock(trie);
    return ret;
}

void delete_kv(trie_t trie, char* key){
  // printf("find() called.\n");
    int ret = 0;
    r_lock(trie);

    #ifndef _NO_HOH_LOCK_TRIE
        pthread_mutex_t *l1, *l2;
        l1 = l2 = NULL;
        l2 = &trie->head->node_lock;
        pthread_mutex_lock(&(*l2));   
    #endif

    trie_node_t x = trie->head;

    for(int i = 0; i<strlen(key); i++){
        int index = key[i] - 'a';

        if(x->children[index]){
            x = x->children[index];    
        } else {
            ret = 1;
            break;
        }

        #ifndef _NO_HOH_LOCK_TRIE
            if(l1){
                pthread_mutex_unlock(&(*l1));
            }
            l1 = l2;
            l2 = &x->node_lock;
            pthread_mutex_lock(&(*l2));
        #endif
    }

    if(ret == 0){
        if(x->is_end){ 
            x->is_end = false;
            ret = 1;
        }
    }

    #ifndef _NO_HOH_LOCK_TRIE
        if(l1){ pthread_mutex_unlock(&(*l1)); }
        if(l2){ pthread_mutex_unlock(&(*l2)); }
    #endif

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
        list[*total_words] = (char*)malloc((strlen(curr_prefix)+1)*sizeof(curr_prefix[0]));
        strcpy(list[*total_words], curr_prefix);
        *total_words = *total_words + 1;

        list[*total_words] = NULL;
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
            unlock(trie);
            return list;
        }
    }

    // now from this node, find all words and add prefix in the starting
    char* _prefix = malloc(100*sizeof(char));
    strcpy(_prefix, prefix);


    // hope this function works correctly
    _rec_auto_comp(t, _prefix, strlen(_prefix), list, &total_words);

    // printf("returning list from keys_with_prefix(),\ntotal words returning: %d\n", total_words);
    unlock(trie);
    free(_prefix);
    return list;
}

void _rec_delete_node(trie_node_t t){
    if(!t){
        return;
    }

    for(int i = 0; i<ALP_SIZE; i++){
        if(t->children[i]){
            _rec_delete_node(t->children[i]);
        }
    }

    free(t);
}

void delete_trie(trie_t trie){
    _rec_delete_node(trie->head);
    free(trie);
}

#endif