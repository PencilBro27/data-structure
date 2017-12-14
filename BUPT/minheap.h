//这是一个最小堆

#ifndef MINHEAP_H
#define MINHEAP_H

#include <algorithm>
#include <cassert>
using namespace std;

template<class T>
class MinHeap{
protected:
    T *data;
    int count,capacity;//分别是现有元素个数和容量

    inline void shiftUp(int k)//时间复杂度是O(log n)
    {
        while(k>1 && data[k/2]>data[k])
        {
            swap(data[k/2],data[k]);
            k/=2;
        }
    }

    inline void shiftDown(int k)//时间复杂度是O(log n)
    {
        while(2*k <= count)
        {
            int j=2*k;
            if(j+1<=count && data[j+1]<data[j]) j++;
            if(data[k]<=data[j]) break;
            swap(data[j],data[k]);
            k=j;
        }
    }

public:
    MinHeap(int capacity)//构造函数，时间复杂度是O(1)
    {
        data=new T[capacity+2];
        count=0;
        this->capacity=capacity;
    }

    ~MinHeap()//析构函数，时间复杂度是O(1)
    {
        delete[] data;
    }

    int size(){return count;}//返回现有元素个数，时间复杂度是O(1)
    bool empty(){return 0==count;}//返回是否为空，时间复杂度是O(1)

    void insert(T a)//插入函数，时间复杂度是O(log n)
    {
        assert(count+1<=capacity);
        data[count+1]=a;
        shiftUp(count+1);
        count++;
    }

    T popMin()//返回并删除最小元素，时间复杂度是O(log n)
    {
        assert(count>0);
        T r=data[1];
        data[1]=data[count];
        count--;
        shiftDown(1);
        return r;
    }

    T getMin()//返回最小元素，时间复杂度是O(1)
    {
        assert(count>0);
        return data[1];
    }
};

#endif
