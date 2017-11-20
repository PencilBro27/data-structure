/*
 * 该文件是作业2.1对应的头文件，它可以供之后的作业使用
 */

#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
using namespace std;

template <class T>
class LinkList
{
protected:
    struct node{
        T a;
        node *next,*prior;
    };
    int length;
    node *front;
public:
    //构造空链表,时间复杂度是O(1)
    LinkList()
    {
        length=0;
        front=new node;
        front->next=front->prior=front;
    }

    //头插法构造链表插入之后顺序颠倒,时间复杂度是O(n)
    LinkList(T *arr,int n)
    {
        front=new node;
        length=0;
        front->next=front->prior=front;
        for(int i=0;i<n;i++)
        {
            insert(front,arr[i]);
        }
        length=n;
    }

    //尾插法构造链表插入之后顺序不变,时间复杂度是O(n)
    LinkList(T *arr,int n,int flag)
    {
        front=new node;
        length=0;
        front->next=front->prior=front;
        for(int i=0;i<n;i++)
        {
            pushBack(arr[i]);
        }
    }

    //复制构造函数,时间复杂度是O(n)
    LinkList(LinkList<T> &o)
    {
        length=0;
        front=new node;
        front->next=front->prior=front;
        typename LinkList<int>::iterator iter(o);
        for(;!iter.end();iter.next())
          pushBack(*iter);
    }

    //传入指针，在该指针所指的节点后面插入,时间复杂度是O(1)
    void insert(void *i,T b)
    {
        node *p=new node;
        p->a=b;
        p->prior=(node*)i;
        //by donghao
        p->next=((node*)i)->next;
        ((node*)i)->next=p;
        p->next->prior=p;
        length++;
    }

    //在指定的编号插入,时间复杂度是O(n)
    bool insert(int i,T b)
    {
        i++;
        if(i<=0||i>length)
        {
            throw "overflow";
            return false;
        }
        node *index=front;
        while(i--)
          index=index->next;
        node *p=new node;
        p->a=b;
        p->next=index;
        p->prior=index->prior;
        p->next->prior=p->prior->next=p;
        length++;
        return true;
    }

    //在末尾插入,时间复杂度是O(1)
    bool pushBack(T b)
    {
        node *p=new node;
        if(!p)
          return false;
        p->a=b;
        p->next=front;
        p->prior=front->prior;
        front->prior=front->prior->next=p;
        length++;
        return true;
    }

    //根据指针删除,时间复杂度是O(1)
    bool deleteNode(void *i)
    {
        if(0==length)
        {
            throw "the linklist is empty";
            return false;
        }
        ((node*)i)->next->prior=((node*)i)->prior;
        ((node*)i)->prior->next=((node*)i)->next;
        length--;
        return true;
    }

    //根据序号删除,时间复杂度是O(n)
    bool deleteNode(int a)
    {
        a++;
        if(a<=0 || a>length)
        {
            throw "overflow";
            return false;
        }
        node *index=front;
        while(a--)
          index=index->next;
        index->next->prior=index->prior;
        index->prior->next=index->next;
        delete index;
        length--;
        return true;
    }

    //传入序号，查找并返回指针,时间复杂度是O(n)
    T *get(int aa)
    {
        aa++;
        if(aa>length || aa<=0)
        {
            throw "overflow";
            return NULL;
        }
        node *index=front;
        //do not copy
        while(aa--)
          index=index->next;
        return (T*)index;
    }

    //方括号重载，时间复杂度是O(n)
    T &operator[](int aa)
    {
        aa++;
        if(aa>length || aa<=0)
        {
            throw "overflow";
            return front->a;
        }
        node *index=front;
        //do not copy
        while(aa--)
          index=index->next;
        return index->a;
    }

    //定位，返回序号，时间复杂度是O(n)
    int locate(T &aa)
    {
        int r=0;
        node *index=front->next;
        while(index!=front)
        {
            if(aa == index->a)
              return r;
            index=index->next;
            r++;
        }
        throw "do not find";
        return NULL;
    }

    //获取链表长度,时间复杂度是O(1)
    int getLength()
    {
        return length;
    }

    //打印链表数据,时间复杂度是O(n)
    void printList()
    {
        node *index=front;
        for(int i=0;i<length;i++)
        {
            index=index->next;
            cout << index->a << endl;
        }
        cout << endl;
    }

    //析构函数,时间复杂度是O(n)
    ~LinkList()
    {
        length++;
        node *index=front;
        node *p=index;
        while(length--)
        {
            index=index->next;
            delete p;
            p=index;
        }
    }

    //链表倒置函数,时间复杂度是O(n)
    void invert()
    {
        node *index=front;
        for(int i=0;i<=length;i++)
        {
            node *temp=index->next;
            index->next=index->prior;
            index->prior=temp;
            index=index->prior;
        }
    }

    //排序函数，排序之后为升序,方法为选择排序,时间复杂度是O(n^2)
    void listSort()
    {
        node *index=front;
        node *index2;
        T *it;
        for(int i=1;i<length;i++)
        {
            index=index->next;
            it=&index->a;
            index2=index;
            for(int j=1;i+j<=length;j++)
            {
                index2=index2->next;
                if(index2->a<*it)
                  it=&index2->a;
            }
            T temp=index->a;
            index->a=*it;
            *it=temp;
        }
    }

    //一个新的构造函数，传入一个数组，自动调用排序函数排序,时间复杂度是O(n^2)
    LinkList(T *arr,int n,double sort)
    {
        front=new node;
        length=0;
        front->next=front->prior=front;
        for(int i=0;i<n;i++)
        {
            pushBack(arr[i]);
        }
        listSort();
    }

    //合并两个顺序链表，合并之后仍为顺序链表且无重复节点,时间复杂度是O(n)
    void merge(LinkList<T> &o)
    {
        node *index1=front->next,*index2=o.front->next;
        while(index1!=front && index2!=o.front)
        {
            if(index2->a < index1->a)
            {
                insert(index1->prior,index2->a);
                index1=index1->prior;
            }
            if(index2->a == index1->a)
              index2=index2->next;
            if(index1->next == front)
              break;
            if(index1->a == index1->next->a)
              deleteNode(index1->next);
            else
              index1=index1->next;
        }
        if(index1->next == front)
        {
            while(index2 != o.front)
            {
                if(index2->a < index1->a)
                {
                    insert(index1->prior,index2->a);
                    index1=index1->prior;
                }
                if(index2->a == index1->a)
                  index2=index2->next;
                if(index2->a > index1->a)
                {
                    insert(index1,index2->a);
                    index1=index1->next;
                    index2=index2->next;
                }
            }
        }
    }

    //迭代器
    class iterator{
    protected:
        LinkList<T> &L;
        union{
            node *n;
            T *p;
        };
    public:
        iterator(LinkList<T> &ll,int index=0):L(ll)
        {
            p=L.get(index);
        }

        iterator(LinkList<T>::iterator &o):L(o.L)
        {
            n=o.n;
        }

        bool begin()
        {
            if(L.length)
              return bool(n=L.front);
            return false;
        }

        LinkList<T>::iterator& operator++()
        {
            n=n->next;
            return *this;
        }

        LinkList<T>::iterator operator++(int)
        {
            LinkList<T>::iterator old(*this);
            n=n->next;
            return old;
        }

        LinkList<T>::iterator& operator--()
        {
            n=n->prior;
            return *this;
        }

        LinkList<T>::iterator operator--(int)
        {
            LinkList<T>::iterator old(*this);
            n=n->prior;
            return old;
        }

        LinkList<T>::iterator& prior()
        {
            n=n->prior;
            return *this;
        }

        LinkList<T>::iterator& next()
        {
            n=n->next;
            return *this;
        }

        bool end()
        {
            return L.front==n;
        }

        T& operator*()
        {
            return *p;
        }
    };
};

#endif
