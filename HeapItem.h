#ifndef HEAPITEM_H
#define HEAPITEM_H

#include "Task.h"

class HeapItem
{
private:
    int m_iKey;
    Task *m_dData;

public:
    HeapItem();
    HeapItem(int key, Task *data);
    ~HeapItem();
    int getKey();                         // возвращает приоритет
    void setKey(int key);               // устанавливает значение приоритета
    Task *getData();                    // возвращает данные
    void setData(Task *data);          // устанавливает данные
};

#endif
