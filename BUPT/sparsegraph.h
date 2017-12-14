//这是一个稀疏图，用邻接表，允许有平行边和自环边，可以自定义是不是有向图（默认是无向图）

#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cassert>
#include <cstring>
#include "minheap.h"
#include "unionfind.h"
#include "indexminheap.h"
using namespace std;

template <class Weight>//Weight是权重的数据类型，节点类型是int
class SparseGraph{
protected:

    //这是边
	struct edge{
        int a,b;
        Weight weight;
        edge(int a=0,int b=0,int w=0)
        {
            this->a=a;
            this->b=b;
            weight=w;
        }

        ~edge(){}

        int other(int x)
        {
            assert(x==a || x==b);
            if(x==a)
              return b;
            return a;
        }

        bool operator<(edge& e){
            return weight < e.weight;
        }

        bool operator<=(edge& e){
            return weight <= e.weight;
        }

        bool operator>(edge& e){
            return weight > e.weight;
        }

        bool operator>=(edge& e){
            return weight >= e.weight;
        }

        bool operator==(edge& e){
            return weight == e.weight;
        }
    };

    int v,e;//分别是节点个数个边的个数
    bool directed;//是不是有向图
    vector<vector<edge *>> g;//存储边

public:

    SparseGraph(int n,bool d=false)//构造函数，时间复杂度是O(V)
    {
        v=n;
        e=0;
        directed=d;
        for(int i=0;i<n;i++)
          g.push_back(vector<edge *>());
    }

    ~SparseGraph()//析构函数，时间复杂度是O(E)
    {
        for(int i=0;i<v;i++)
          for(int j=0;j<g[i].size();j++)
            delete g[i][j];
    }

    int V(){return v;}//返回节点个数，时间复杂度是O(1)
    int E(){return e;}//返回边的个数，时间复杂度是O(1)

    bool hasEdge(int a,int b)//返回是否有边，最差时间复杂度是O(E)
    {
        assert(a>=0 && a<v && b>=0 && b<v);
        for(int i=0;i<g[a].size();i++)
          if(g[a][i]->b==b)
            return true;
        return false;
    }

    void addEdge(int a,int b,Weight w)//添加边，时间复杂度是O(1)
    {
        assert(a>=0 && a<v && b>=0 && b<v);
        g[a].push_back(new edge(a,b,w));
        if(!directed && a!=b)
          g[b].push_back(new edge(b,a,w));
        e++;
    }

    void bfs(int start=0)//BFS，时间复杂度是O(E)
    {
        assert(start>=0 && start<v);
        cout << "BFS:  ";
        int temp;
        bool *visited=new bool[v]();
        queue<int> q;
        q.push(start);
        visited[start]=true;
        while(!q.empty())
        {
            temp=q.front();
            q.pop();
            cout << temp << ' ';
            for(int i=0;i<g[temp].size();i++)
              if(!visited[g[temp][i]->b])
              {
                  visited[g[temp][i]->b]=true;
                  q.push(g[temp][i]->b);
              }
        }
        cout << endl << endl;
        delete []visited;
    }

    void dfs(int start=0)//DFS，时间复杂度是O(E)
    {
        assert(start>=0 && start<v);
        cout << "DFS:  ";
        bool *visited=new bool[v]();
        stack<int> vert,flag;
        vert.push(start);
        flag.push(0);
        cout << start << ' ';
        visited[start]=true;
        while(!vert.empty())
        {
            if(flag.top()<g[vert.top()].size())
            {
                if(!visited[g[vert.top()][flag.top()]->b])
                {
                    cout << g[vert.top()][flag.top()]->b << ' ';
                    visited[g[vert.top()][flag.top()]->b]=true;
                    vert.push(g[vert.top()][flag.top()]->b);
                    flag.top()+=1;
                    flag.push(0);
                }
                else
                {
                    flag.top()+=1;
                }
            }
            else
            {
                flag.pop();
                vert.pop();
            }
        }
        cout << endl << endl;
        delete []visited;
    }

    void prim(int start=0)//普里姆算法，时间复杂度是O(E * log E)
    {
        assert(start>=0 && start<v);
        cout << "Prim Algorithm:  start from the Vertex:  " << start << endl;
        bool *visited=new bool[v]();
        edge temp;
        MinHeap<edge> h(2*e);
        for(int i=0;i<g[start].size();i++)
          h.insert(*(g[start][i]));
        visited[start]=true;
        while(!h.empty())
        {
            temp=h.popMin();
            if(visited[temp.a] && visited[temp.b])
              continue;
            cout << "Edge: " << temp.a << " --- " << temp.b << endl;
            int j=visited[temp.a] ? temp.b : temp.a;
            visited[j]=true;
            for(int i=0;i<g[j].size();i++)
              h.insert(*(g[j][i]));
        }
        cout << endl << endl;
        delete []visited;
    }

    void kruskal()//克鲁斯卡尔算法，时间复杂度是O(E * log E)
    {
        cout << "Kruskal Algorithm:" << endl;
        MinHeap<edge> h(e);
        UnionFind vert(v);
        int edgeCount=0;
        edge temp;
        for(int i=0;i<v;i++)
          for(int j=0;j<g[i].size();j++)
            if(g[i][j]->a < g[i][j]->b)
              h.insert(*(g[i][j]));
        while(!h.empty())
        {
            temp=h.popMin();
            if(!vert.isConnected(temp.a,temp.b))
            {
                vert.connect(temp.a,temp.b);
                cout << "Edge: " << temp.a << " --- " << temp.b << endl;
                edgeCount++;
            }
        }
        cout << v-edgeCount << "   Connected Component(s) in total" << endl << endl;
    }

    void dijkstra(int s=0)//Dijkstra算法，时间复杂度是O(E * log V)
    {
        assert(s>=0 && s<v);
        cout << endl << "Dijkstra Algorithm:  start from the Vertex: " << s << endl << endl;
        Weight *disk=new Weight[v]();
        int temp,temp2,*from=new int[v];
        bool *mark=new bool[v]();
        memset(from,-1,v*sizeof(int));
        IndexMinHeap<Weight> imh(v);
        imh.insert(s,disk[s]);
        while(!imh.empty())
        {
            temp=imh.popMinIndex();
            mark[temp]=true;
            for(int i=0;i<g[temp].size();i++)
            {
                temp2=g[temp][i]->b;
                if(!mark[temp2])
                  if(-1==from[temp2] || disk[temp]+g[temp][i]->weight<disk[temp2])
                  {
                      disk[temp2]=disk[temp]+g[temp][i]->weight;
                      from[temp2]=temp;
                      if(imh.contain(temp2))
                        imh.change(temp2,disk[temp2]);
                      else
                        imh.insert(temp2,disk[temp2]);
                  }
            }
        }
        for(int i=0;i<v;i++)
        {
            if(-1==from[i])
              continue;
            cout << "to Vertex: " << i << "   disk:  " << disk[i] << "   Path:  " << i;
            for(int j=from[i];-1 != j;j=from[j])
              cout << " <-- " << j;
            cout << endl << endl;
        }
        delete []disk;
        delete []from;
        delete []mark;
    }
};

#endif
