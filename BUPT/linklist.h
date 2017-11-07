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
		node *next,*front;
	};
	int length;
	node *first;
public:
	//构造空链表,时间复杂度是O(1)
	LinkList()
	{
		length=0;
		first=new node;
		first->next=first->front=first;
	}

	//头插法构造链表插入之后顺序颠倒,时间复杂度是O(n)
	LinkList(T *arr,int n)
	{
		first=new node;
		length=0;
		first->next=first->front=first;
		for(int i=0;i<n;i++)
		{
			insert(first,arr[i]);
		}
		length=n;
	}

	//尾插法构造链表插入之后顺序不变,时间复杂度是O(n)
	LinkList(T *arr,int n,int flag)
	{
		first=new node;
		length=0;
		first->next=first->front=first;
		for(int i=0;i<n;i++)
		{
			pushBack(arr[i]);
		}
	}

	//复制构造函数,时间复杂度是O(n)
	LinkList(LinkList<T> &o)
	{
		length=0;
		first=new node;
		first->next=first->front=first;
		for(int i=1;i<=o.length;i++)
		  pushBack(((node*)o.get(i))->a);
	}

	//传入指针，在该指针所指的节点后面插入,时间复杂度是O(1)
	void insert(void *i,T b)
	{
		node *p=new node;
		p->a=b;
		p->front=(node*)i;
		//by donghao
		p->next=((node*)i)->next;
		((node*)i)->next=p;
		p->next->front=p;
		length++;
	}

	//在指定的编号插入,时间复杂度是O(n)
	bool insert(int i,T b)
	{
		if(0==i)
		{
			throw "this is head";
			return false;
		}
		if(i<0||i>length)
		{
			throw "overflow";
			return false;
		}
		node *index=first;
		while(i--)
		  index=index->next;
		node *p=new node;
		p->a=b;
		p->next=index;
		p->front=index->front;
		p->next->front=p->front->next=p;
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
		p->next=first;
		p->front=first->front;
		first->front=first->front->next=p;
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
		((node*)i)->next->front=((node*)i)->front;
		((node*)i)->front->next=((node*)i)->next;
		length--;
		return true;
	}

	//根据序号删除,时间复杂度是O(n)
	bool deleteNode(int a)
	{
		if(a<=0 || a>length)
		{
			throw "overflow or you are trying to delete the head";
			return false;
		}
		node *index=first;
		while(a--)
		  index=index->next;
		index->next->front=index->front;
		index->front->next=index->next;
		delete index;
		length--;
		return true;
	}

	//传入序号，查找并返回指针,时间复杂度是O(n)
	T *get(int aa)
	{
		if(aa>length || aa<=0)
		{
			throw "overflow";
			return NULL;
		}
		node *index=first;
		//do not copy
		while(aa--)
		  index=index->next;
		return (T*)index;
	}

	//方括号重载，时间复杂度是O(n)
	T &operator[](int aa)
	{
		if(aa>length || aa<=0)
		{
			throw "overflow";
			return first->a;
		}
		node *index=first;
		//do not copy
		while(aa--)
		  index=index->next;
		return index->a;
	}

	//定位，返回序号，时间复杂度是O(n)
	int locate(T &aa)
	{
		int r=1;
		node *index=first->next;
		while(index!=first)
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
		node *index=first;
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
		node *index=first;
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
		node *index=first;
		for(int i=0;i<=length;i++)
		{
			node *temp=index->next;
			index->next=index->front;
			index->front=temp;
			index=index->front;
		}
	}

	//排序函数，排序之后为升序,方法为选择排序,时间复杂度是O(n^2)
	void listSort()
	{
		node *index=first;
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
		first=new node;
		length=0;
		first->next=first->front=first;
		for(int i=0;i<n;i++)
		{
			pushBack(arr[i]);
		}
		listSort();
	}

	//合并两个顺序链表，合并之后仍为顺序链表且无重复节点,时间复杂度是O(n)
	void merge(LinkList<T> &o)
	{
		node *index1=first->next,*index2=o.first->next;
		while(index1!=first && index2!=o.first)
		{
			if(index2->a < index1->a)
			{
				insert(index1->front,index2->a);
				index1=index1->front;
			}
			if(index2->a == index1->a)
			  index2=index2->next;
			if(index1->next == first)
			  break;
			if(index1->a == index1->next->a)
			  deleteNode(index1->next);
			else
			  index1=index1->next;
		}
		if(index1->next == first)
		{
			while(index2 != o.first)
			{
				if(index2->a < index1->a)
				{
					insert(index1->front,index2->a);
					index1=index1->front;
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
};

#endif
