#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>

using namespace std;

#include "ugraph.h"
#include "item.h"
#include "priorityqueue.h"

Ugraph::Ugraph(int N){

  size = N;

  Adj.resize(size);
  distance.resize(size);
  parents.resize(size);
  colors.resize(size);
  stamps.resize(size);
  mst.resize(size);

}//default

void Ugraph::addEdge(int u, int v){
  Adj[u].push_back(edge(v, 0));
  Adj[v].push_back(edge(u, 0));
}

void Ugraph::addEdge(int u, int v, int aweight){
  Adj[u].push_back(edge(v, aweight));
  Adj[v].push_back(edge(u, aweight));
}

void Ugraph::removeEdge(int u, int v)
{
  int sizeU = (int) Adj[u].size();

  for (int i = 0; i < sizeU; i++)
  {
    int cur = Adj[u][i].neighbor;

    if (cur == v)
    {
      Adj[u][i] = Adj[u][sizeU - 1];
      Adj[u].resize(sizeU - 1);
      break;
    }
  }

  int sizeV = (int) Adj[v].size();

  for (int i = 0; i < sizeV; i++)
  {
    int cur = Adj[v][i].neighbor;

    if (cur == u)
    {
      Adj[v][i] = Adj[v][sizeV - 1];
      Adj[v].resize(sizeV - 1);
      break;
    }
  }
}

void Ugraph::printGraph(){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < (int)Adj[i].size(); j++){
      int v = Adj[i][j].neighbor;
      cout << v << " " ;
    }//for j
    cout << endl;
  }
}//printGraph

void Ugraph::bfs(int s){
  for(int i = 0; i < size; i++){
    distance[i] = INT_MAX;
    parents[i] = i;
  }//for
  distance[s] = 0;
  queue<int> aq;
  aq.push(s);
  while(!aq.empty()){
    int u = aq.front();
    cout << u << " ";
    aq.pop();

    for(int i = 0; i < (int)Adj[u].size(); i++){
      int v = Adj[u][i].neighbor;
      if(distance[v] == INT_MAX){
        distance[v] = distance[u] + 1;
        parents[v] = u;
        aq.push(v);
      }
    }//for
  }//while

  cout << endl;
}//bfs

void Ugraph::dfs(){
  for(int i = 0; i < size; i++){
    parents[i] = i;
    colors[i] = 'W';
  }	
  int t = 0;

  for(int i = 0; i < size; i++){
    if(colors[i] == 'W'){
      //color[i] = 'G';
      dfsVisit(i, t);
    }//if
  }//for

  cout << endl;

}//dfs

void Ugraph::dfsVisit(int u, int &t){
  cout << u << " ";

  colors[u] = 'G';
  stamps[u].d = t;
  t++;

  for(int i = 0; i < (int)Adj[u].size(); i++){
    int v = Adj[u][i].neighbor;
    if(colors[v] == 'W'){
      parents[v] = u;
      colors[v] = 'G';
      dfsVisit(v, t);
    }
  }//for
  colors[u] = 'B';
  stamps[u].f = t;
  t++;
}//dfsVisit	

void Ugraph::dijkstra(int s)
{
  for (int i = 0; i < size; i++)
  {
    distance[i] = INT_MAX;
    parents[i] = i;
  }//for

  Item *priorities = new Item[size];

  for (int i = 0; i < size; i++)
  {
    priorities[i] = Item(i, distance[i]);
  }

  distance[s] = 0;
  priorities[s].priority = 0;
  PriorityQueue pq(priorities, size);

  while(pq.getSize() != 0)
  {
    Item anItem = pq.getMin();
    pq.pop();
    int u = anItem.key;

    if (distance[u] != INT_MAX)
    {
      for (int i = 0; i < (int) Adj[u].size(); i++)
      {
        int n = Adj[u][i].neighbor;
        int w = Adj[u][i].w;
        int nd = distance[u] + w;

        if (pq.isKey(n))
        {
          if (nd < distance[n])
          {
            distance[n] = nd;
            parents[n] = u;
            pq.updatePriority(n, distance[n]);
          }
        }
      }//for
    }
  }//while
}

void Ugraph::printDistance()
{
  for (int i = 0; i < size; i++)
  {
    cout << distance[i] << " ";
  }

  cout << endl;
}

void Ugraph::printParents()
{
  for (int i = 0; i < size; i++)
  {
    cout << parents[i] << " ";
  }

  cout << endl;
}

void Ugraph::printPath(int u, int v)
{
  if (parents[v] != u)
    printPath(u, parents[v]);

  if (parents[v] == u)
    cout << u << " ";

  cout << v << " ";
  return;
}

int Ugraph::lenghtShortestW(int u, int v)
{
  dijkstra(u);
  printPath(u, v);
  cout << endl;
  return distance[v];
}

bool lessThan(const edge &x, const edge &y){ return (x.w < y.w) ? true : false; };

void Ugraph::kruskal()
{
  vector<edge> edgesAll;

  for (int u = 0; u < size; u++)
  {
    for (int j = 0; j < (int) Adj[u].size(); j++)
    {
      int v = Adj[u][j].neighbor;
      int w = Adj[u][j].w;
      
      if (u < v)
        edgesAll.push_back(edge(u, v, w));
    }
  }

  for (int i = 0; i < size; i++)
  {
    distance[i] = 0;
    parents[i] = i;
  }//for

  sort(edgesAll.begin(), edgesAll.end(), lessThan);

  mst.resize(size);

  int counter = 0;
  
  for (int i = 0; i < (int) edgesAll.size(); i++)
  {
    if (counter == size - 1)
      break;

    int u = edgesAll[i].source;
    int v = edgesAll[i].neighbor;
    int w = edgesAll[i].w;

    int setU = findSet(u);
    int setV = findSet(v);

    if (setU != setV)
    {
      mst[u].push_back(edge(u, v, w));
      mst[v].push_back(edge(v, u, w));
      combine(setU, setV);
      counter++;
    }
  }
}

int Ugraph::findSet(int v)
{
  if (v != parents[v])
    parents[v] = findSet(parents[v]);

  return parents[v];
}

void Ugraph::combine(int x, int y)
{
  if (distance[x] > distance[y])
    parents[y] = x;

  else
  {
    parents[x] = y;
    
    if (distance[x] == distance[y])
    {
      distance[y]++;
    }
  }
}

void Ugraph::printMST()
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < (int) mst[i].size(); j++)
    {
      cout << mst[i][j].neighbor << " ";
    }
    
    cout << endl;
  }
}

int Ugraph::weightMST()
{
  int sum = 0;

  for (int i = 0; i < (int) mst.size(); i++)
  {
    for (int j = 0; j < (int) mst[i].size(); j++)
    {
      sum += mst[i][j].w;
    }
  }

  return sum / 2;
}
