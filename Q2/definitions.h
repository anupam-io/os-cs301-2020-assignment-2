/* 
INSTRUCTIONS:

All enum, structs and functions to be declared here.
If a definition is already declared, do not change it.
You may add extra definitions as required.

*/

#ifndef __DEF_H__
#define __DEF_H__

//----------------------------------------------------------------
//----------------------------------------------------------------
/* ALL ENUMERATORS HERE */

// LOOP - Workload type for Loop
// RANDOM - Workload type for RANDOM
// LOCAL - 80-20 workload type

typedef enum enum_workloads{LOOP, RANDOM, LOCAL}WorkloadsT;

//----------------------------------------------------------------
//----------------------------------------------------------------
/* ALL STRUCTS HERE */

typedef struct workload
{
	// Defines type of workload
	WorkloadsT type;
	// The number of pages in workload
	int pages;
	// The total size of the workload
	int size;
	// The final work to run the policy
	int * work;
}workload;

//----------------------------------------------------------------
//----------------------------------------------------------------
/* ALL FUNCTION DEFINITIONS HERE */

workload * generate_workload(WorkloadsT type, int pages, int size);
workload * generate_random(workload* w);
workload * generate_loop(workload* w);
workload * generate_local(workload* w);

float policy_FIFO(workload* w, int cache_size);
float policy_LRU(workload* w, int cache_size);
float policy_RANDOM(workload* w, int cache_size);
float policy_LRUapprox(workload* w, int cache_size);

#endif /* __DEF_H__ */
