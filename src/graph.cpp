#include "../includes/graph.h"

Graph::Graph(int V) { adjList.resize(V); }

void Graph::addEdge(int u, int v, int w) {
  adjList[u].push_back({v, w});
  adjList[v].push_back({u, w});
}

vector<int> Graph::dijkstra(int src, int dest) {
  // Initializations
  vector<int> distance(N_STATIONS, INF);
  vector<int> previous(N_STATIONS, UNDEFINED);

  distance[src] = 0;

  FibonacciHeap pq;
  vector<Node *> stationsPtr(N_STATIONS); // To aid in decreaseKey
  Node *p;
  for (int i = 1; i < N_STATIONS; i++) {
    p = pq.insert(i, distance[i]);
    stationsPtr[i] = p;
  }

  // Dijkstra Main
  while (!pq.isEmpty()) {
    int id, value;
    pair<int, int> tmp = pq.removeMinimum();
    id = tmp.first, value = tmp.second;
    for (auto v : adjList[id]) {
      auto alt = value + v.second;
      if (alt < distance[v.first]) {
        distance[v.first] = alt;
        previous[v.first] = id;
        pq.decreaseKey(stationsPtr[v.first], alt);
      }
    }
  }
  cout<<"\nTime Taken: "<<distance[dest]<<" minutes"<<endl;

  // Route Construction
  vector<int> route;
  while (dest != UNDEFINED) {
    route.push_back(dest);
    dest = previous[dest];
  }
  std::reverse(route.begin(), route.end());
  return route;
}

int Graph::countDFS() {
  vector<bool> visited(N_STATIONS, false);
  int count = 0;
  for (int i = 1; i < N_STATIONS; i++) {
    if (!visited[i]) {
      dfsutil(i, visited);
      count++;
    }
  }
  return count;
}

void Graph::dfsutil(int id, vector<bool> &visited) {
  visited[id] = true;
  for (auto v : adjList[id]) {
    if (!visited[v.first]) {
      dfsutil(v.first, visited);
    }
  }
}