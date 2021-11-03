#pragma once

#include "constants.h"
#include "graph.h"
#include "station.h"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

void initStations(vector<Station> &stations);
void initRouteMap(Graph &routeMap);
void listStations(vector<Station> &stations);
void printRoute(vector<Station> &stations, vector<int> &route);