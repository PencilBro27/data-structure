#ifndef INDEXMINHEAP_H
#define INDEXMINHEAP_H

#include <cassert>
#include <algorithm>
using namespace std;

template<class T>
class IndexMinHeap{
protected:
    T *data;
    int *indexes;
    int *reverse;
    int count;
    int capa;

    inline void shiftUp(int index)
    {
        while(index>1 && data[indexes[index/2]]>data[indexes[index]])
        {
            swap(indexes[index/2],indexes[index]);
            reverse[indexes[index/2]]=index/2;
            reverse[indexes[index]]=index;
            index/=2;
        }
    }

    inline void shiftDown(int index)
    {
        int j;
        while(2*index<=count)
        {
            j=2*index;
            if(j+1<=count && data[indexes[index]]>data[indexes[j+1]])
              j++;
            if(data[indexes[index]]<=data[indexes[index]])
              break;
            swap(indexes[index],indexes[j]);
            reverse[indexes[index]]=index;
            reverse[indexes[j]]=j;
            index=j;
        }
    }

public:
    IndexMinHeap(int capacity)
    {
        data=new T[capacity+1]();
        indexes=new int[capacity+2]();
        reverse=new int[capacity+1]();
        count=0;
        capa=capacity;
    }

    ~IndexMinHeap()
    {
        delete []data;
        delete []indexes;
        delete []reverse;
    }

    int size(){return count;}
    int capacity(){return capa;}
    bool empty(){return 0==count;}

    void insert(int index,T t)
    {
        assert(count+1<=capa && index+1>=1 && index+1<=capa && !contain(index));
        index++;
        count++;
        data[index]=t;
        indexes[count]=index;
        reverse[index]=count;
        shiftUp(count);
    }

    T popMin()
    {
        assert(count>0);
        T r=data[indexes[1]];
        swap(indexes[1],indexes[count]);
        reverse[indexes[count]]=0;
        reverse[indexes[1]]=1;
        count--;
        shiftDown(1);
        return r;
    }

    int popMinIndex()
    {
        assert(count>0);
        int r=indexes[1]-1;
        swap(indexes[1],indexes[count]);
        reverse[indexes[count]]=0;
        reverse[indexes[1]]=1;
        count--;
        shiftDown(1);
        return r;
    }

    T getMin()
    {
        assert(count>0);
        return data[indexes[1]];
    }

    int getMinIndex()
    {
        assert(count>0);
        return indexes[1]-1;
    }

    bool contain(int index)
    {
        return reverse[index+1]!=0;
    }

    T getData(int index)
    {
        assert(contain(index));
        return data[index+1];
    }

    void change(int index,T newData)
    {
        assert(contain(index));
        index++;
        data[index]=newData;
        shiftUp(reverse[index]);
        shiftDown(reverse[index]);
    }
};

#endif
