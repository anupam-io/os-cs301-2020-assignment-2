/*
INSTRUCTIONS:
This file must include only the main function
The main function should print out the various cases
and finally print out tables showing the performance
of various policies with the different workloads.
Vary the cache size.

You may include a function or 2 to ease the printing of tables.

*/
#include <stdio.h>
#include <stdlib.h>
#include "policy.c"
#include "definitions.h"
#include "workload.c"

int main(int argc, char* argv[])
{	
	int size = 100;
	int pages = 10;

	int* data = (int*)malloc(size*sizeof(int));
	for(int i = 0; i<size; i++){
		data[i] = (i*i*i)%pages;
	}

	workload* w = (workload*)malloc(sizeof(workload));
	w->type = 0;
	w->pages = pages;
	w->size = size;
	w->work = data;

	

	return 0;
}