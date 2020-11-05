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
	workload* w;

	printf("Loop workload\n");
	w = generate_workload(LOOP, 10, 100);
	for(int i = 0; i<w->size; i++){
		printf("%d ", w->work[i]);
	} printf("\n");


	printf("Random workload\n");
	w = generate_workload(RANDOM, 10, 100);
	for(int i = 0; i<w->size; i++){
		printf("%d ", w->work[i]);
	} printf("\n");


	printf("Local workload\n");
	w = generate_workload(LOCAL, 10, 100);
	int fr[w->pages];
	for(int i = 0; i<w->pages; i++) fr[i] = 0;
	for(int i = 0; i<w->size; i++) fr[w->work[i]]++;
	for(int i = 0; i<w->pages; i++){
		printf("%d: %d\n", i, fr[i]);
	}
	
	return 0;
}