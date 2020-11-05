/* INSTRUCTIONS:

This file will contain all functions related with various policies.
Each policy must return the hit rate

*/

#include "definitions.h"

float policy_FIFO(workload* w, int cache_size)
{
	// the percept of references found in memory
	int hits = 0;
	queue* q = new_queue();

	for(int i = 0; i<w->size; i++){
		// if i in cache
		// mark it as a hit
		// else if i is not in cache
		// remove the last element in the cache
		// insert i into the cache
		if(find_and_remove(q, w->work[i]) == 1){
			hits++;
			push(q, w->work[i]);
		} else {
			push(q, w->work[i]);
			if(q->curr_size > cache_size){
				pop(q);
			}
		}
	}

	return (float)(hits*100/w->size);
}

float policy_LRU(workload* w, int cache_size)
{
	float hit_rate = 0;
	/* fill this */
	return hit_rate;
}

float policy_LRUapprox(workload* w, int cache_size)
{
	float hit_rate = 0;
	/* fill this */
	return hit_rate;
}

float policy_RANDOM(workload* w, int cache_size)
{
	float hit_rate = 0;
	/* fill this */
	return hit_rate;
}
