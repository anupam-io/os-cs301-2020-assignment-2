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
#include "definitions.h"
#include "policy.c"
#include "workload.c"
#include "queue.c"

int main(int argc, char* argv[])
{
	tp = fopen("timings.csv", "w");

	workload* w;
	w = generate_workload(LOOP, 100, 10000);
	for(int cs = 1; cs<=100; cs++){
		test_all(w, cs);
	}
	printf("\n");
	fprintf(tp, "\n");

	
	w = generate_workload(RANDOM, 100, 10000);
	for(int cs = 1; cs<=100; cs++){
		test_all(w, cs);
	}
	printf("\n");
	fprintf(tp, "\n");
	
	w = generate_workload(LOCAL, 100, 10000);
	for(int cs = 1; cs<=100; cs++){
		test_all(w, cs);
	}

	return 0;
}