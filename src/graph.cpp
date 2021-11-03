#include "../includes/graph.h"

Graph::Graph(int V) { adjList.resize(V); }

void Graph::addEdge(int u, int v, int w) {
  adjList[u].push_back({v, w});
  adjList[v].push_back({u, w});
}

vector<int> Graph::dijkstra(int src, int dest) {
  vector<int> distance(N_STATIONS, INF);
  vector<int> previous(N_STATIONS, UNDEFINED);

  distance[src] = 0;

  FibonacciHeap pq;
  vector<Node *> stationsPtr(N_STATIONS);
  Node *p;
  for (int i = 1; i < N_STATIONS; i++) {
    p = pq.insert(i, distance[i]);
    stationsPtr[i] = p;
  }

  while (!pq.isEmpty()) {
    int id, value;
    pair<int, int> tmp = pq.removeMinimum();
    id = tmp.first, value = tmp.second;
    // cout << id << "," << value << endl;  
    // cout << "Works here\n";
    for (auto v : adjList[id]) {
      // cout << "Works here again\n";
      auto alt = value + v.second;
      if (alt < distance[v.first]) {
        distance[v.first] = alt;
        previous[v.first] = id;
        pq.decreaseKey(stationsPtr[v.first], alt);
      }
    }
  }

  // destination_reached:
  vector<int> route;
  while (dest != UNDEFINED) {
    route.push_back(dest);
    dest = previous[dest];
  }
  std::reverse(route.begin(), route.end());
  return route;
}