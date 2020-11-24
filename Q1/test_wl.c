#define _NO_HOH_LOCK_TRIE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "trie.c"
#include "workload.c"

int main(){
    workload* w = generate_workload(READ);
    test_workload(w);
    
    
    return 0;
}
