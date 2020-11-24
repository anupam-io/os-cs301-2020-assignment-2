#ifndef _W_LOADS
#define _W_LOADS

#include "trie.h"
typedef enum enum_workload{READ, WRITE, RW}WorkloadT;

typedef struct workload
{
    trie_t trie;

    WorkloadT type;

    
}workload;

void make_trie(trie_t trie){
    // insert some words into the trie, lets say 10000
    // create random words
    // insert into the trie

}

workload* generate_workload(WorkloadT type){
    // set read and write commands
    // decide hwo many commands to make
    

}



#endif