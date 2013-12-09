#include "Queue.h"

Queue::Queue()
{
	heap = new Heap(10);
}

Queue::~Queue()
{
	delete heap;
	heap = 0;
}

void Queue::enqueue(Task *task)
{
	if (task == 0)
		return;

	heap->Enqueue(task->priority, task);
}

Task *Queue::dequeue()
{
	return getCount() == 0 ? (Task *)0 : heap->Dequeue()->getData();
}

int Queue::getCount() const
{
	return heap->getNumElements();
}

