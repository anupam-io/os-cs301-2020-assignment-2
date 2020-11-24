#define _NO_HOH_LOCK_TRIE
// #define _S_LOCK_TRIE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "trie.c"
#include <time.h>
#include "workload.c"

int main(){
    read_words();
    clock_t t1, t2;

    workload* w;



    w = generate_workload(READ);    
    t1 = clock();
    test_workload(w);
    t2 = clock();
    // print_workload(w);
    printf("READ: %f microseconds.\n", 1000*(double)(t2 - t1)/CLOCKS_PER_SEC);

    w = generate_workload(WRITE);    
    t1 = clock();
    test_workload(w);
    t2 = clock();
    // print_workload(w);
    printf("WRITE: %f microseconds.\n", 1000*(double)(t2 - t1)/CLOCKS_PER_SEC);

    w = generate_workload(RW);    
    t1 = clock();
    test_workload(w);
    t2 = clock();
    // print_workload(w);
    printf("READ-WRITE: %f microseconds.\n", 1000*(double)(t2 - t1)/CLOCKS_PER_SEC);
    
    
    return 0;
}
