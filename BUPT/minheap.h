#ifndef MINHEAP_H
#define MINHEAP_H

#include <algorithm>
#include <cassert>
using namespace std;

template<class T>
class MinHeap{
protected:
    T *data;
    int count,capacity;

    void shiftUp(int k)
    {
        while(k>1 && data[k/2]>data[k])
        {
            T temp=data[k/2];
            data[k/2]=data[k];
            data[k]=temp;
            k/=2;
        }
    }

    void shiftDown(int k)
    {
        while(2*k <= count)
        {
            int j=2*k;
            if(j+1<=count && data[j+1]<data[j]) j++;
            if(data[k]<=data[j]) break;
            T temp=data[j];
            data[j]=data[k];
            data[k]=temp;
            k=j;
        }
    }

public:
    MinHeap(int capacity)
    {
        data=new T[capacity+1];
        count=0;
        this->capacity=capacity;
    }

    ~MinHeap()
    {
        delete[] data;
    }

    int size(){return count;}
    bool empty(){return 0==count;}

    void insert(T a)
    {
        assert(count+1<=capacity);
        data[count+1]=a;
        shiftUp(count+1);
        count++;
    }

    T popMin()
    {
        assert(count>0);
        T r=data[1];
        data[1]=data[count];
        count--;
        shiftDown(1);
        return r;
    }

    T getMin()
    {
        assert(count>0);
        return data[1];
    }
};

#endif
