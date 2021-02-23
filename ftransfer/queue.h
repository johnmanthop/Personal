#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#define QSIZE 32

struct queue {
	void *array;
	unsigned max, size, offset;
};//By convention pass all data as pointers casted to void*

struct queue init_Q(unsigned offset);

void* Q_add_end    (struct queue *q, void* inp);
void* Q_get_start  (struct queue *q);
void* Q_pop_start  (struct queue *q);

#endif