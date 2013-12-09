#include <iostream>
#include "Heap.h"

using namespace std;

//---------------------------------------
// Конструктор
//---------------------------------------
Heap::Heap(int size)
{
    // Создаем кучу заданного размера
    m_Elements = new HeapItem[size];
    m_iNumElements = 0;
    m_iHeapLength = size;
}

//---------------------------------------
// Деструктор
//---------------------------------------
Heap::~Heap()
{
    delete[] m_Elements;
}

//---------------------------------------
// Перестройка после удаления
//---------------------------------------
void Heap::ReheapDown(int root, int bottom)
{
    int maxChild;
    int rightChild;
    int leftChild;
    HeapItem temp;

    leftChild = root * 2 + 1;          // левый сын
    rightChild = root * 2 + 2;          // правый сын

    // Проверяем рекурсивные вызовы.Если левый сын меньше или равен меньшему, то мы еще не закончили.
    if(leftChild <= bottom)
    {
        if(leftChild == bottom)          // если у этого нет правого корня
        {
            maxChild = leftChild;     //     то максимальное в левом
        }
        else
        {
            // получаем самое меньшее в дереве
            if(m_Elements[leftChild].getKey() <= m_Elements[rightChild].getKey())
                maxChild = rightChild;
            else
                maxChild = leftChild;
        }
        if(m_Elements[root].getKey() < m_Elements[maxChild].getKey())
        {
            // меняем два элемента
            temp = m_Elements[root];
            m_Elements[root] = m_Elements[maxChild];
            m_Elements[maxChild] = temp;
            // рекурсивно вызываем, пока не закончим перестройку
            ReheapDown(maxChild, bottom);
        }
    }
}

//---------------------------------------
// Перестройка после вставки
//---------------------------------------
void Heap::ReheapUp(int root, int bottom)
{
    int parent;
    HeapItem temp;

    // Проверяем рекурсивные вызовы.  Если меньший больше чем корень, мы еще не закончили
    if(bottom > root)
    {
        parent = (bottom -1) / 2;
        if(m_Elements[parent].getKey() < m_Elements[bottom].getKey())
        {
            // меняем два элемента
            temp = m_Elements[parent];
            m_Elements[parent] = m_Elements[bottom];
            m_Elements[bottom] = temp;
            // рекурсивно вызываем, пока не перестроим
            ReheapUp(root, parent);
        }
    }
}

//---------------------------------------
// добавление элемента в кучу
//---------------------------------------
bool Heap::Enqueue(HeapItem *item)
{
    if(m_iNumElements < m_iHeapLength)
    {
        m_Elements[m_iNumElements] = *item; // копируем в массив
        ReheapUp(0, m_iNumElements);
        m_iNumElements++;
        return true;
    }
    return false;
}

//---------------------------------------
// Добавление
//---------------------------------------
bool Heap::Enqueue(int key, Task *data)
{
    bool retVal;
    HeapItem *temp = new HeapItem(key, data);
    retVal = Enqueue(temp);
    delete temp;  // удаляем
    return retVal;
}

//---------------------------------------
// Get item at the root
//---------------------------------------
HeapItem *Heap::Dequeue()
{
    HeapItem *temp = new HeapItem(m_Elements[0].getKey(), m_Elements[0].getData());
    m_iNumElements--;
    // Copy last item into root
    m_Elements[0] = m_Elements[m_iNumElements];
    // Reheap the tree
    ReheapDown(0, m_iNumElements - 1);
    return temp;
}

//---------------------------------------
// Возвращаем количество элементов
//---------------------------------------
int Heap::getNumElements()
{
    return m_iNumElements;
}
