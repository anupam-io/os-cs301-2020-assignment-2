/*
INSTRUCTIONS:

This file will contain all the functions related to the generation of workload

*/

#include "definitions.h"
#include "time.h"

workload* generate_workload(WorkloadsT type, int pages, int size)
{
    workload* w = (workload*)malloc(sizeof(workload));
    w->type = type;
    w->pages = pages;
    w->size = size;
    w->work = (int*)malloc(w->size*sizeof(int));

    if(type == LOOP){
        generate_loop(w);
    } else if(type == RANDOM) {
        generate_random(w);
    } else {
        generate_local(w);
    }
    
    return w;
}

workload* generate_random(workload* w)
{
    srand(time(0));
    int ind = 0;
    while(ind!=w->size){
        w->work[ind++] = rand()%w->pages; 
    }

    return w;
}

workload* generate_loop(workload* w)
{
    printf("loop called.\n");
    int ind = 0, i = 0;

    while(ind!=w->size){
        w->work[ind++] = i++;
        if(i == w->pages){
            i = 0;
        }
    }

    return w;
}

workload* generate_local(workload* w)
{
    // case1: 80% of the references from 20% of the pages
    // case2: 20% of the references from 80% of the pages
    srand(time(0));
    
    int ind = 0;
    int mid = 20*w->pages/100;

    while (ind!=w->size){
        int r = rand()%100;
        if(r<80){
            w->work[ind++] = rand()%mid;
        } else {
            w->work[ind++] = rand()%(w->pages-mid) + mid;
        }
    }
    
    return w;
}