#ifndef _W_LOADS
#define _W_LOADS

#include "trie.h"
#include <time.h>
#include <stdio.h>
typedef enum enum_workload
{
    READ,
    WRITE,
    RW
} WorkloadT;




const int
    THREADS = 100,
    TOTAL_QUERIES = 10000,
    TOTAL_WORDS = 30000;

char* words[30000];



typedef struct workload
{
    trie_t trie;
    WorkloadT type;

    int total_threads;
    pthread_t *threads;

    double** timings;

} workload;

workload* w;

char *rand_word(int len)
{
    char *str = (char*)malloc(len * sizeof(char));
    for (int i = 0; i < len; i++)
    {
        str[i] = 'a' + rand() % 26;
    }
    return str;
}

workload *generate_workload(WorkloadT type)
{
    workload *w = (workload *)malloc(sizeof(workload));
    w->trie = init_trie();
    w->type = type;

    w->total_threads = THREADS;
    w->threads = (pthread_t*)malloc(w->total_threads * sizeof(pthread_t));

    w->timings = (double**)malloc(w->total_threads * sizeof(double *));
    for (int i = 0; i < w->total_threads; i++)
    {
        w->timings[i] = (double*)malloc(TOTAL_QUERIES * sizeof(double));
    }

    // inserting some initial words into the trie
    for (int i = 0; i < TOTAL_WORDS; i++)
    {
        insert(w->trie, words[i], 1);
    }

    // generating appropriate queries for the workload
    return w;
}

void *th_func(void *x)
{
    // workload* w = (workload*)*((workload **)_w); // in case argument needs to be changed
    int tno = *((int *)x);
    srand(time(0));

    clock_t t1, t2;

    if (w->type == READ)
    {
        // READ INTENSIVE WORKLOAD
        for (int i = 0; i < TOTAL_QUERIES; i++)
        {
            int *res = malloc(sizeof(int));
            t1 = clock();
            find(w->trie, words[rand()%TOTAL_WORDS], res);
            t2 = clock();

            w->timings[tno][i] = (double)(t2 - t1) / CLOCKS_PER_SEC;
        }
    }
    else if (w->type == WRITE)
    {
        // WRITE INTENSIVE WORKLOAD
        for (int i = 0; i < TOTAL_QUERIES; i++)
        {
            int *res = malloc(sizeof(int));
            t1 = clock();
            insert(w->trie, words[rand()%TOTAL_WORDS], 1);
            t2 = clock();

            w->timings[tno][i] = (double)(t2 - t1) / CLOCKS_PER_SEC;
        }
    }
    else
    {
        // Mixed WORKLOAD
        for (int i = 0; i < TOTAL_QUERIES; i++)
        {
            int *res = malloc(sizeof(int));

            if (rand() % 2)
            {
                t1 = clock();
                find(w->trie, words[rand()%TOTAL_WORDS], res);
                t2 = clock();
            }
            else
            {
                t1 = clock();
                insert(w->trie, words[rand()%TOTAL_WORDS], 1);
                t2 = clock();
            }

            w->timings[tno][i] = (double)(t2 - t1) / CLOCKS_PER_SEC;
        }
    }
}

void test_workload(workload *_w)
{
    w = _w;

    int tno[w->total_threads];
    for(int i = 0; i<w->total_threads; i++)
    {
        tno[i] = i;
    }

    for (int i = 0; i < w->total_threads; i++)
    {
        
        pthread_create(&w->threads[i], NULL, th_func, (void *)&tno[i]);
    }

    for (int i = 0; i < w->total_threads; i++)
    {
        pthread_join(w->threads[i], NULL);
    }
}

void print_workload(workload* w){
    for(int i = 0; i<w->total_threads; i++){
        for(int j = 0; j<TOTAL_QUERIES; j++){
            printf("%f\n", w->timings[i][j]);
        }
        printf("\n");
    }
}

void read_words(){
    FILE *file = fopen("words.txt", "r");
    char line[100];
    for(int i = 0; i<TOTAL_WORDS; i++){
        fscanf(file, "%s", line);
        words[i] = (char*)malloc(strlen(line)*sizeof(char));
        strcpy(words[i], line);
    }
    fclose(file);
}

#endif