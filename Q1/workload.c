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
    TOTAL_WORDS = 30000;
char* words[30000];

typedef struct workload
{
    trie_t trie;
    WorkloadT type;

    int total_threads;
    pthread_t *threads;

    int no_queries;
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

workload *generate_workload(WorkloadT type, int no_threads, int no_queries)
{
    workload *w = (workload *)malloc(sizeof(workload));
    w->trie = init_trie();
    w->type = type;

    w->no_queries = no_queries;
    w->total_threads = no_threads;
    w->threads = (pthread_t*)malloc(w->total_threads * sizeof(pthread_t));

    // inserting some initial words into the trie
    for (int i = 0; i < TOTAL_WORDS; i++)
    {
        insert(w->trie, words[i], 1);
    }

    return w;
}

void *th_func(void *x)
{
    // workload* w = (workload*)*((workload **)_w); // in case argument needs to be changed
    srand(time(0));


    if (w->type == READ)
    {
        // READ INTENSIVE WORKLOAD
        for (int i = 0; i < w->no_queries; i++)
        {
            int *res = malloc(sizeof(int));
            find(w->trie, words[rand()%TOTAL_WORDS], res);
        }
    }
    else if (w->type == WRITE)
    {
        // WRITE INTENSIVE WORKLOAD
        for (int i = 0; i < w->no_queries; i++)
        {
            insert(w->trie, words[rand()%TOTAL_WORDS], 1);
        }
    }
    else
    {
        // Mixed WORKLOAD
        for (int i = 0; i < w->no_queries; i++)
        {
            int *res = malloc(sizeof(int));

            if (rand() % 2)
            {
                find(w->trie, words[rand()%TOTAL_WORDS], res);
            }
            else
            {
                insert(w->trie, words[rand()%TOTAL_WORDS], 1);
            }
        }
    }
    return NULL;
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

    return;
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