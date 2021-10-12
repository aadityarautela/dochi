#pragma once

#include "station.h"
#include "graph.h"
#include <vector>

using namespace std;

const int N_STATIONS = 231;
void initStations(vector<Station> &stations);
void initRouteMap(Graph &routeMap);