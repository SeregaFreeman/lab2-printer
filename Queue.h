#ifndef QUEUE_H
#define QUEUE_H

#include "Heap.h"
#include "Task.h"

class Queue
{
public:
	Queue();
	~Queue();

	void enqueue(Task *task);
	Task *dequeue();
	int getCount() const;
private:
	Heap *heap;
};

#endif
