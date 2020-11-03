#define _S_LOCK_TRIE
// #define _NO_HOH_LOCK_TRIE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "trie.h"
#include "trie.c"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define RED     "\033[31m"      /* Red */
#define ff fflush(stdout)

trie_t trie;

void test_file_diff(char* f1, char* f2){
    char command[200];
    sprintf(command,"cmp -s %s %s && echo \"\\033[32mPassed\" || echo \"\\033[31mFailure\"",f1, f2);
    system(command);
}

void* insert_task(void *tnum){
    int t = *((int *) tnum);
    char key[15];
    int val;
    char ins_file_name[100];
    sprintf(ins_file_name, "./tests/multi_thread/initial/%d.txt",t);
    FILE* ins_file = fopen(ins_file_name,"r");
    while (1)
    {
        fscanf(ins_file,"%s",key);
        if (key[0]=='-') break;
        fscanf(ins_file,"%d",&val);
        insert(trie,key,val);
    }
    fclose(ins_file);
    return NULL;
}

void* find_task(void *tnum){
    int t = *((int *) tnum);
    char key[15];
    char find_test_name[100];
    sprintf(find_test_name,"./tests/multi_thread/find/%d.txt",t);
    FILE* find_test = fopen(find_test_name,"r");
    char find_test_exp_name[100];
    sprintf(find_test_exp_name,"./.testout/exp_find_%d.txt",t);
    FILE* find_test_exp = fopen(find_test_exp_name,"w");
    while (1)
    {
        int f_ret = -101;
        fscanf(find_test,"%s",key);
        if (key[0]=='-') break;
        if(find(trie,key,&f_ret)==-1) fprintf(find_test_exp,"NO\n");
        else fprintf(find_test_exp,"YES\n");
    }
    fclose(find_test);
    fclose(find_test_exp);
    return NULL;
}

int main(int argc, char* argv[]){
    // Trie test begins
    trie = init_trie();
    char key[15];
    int val;
    int narr[5] = {0,1,2,3,4};

    // Inserting
    printf(YELLOW "Testing Insert..." RESET);
    pthread_t ins_threads[3];
    pthread_create(&ins_threads[0], NULL, insert_task,(void *)&narr[1]);
    pthread_create(&ins_threads[1], NULL, insert_task,(void *)&narr[2]);
    pthread_create(&ins_threads[2], NULL, insert_task,(void *)&narr[3]);

    pthread_join(ins_threads[0],NULL);
    pthread_join(ins_threads[1],NULL);
    pthread_join(ins_threads[2],NULL);

    // Test trie state after insert
    char * ins_exp_name = "./tests/multi_thread/initial/exp_ins.txt";
    FILE* ins_exp = fopen(ins_exp_name,"r");
    int err = 0;
    while (1)
    {
        int f_ret = -101;
        fscanf(ins_exp,"%s",key);
        if (key[0]=='-') break;
        fscanf(ins_exp,"%d",&val);
        find(trie,key,&f_ret);
        if (f_ret!=val){
            err = 1;
            break;
        }
    }
    fclose(ins_exp);
    if(err==1) printf(RED "Failure\n" RESET);
    else printf(GREEN "Passed\n" RESET);

    // Test find
    printf(YELLOW "Testing Find...\n" RESET);ff;
    pthread_t find_threads[3];
    pthread_create(&find_threads[0], NULL, find_task,(void *)&narr[1]);
    pthread_create(&find_threads[1], NULL, find_task,(void *)&narr[2]);
    pthread_create(&find_threads[2], NULL, find_task,(void *)&narr[3]);

    pthread_join(find_threads[0],NULL);
    pthread_join(find_threads[1],NULL);
    pthread_join(find_threads[2],NULL);
    printf(YELLOW "Thread 1: " RESET);ff;
    test_file_diff("./tests/multi_thread/find/exp_find_1.txt","./.testout/exp_find_1.txt");
    printf(YELLOW "Thread 2: " RESET);ff;
    test_file_diff("./tests/multi_thread/find/exp_find_2.txt","./.testout/exp_find_2.txt");
    printf(YELLOW "Thread 3: " RESET);ff;
    test_file_diff("./tests/multi_thread/find/exp_find_3.txt","./.testout/exp_find_3.txt");

    
    // Delete the trie
    delete_trie(trie);
    return 0;
}