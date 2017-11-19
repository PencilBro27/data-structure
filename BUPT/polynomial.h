/*
 * 这是作业2.3对应的头文件
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "linklist.h"
using namespace std;

//为方便操作，对结构体进行了运算符重载
struct polynomialNode{
    float coef;
    int expn;
    bool operator<(polynomialNode &o)
    {
        return expn>o.expn;
    }
    bool operator>(polynomialNode &o)
    {
        return expn<o.expn;
    }
    bool operator==(polynomialNode &o)
    {
        return expn==o.expn;
    }
    polynomialNode operator+(polynomialNode &o)
    {
        polynomialNode r;
        r.expn=expn;
        r.coef=coef+o.coef;
        return r;
    }
    polynomialNode operator-(polynomialNode &o)
    {
        polynomialNode r;
        r.expn=expn;
        r.coef=coef-o.coef;
        return r;
    }
    polynomialNode &operator=(polynomialNode &o)
    {
        coef=o.coef;
        expn=o.expn;
        return *this;
    }
    void operator+=(polynomialNode &o)
    {
        coef+=o.coef;
    }
    void operator-=(polynomialNode &o)
    {
        coef-=o.coef;
    }
};

class polynomial:protected LinkList<polynomialNode>{
protected:

    //删除重复节点的函数,自通调用排序函数,时间复杂度是O(n^2)
    void deleteSame()
    {
        listSort();
        node *index=front;
        while(index->next != front)
        {
            index=index->next;
            if(index->a == index->next->a && index->next != front)
            {
                index->a += index->next->a;
                deleteNode(index->next);
                if(index->a.coef < 1e-6)
                  deleteNode(index);
            }
        }
    }
public:

    //空构造函数,时间复杂度是O(1)
    polynomial():LinkList()
    {}

    //有输入的构造函数,时间复杂度是O(n)
    polynomial(polynomialNode *arr,int n):LinkList(arr,n)
    {
        deleteSame();
    }

    //输入两个数组，一个代表次数，另一个代表系数，时间复杂度是O(n)
    polynomial(float *c,int *e,int n):LinkList()
    {
        while(n--)
          insert(c[n],e[n]);
    }

    //答应在显示屏上的函数,时间复杂度是O(n)
    void printList()
    {
        node *index=front;
        for(int i=0;i<length;i++)
        {
            if(i)
              cout << '+';
            index=index->next;
            cout << index->a.coef << "x^" << index->a.expn;
        }
        cout << endl;
    }

    //合并函数，自动调用删除重复的节点的函数,时间复杂度是O(n^2)
    void merge(polynomial &o)
    {
        node *index=o.front;
        for(int i=0;i<o.length;i++)
        {
            index=index->next;
            pushBack(index->a);
        }
        deleteSame();
    }

    //删除一个指定次数的节点,时间复杂度是O(n)
    bool deletePolynomialNode(int n)
    {
        if(n<0)
        {
            throw "n must bigger than 0";
            return false;
        }
        node *index=front->next;
        while(index!=front)
          if(index->a.expn==n)
          {
              deleteNode(index);
              return true;
          }
        throw "do not find";
        return false;
    }

    //插入一个结点，并覆盖原有的相同次数的节点,时间复杂度是O(n)
    bool insert(float c,int e)
    {
        if(e<0)
        {
            throw "e must bigger than 0";
            return false;
        }
        node *index2=front->next;
        while(index2 != front)
        {
            if(index2->a.expn == e)
              LinkList::deleteNode(index2);
            index2=index2->next;
        }
        if(0 == c)
          return true;
        polynomialNode n;
        n.coef=c;
        n.expn=e;
        if(e>front->next->a.expn)
        {
            LinkList::insert(front,n);
            return true;
        }
        if(e<front->prior->a.expn)
        {
            LinkList::insert(front->prior,n);
            return true;
        }
        if(e<front->prior->prior->a.expn)
        {
            LinkList::insert(front->prior->prior,n);
            return true;
        }
        node *index=front->next;
        while(index->next != front)
        {
            if(e<index->a.expn && e>index->next->a.expn)
            {
                LinkList::insert(index,n);
                return true;
            }
            index=index->next;
        }
    }

    //计算函数,输入x,时间复杂度是O(n)
    double calculate(double x)
    {
        double r=0.0;
        double *arr=new double[front->next->a.expn + 1];
        arr[0]=1.0;
        for(int i=0;i<front->next->a.expn;i++)
          arr[i+1]=arr[i]*x;
        node *index=front;
        for(int i=0;i<length;i++)
        {
            index=index->next;
            r+=index->a.coef*arr[index->a.expn];
        }
        return r;
    }

    //求导，覆盖原有的多项式，时间复杂度是O(n)
    void differential()
    {
        node *index=front->next;
        while(index != front)
        {
            index->a.coef*=index->a.expn--;
            index=index->next;
        }
        if(-1 == index->prior->a.expn)
          deleteNode(index->prior);
    }
};

#endif
