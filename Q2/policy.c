/* INSTRUCTIONS:

This file will contain all functions related with various policies.
Each policy must return the hit rate

*/

#include "definitions.h"
#include <time.h>

float policy_FIFO(workload *w, int cache_size)
{
    int hits = 0;
    queue *q = new_queue();

    for (int i = 0; i < w->size; i++)
    {
        if (find(q, w->work[i]) == 1)
        {
            hits++;
        }
        else
        {
            push(q, w->work[i]);
            if (q->curr_size > cache_size)
            {
                pop(q);
            }
        }
    }

    return (float)hits * 100 / w->size;
}

float policy_RANDOM(workload *w, int cache_size)
{
    int hits = 0;
    queue *q = new_queue();

    for (int i = 0; i < w->size; i++)
    {
        if (find(q, w->work[i]) == 1)
        {
            hits++;
        }
        else
        {
            push(q, w->work[i]);
            if (q->curr_size > cache_size)
            {
                remove_random(q);
            }
        }
    }

    return (float)hits * 100 / w->size;
}

float policy_LRU(workload *w, int cache_size)
{
    int hits = 0;
    queue *q = new_queue();

    for (int i = 0; i < w->size; i++)
    {
        if (find_and_remove(q, w->work[i]) == 1)
        {
            hits++;
            push(q, w->work[i]);
        }
        else
        {
            push(q, w->work[i]);
            if (q->curr_size > cache_size)
            {
                pop(q);
            }
        }
    }

    return (float)hits * 100 / w->size;
}

float policy_LRUapprox(workload *w, int cache_size)
{
    int hits = 0;
    queue *q = new_queue();
    int bitref[cache_size];
    for (int i = 0; i < cache_size; i++)
    {
        bitref[i] = 0;
    }

    // To find the first element that does not
    // have the bitref set to true
    int ptr = 0;

    for (int i = 0; i < w->size; i++)
    {

        if (find(q, w->work[i]) == 0)
        {
            // Pushing into the queue, when it is not full
            if (q->curr_size < cache_size)
            {
                push(q, w->work[i]);
            }
            // Queue if full
            else
            {
                ptr = 0;

                // Find the first value that has its
                // bit set to 0
                while (q->curr_size)
                {
                    if (bitref[ptr % cache_size])
                    {
                        // setting 0 to the values which were 1
                        bitref[ptr % cache_size] = 0;
                    }
                    else
                    {
                        // breaking as the value 0 found
                        break;
                    }
                    ptr++;
                }

                // If the queue was empty
                if (q->curr_size == 0)
                {
                    push(q, w->work[i]);
                }
                // If queue was not empty
                else
                {
                    int j = 0;
                    // Rotate the queue
                    // if bitref = 0, break
                    // else set bitref as 0
                    while (j < (ptr % cache_size))
                    {
                        push(q, pop(q));

                        // Rotate the bitref array
                        int temp = bitref[0];
                        for (int i = 0; i < cache_size - 1; i++)
                        {
                            bitref[i] = bitref[i + 1];
                        }
                        bitref[cache_size - 1] = temp;

                        j++;
                    }

                    // Remove front element having bitref == 0
                    pop(q);

                    // Push this element into the queue
                    push(q, w->work[i]);
                }
            }
        }
        else
        {
            // If the input for the iteration was a hit
            queue *temp = copy_queue(q);
            int counter = 0;

            while (temp->curr_size)
            {
                if (temp->front->data == w->work[i])
                {
                    bitref[counter] = 1;
                }
                counter++;
                pop(temp);
            }

            hits++;
        }
    }

    return (float)hits * 100 / w->size;
}

void test_all(workload *w, int cache_size)
{
    float fifo, random, lru, applru;
    float t_fifo, t_random, t_lru, t_applru;

    clock_t st, fin;

    st = clock();
    fifo = policy_FIFO(w, cache_size);
    fin = clock();
    t_fifo = (double)(fin - st) / CLOCKS_PER_SEC;

    st = clock();
    random = policy_RANDOM(w, cache_size);
    fin = clock();
    t_random = (double)(fin - st) / CLOCKS_PER_SEC;

    st = clock();
    lru = policy_LRU(w, cache_size);
    fin = clock();
    t_lru = (double)(fin - st) / CLOCKS_PER_SEC;

    st = clock();
    applru = policy_LRUapprox(w, cache_size);
    fin = clock();
    t_applru = (double)(fin - st) / CLOCKS_PER_SEC;

    fprintf(time_p, "%d, %f, %f, %f, %f\n",
            cache_size,
            t_fifo, t_random, t_lru, t_applru);

    fprintf(perf_p, "%d, %f, %f, %f, %f\n",
           cache_size,
           fifo, random, lru, applru);
}