//该文件是并查集，有路径压缩算法

#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <cassert>
using namespace std;

class UnionFind{
protected:
    // rank[i]表示以i为根的集合所表示的树的层数
    // 在后续的代码中, 我们并不会维护rank的语意, 也就是rank的值在路径压缩的过程中, 有可能不在是树的层数值
    // 这也是我们的rank不叫height或者depth的原因, 他只是作为比较的一个标准
    int *rank;
    int *index;
    int size;

    inline int find(int p)
    {
        int pRoot=index[p],temp;
        for(;pRoot!=index[pRoot];pRoot=index[pRoot]);
        for(;pRoot!=index[p];)
        {
            temp=p;
            p=index[p];
            index[temp]=pRoot;
        }
        return pRoot;
    }
public:
    //构造函数，时间复杂度是O(n)
    UnionFind(int n=128)
    {
        assert(n>0);
        index=new int[n];
        rank=new int[n]();
        for(int i=0;i<n;i++)
          index[i]=i;
        size=n;
    }

    //析造函数，时间复杂度是O(n)
    ~UnionFind()
    {
        delete []index;
        delete []rank;
    }

    //查找函数，时间复杂度是O(h)，h是深度
    bool isConnected(int p,int q)
    {
        assert(p>=0 && p<size && q>=0 && q<size);
        return find(p)==find(q);
    }

    //连接函数，时间复杂度是O(h)，h是深度
    void connect(int p,int q)
    {
        assert(p>=0 && p<size && q>=0 &&q<size);
        int pRoot=find(p),qRoot=find(q);
        if(pRoot==qRoot)
          return ;
        if(rank[pRoot] < rank[qRoot])
          index[pRoot]=qRoot;
        else if(rank[pRoot] > rank[qRoot])
          index[qRoot]=pRoot;
        else
        {
            index[pRoot]=qRoot;
            rank[qRoot]++;
        }
    }
};

#endif
