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
		if(find(q, w->work[i]) == 1){
			hits++;
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
	// the percept of references found in memory
	int hits = 0;
	queue* q = new_queue();

	for(int i = 0; i<w->size; i++){
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

float policy_LRUapprox(workload* w, int cache_size)
{
	int hits = 0;
    queue* q = new_queue(); 
    int bitref[cache_size];
	for(int i = 0; i<cache_size; i++){
		bitref[i] = 0;
	} 
  

    // To find the first element that does not 
    // have the bitref set to true 
    int ptr = 0;
	// To check if the queue is filled up or not 
    int count = 0; 
    
	for (int i = 0; i < w->size; i++) { 
        if (find(q, w->work[i]) == 0) { 			
            
			if (count < cache_size) { 
            	// Queue is not filled up to capacity 
                push(q, w->work[i]);
                count++; 
            } 
            else { 
            	// Queue is filled up to capacity
                ptr = 0; 

                // Find the first value that has its 
                // bit set to 0 
                while (q->front) {
                    // If the value has bit set to 1 
                    // Set it to 0 
                    if(bitref[ptr % cache_size]){
                        bitref[ptr % cache_size] = 0;
					}else{
                    	// Found the bit value 0 
                        break; 
					}
  
                    ptr++; 
                } 
  
                // If the queue was empty 
                if (q->curr_size == 0) { 
                    pop(q); 
                    push(q, w->work[i]); 
                } 
  
                // If queue was not empty 
                else { 
                    int j = 0; 
  
                    // Rotate the queue and set the front's 
                    // bit value to 0 until the value where 
                    // the bitref = 0 
                    while (j < (ptr % cache_size)) { 
                        int t1 = q->front->data; 
                        pop(q); 
                        push(q, t1); 
                        int temp = bitref[0]; 
  
                        // Rotate the bitref array 
                        for (int counter = 0; counter < cache_size - 1; counter++) 
                            bitref[counter] = bitref[counter + 1]; 
                        bitref[cache_size - 1] = temp; 
                        j++; 
                    } 
  
                    // Remove front element 
                    // (the element with the bitref = 0) 
                    pop(q);
  
                    // Push the element from the 
                    // page array (next input) 
					push(q, w->work[i]); 
                } 
            } 
        } 
        else { 
        	// If the input for the iteration was a hit 
            queue* temp = copy_queue(q);
            int counter = 0; 

            while (temp->curr_size) { 
                if (temp->front->data == w->work[i]){
                    bitref[counter] = 1;
				} 
                counter++; 
                pop(temp); 
            } 
            
            hits++; 
        } 
    }
    
	return (float)(hits*100/w->size);
}

float policy_RANDOM(workload* w, int cache_size)
{
	// the percept of references found in memory
	int hits = 0;
	queue* q = new_queue();

	for(int i = 0; i<w->size; i++){
		if(find(q, w->work[i]) == 1){
			hits++;
		} else {
			push(q, w->work[i]);
			if(q->curr_size > cache_size){
				remove_random(q);
			}
		}
	}

	return (float)(hits*100/w->size);
}
