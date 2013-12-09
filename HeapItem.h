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
    int getKey();                         // ���������� ���������
    void setKey(int key);               // ������������� �������� ����������
    Task *getData();                    // ���������� ������
    void setData(Task *data);          // ������������� ������
};

#endif
