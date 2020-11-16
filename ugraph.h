#include<string>
#include<iostream>
using namespace std;

#include "timestamp.h"
#ifndef UGRAPH_H
#define UGRAPH_H

struct edge{
  int source;
  int neighbor; // adjacent node
  int w; //keeps auxiliary information
  edge(){
    neighbor = 0;
    w = 0;
  };
  edge(int i, int j){
    neighbor = i;
    w = j;
  };
  edge(int from, int to, int aweight)
  {
    source = from;
    neighbor = to;
    w = aweight;
  };
};

class Ugraph{
  public:
    Ugraph(int N);
    void bfs(int s);
    void dfs();
    void dfsVisit(int u, int &t);
    void printGraph();
    void addEdge(int u, int v);
    void addEdge(int u, int v, int weight);
    void removeEdge(int u, int v);

    // Project 4 Functions
    void dijkstra(int s);

    void printDistance();

    void printParents();

    void printPath(int u, int v);

    int lenghtShortestW(int u, int v);

    void kruskal();

    void printMST();

    int weightMST();

  private:
    vector< vector<edge> > Adj; //adjacency lists of the graph 
    vector<int> distance; //for BFS and DFS
    vector<int> parents; //for BFS and DFS
    vector<char> colors; //for DFS
    vector<TimeStamp> stamps; //for DFS: stamps[v].d returns discovery time of v, and stamps[v].f finishing time.
    int size;
    
    vector< vector<edge> > mst;

    int findSet(int v);

    void combine(int x, int y);
};

#endif
