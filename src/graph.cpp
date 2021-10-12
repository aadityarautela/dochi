#include "../includes/graph.h"

Graph::Graph(int V) { adjList.resize(V); }

void Graph::addEdge(int u, int v, int w) {
  adjList[u].push_back({v, w});
  adjList[v].push_back({u, w});
}