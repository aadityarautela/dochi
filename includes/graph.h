#pragma once
#include "fibheap.h"
#include "station.h"
#include "constants.h"
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
private:
  vector<vector<pair<int, int>>> adjList;
  void dfsutil(int id, vector<bool> &visited);

public:
  Graph(int V);
  void addEdge(int u, int v, int w);
  vector<int> dijkstra(int src, int dest);
  int weight(int u, int v);
  int countDFS();
};
