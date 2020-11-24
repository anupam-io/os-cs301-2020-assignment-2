#ifndef _W_LOADS
#define _W_LOADS

#include "trie.h"
typedef enum enum_workload{READ, WRITE, RW}WorkloadT;

const int 
    INIT_WORDS = 1000,
    TOTAL_QUERIES = 1000,
    WORD_LEN = 5;

typedef struct workload
{
    trie_t trie;
    WorkloadT type;
    char** ins;
    char** fin;
}workload;

char* rand_word(int len){
    char* str = malloc(len*sizeof(char));
    for(int i = 0; i<len; i++){
        str[i] = 'a'+ rand()%26;
    }
    return str;
}

workload* generate_workload(WorkloadT type){
    workload* w = (workload*)malloc(sizeof(workload));
    w->trie = init_trie();
    w->type = type;

    // inserting some initial words into the trie
    for(int i = 0; i<INIT_WORDS; i++){
        insert(w->trie, rand_word(WORD_LEN), 1);
    }

    // generating appropriate queries for the workload
    if(type == READ){
        w->fin = malloc(TOTAL_QUERIES*sizeof(char*));
        for(int i = 0; i<TOTAL_QUERIES; i++){
            w->fin[i] = rand_word(WORD_LEN);
        }
    }
    return w;
}

void test_workload(workload* w){
    if(w->type == READ){
        for(int i = 0; i<TOTAL_QUERIES; i++){
            int* res = malloc(sizeof(int));
            find(w->trie, w->fin[i], res);
        }
    }    
}

#endif