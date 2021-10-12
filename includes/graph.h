#pragma once
#include "station.h"
#include "fibheap.h"
#include <vector>

using namespace std;

class Graph {
private:
  vector<vector<pair<int, int>>> adjList;

public:
  Graph(int V);
  void addEdge(int u, int v, int w);
};
