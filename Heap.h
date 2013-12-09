#ifndef HEAP_H
#define HEAP_H
#include "HeapItem.h"

class Heap
{
private:
    HeapItem *m_Elements;
    int m_iNumElements;
    int m_iHeapLength;

public:
    Heap(int size = 10);
    ~Heap();
    void ReheapDown(int root, int bottom);
    void ReheapUp(int root, int bottom);
    bool Enqueue(HeapItem *item);
    bool Enqueue(int key, Task *data);
    HeapItem *Dequeue();
    int getNumElements();
};

#endif
