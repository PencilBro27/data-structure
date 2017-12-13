#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cassert>
#include <cstring>
#include "minheap.h"
using namespace std;

template <class Weight>
class SparseGraph{
protected:

    struct edge{
        int a,b;
        Weight weight;
        edge(int a,int b,Weight w)
        {
            this->a=a;
            this->b=b;
            weight=w;
        }

        edge(){}

        edge(edge &o)
        {
            a=o.a;
            b=o.b;
            weight=o.weight;
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

    int v,e;
    bool directed;
    vector<vector<edge *>> g;

public:

    SparseGraph(int n,bool d=false)
    {
        v=n;
        e=0;
        directed=d;
        for(int i=0;i<n;i++)
          g.push_back(vector<edge *>());
    }

    ~SparseGraph()
    {
        for(int i=0;i<v;i++)
          for(int j=0;j<g[i].size();j++)
            delete g[i][j];
    }

    int V(){return v;}
    int E(){return e;}

    bool hasEdge(int a,int b)
    {
        assert(a>=0 && a<v && b>=0 && b<v);
        for(int i=0;i<g[a].size();i++)
          if(g[a][i]->b==b)
            return true;
        return false;
    }

    void addEdge(int a,int b,Weight w)
    {
        assert(a>=0 && a<v && b>=0 && b<v);
        g[a].push_back(new edge(a,b,w));
        if(!directed && a!=b)
          g[b].push_back(new edge(b,a,w));
        e++;
    }

    void bfs(int start=0)
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

    void dfs(int start=0)
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

    void prim(int start=0)
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

    void kruskal()
    {
        cout << "Kruskal Algorithm:" << endl;
        MinHeap<edge> h(e);
        vector<vector<int>> vertex;
        int edgeCount=0;
        edge temp;
        int index1,index2;
        for(int i=0;i<v;i++)
          for(int j=0;j<g[i].size();j++)
            if(g[i][j]->a < g[i][j]->b)
              h.insert(*(g[i][j]));
        while(!h.empty())
        {
            index1=index2=-1;
            temp=h.popMin();
            for(int i=0;i<vertex.size();i++)
              for(int j=0;j<vertex[i].size();j++)
              {
                  if(temp.a==vertex[i][j])
                    index1=i;
                  if(temp.b==vertex[i][j])
                    index2=i;
              }
            if(-2==index1+index2)
            {
                cout << "Edge: " << temp.a << " --- " << temp.b << endl;
                vertex.push_back(vector<int>());
                vertex[vertex.size()-1].push_back(temp.a);
                vertex[vertex.size()-1].push_back(temp.b);
                edgeCount++;
            }
            else if(index1==index2)
            {
                continue;
            }
            else if(-1==index1)
            {
                vertex[index2].push_back(temp.a);
                cout << "Edge: " << temp.a << " --- " << temp.b << endl;
                edgeCount++;
            }
            else if(-1==index2)
            {
                vertex[index1].push_back(temp.b);
                cout << "Edge: " << temp.a << " --- " << temp.b << endl;
                edgeCount++;
            }
            else
            {
                cout << "Edge: " << temp.a << " --- " << temp.b << endl;
                edgeCount++;
                for(int i=0;i<vertex[index2].size();i++)
                  vertex[index1].push_back(vertex[index2][i]);
                vertex.erase(vertex.begin()+index2);
            }
        }
        cout << v-edgeCount << "   Connected Component(s) in total" << endl << endl;
    }

    void dijkstra(int s=0)
    {
        assert(s>=0 && s<v);
        cout << endl << "Dijkstra Algorithm:  start from the Vertex: " << s << endl << endl;
        int temp=s,temp2;
        Weight *disk=new Weight[v]();
        int *from=new int[v];
        bool *mark=new bool[v]();
        memset(from,-1,v*sizeof(int));
        mark[s]=true;
        while(true)
        {
            for(int i=0;i<g[temp].size();i++)
            {
                temp2=g[temp][i]->b;
                if(-1==from[temp2] && temp != temp2 && false==mark[temp2])
                {
                    from[temp2]=temp;
                    disk[temp2]=disk[temp]+g[temp][i]->weight;
                }
                else if(disk[temp]+g[temp][i]->weight < disk[temp2] && temp != temp2)
                {
                    from[temp2]=temp;
                    disk[temp2]=disk[temp]+g[temp][i]->weight;
                }
            }
            temp=-1;
            for(int i=0;i<v;i++)
              if(-1 != from[i] && false==mark[i])
              {
                  temp=i;
                  break;
              }
            for(int i=0;i<v;i++)
              if(-1 != from[i] && disk[i] < disk[temp] && false==mark[i])
                temp=i;
            if(-1==temp)
              break;
            mark[temp]=true;
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
