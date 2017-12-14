//这是一个最小索引堆

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

    inline void shiftUp(int index)//时间复杂度是O(log n)
    {
        while(index>1 && data[indexes[index/2]]>data[indexes[index]])
        {
            swap(indexes[index/2],indexes[index]);
            reverse[indexes[index/2]]=index/2;
            reverse[indexes[index]]=index;
            index/=2;
        }
    }

    inline void shiftDown(int index)//时间复杂度是O(log n)
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
    IndexMinHeap(int capacity)//构造函数，时间复杂度是O(1)
    {
        data=new T[capacity+1]();
        indexes=new int[capacity+2]();
        reverse=new int[capacity+1]();
        count=0;
        capa=capacity;
    }

    ~IndexMinHeap()//析构函数，时间复杂度是O(1)
    {
        delete []data;
        delete []indexes;
        delete []reverse;
    }

    int size(){return count;}//返回元素个数，时间复杂度是O(1)
    int capacity(){return capa;}//返回总容量，时间复杂度是O(1)
    bool empty(){return 0==count;}//返回是否为空，时间复杂度是O(1)

    void insert(int index,T t)//插入元素，时间复杂度是O(log n)
    {
        assert(count+1<=capa && index+1>=1 && index+1<=capa && !contain(index));
        index++;
        count++;
        data[index]=t;
        indexes[count]=index;
        reverse[index]=count;
        shiftUp(count);
    }

    T popMin()//返回并删除最小元素，时间复杂度是O(log n)
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

    int popMinIndex()//删除最小元素并返回索引，时间复杂度是O(log n)
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

    T getMin()//返回最小元素，时间复杂度是O(1)
    {
        assert(count>0);
        return data[indexes[1]];
    }

    int getMinIndex()//返回最小元素的索引，时间复杂度是O(1)
    {
        assert(count>0);
        return indexes[1]-1;
    }

    bool contain(int index)//检测索引是否存在，时间复杂度是O(1)
    {
        return reverse[index+1]!=0;
    }

    T getData(int index)//返回索引对应的值，时间复杂度是O(1)
    {
        assert(contain(index));
        return data[index+1];
    }

    void change(int index,T newData)//改变索引对应元素的值，时间复杂度是O(log n)
    {
        assert(contain(index));
        index++;
        data[index]=newData;
        shiftUp(reverse[index]);
        shiftDown(reverse[index]);
    }
};

#endif
