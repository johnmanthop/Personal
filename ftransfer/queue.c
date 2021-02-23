#include "queue.h"
#include <stdlib.h>
#include <string.h>

//generic queue implementation
struct queue init_Q(unsigned offset)
{
	struct queue q;
	//malloc 32 * sizeof data (32 slots)
	q.array  = malloc(QSIZE * offset);
	for (int i = 0; i < QSIZE; ++i) {
		*((char*)q.array + i) = (char)0;
	}
	
	q.max    = QSIZE;
	q.size   = 0;
	q.offset = offset;

	return q;
}

void *Q_add_end(struct queue *q, void* input)
{
	//if the queue is full return max
	if (q->size >= q->max - 1) return NULL;
	//otherwise copy the data to the end of the queue
	memcpy((char*)q->array + (q->size++)*q->offset, input, q->offset);
	return (void*)1;
}

void *Q_get_start(struct queue *q)
{
	//return queue top
	return q->array;
}

void *Q_pop_start(struct queue *q)
{
	//malloc a slot to save the popped data (cannot be done with static variables)
	void *temp = malloc(q->offset);
	memcpy(temp, q->array, q->offset); //copy the to be popped data
	
	if (q->size > 1) q->size--;
	//slide everything to the left
	for (int i = 1; i < q->max; ++i) {
		memcpy((char*)q->array + (i - 1)*q->offset, (char*)q->array + i*q->offset, q->offset);
	} 
	
	return temp;
}