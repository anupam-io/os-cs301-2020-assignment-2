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

int main(int argc, char *argv[])
{
	int max_thread = atoi(argv[1]);
	int workload_size = atoi(argv[2]);
	int workload_pages = atoi(argv[3]);

	time_p = fopen("timings.csv", "w");
	perf_p = fopen("outputs.csv", "w");

	workload *w;

	for (int i = 0; i < 3; i++)
	{
		w = generate_workload(i, workload_pages, workload_size);
		for (int cs = 1; cs <= max_thread; cs++)
		{
			test_all(w, cs);
		}
		fprintf(time_p, "\n");
		fprintf(perf_p, "\n");
	}

	fclose(time_p);
	fclose(perf_p);
	return 0;
}