// #define _NO_HOH_LOCK_TRIE
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
    FILE *fp = fopen("wl/hoh_lock.csv", "w");

    read_words();
    clock_t begin, finish;
    double dur;

    workload* w;


    for(int i = 0; i<3; i++){
        for(int t = 2; t<=30; t+=2){
            w = generate_workload(i, t, 1000);  
            begin = clock();
            test_workload(w);
            finish = clock();
            dur = 1000*(double)(finish - begin)/CLOCKS_PER_SEC;
            fprintf(fp, "%d, %f\n", t, dur);
        }
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    return 0;
}
