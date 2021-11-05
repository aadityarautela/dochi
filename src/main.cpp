#include "../includes/utils.h"

/*
* TODO
* 1) TIME (aka distance) Print
* 2) MARK INTERCHANGE with *
*/

int main() {
  vector<Station> stations;
  initStations(stations);
  Graph routeMap(N_STATIONS);
  initRouteMap(routeMap);

  bool valid_id = false;
  while (true) {
    listStations(stations);
    int src, dest;
    while (!valid_id) {
      cout << "Enter Source Station ID: ";
      cin >> src;
      if (src > 0 && src < N_STATIONS)
        valid_id = true;
      else
        cout << "Invalid Source Station ID. Please Retry.\n";
    }
    valid_id = false;
    while (!valid_id) {
      cout << "Enter Destination Station ID: ";
      cin >> dest;
      if (dest > 0 && dest < N_STATIONS)
        valid_id = true;
      else
        cout << "Invalid Destination Station ID. Please Retry.\n";
    }

    auto route = routeMap.dijkstra(src, dest);
    printRoute(stations, route);
    bool exit_prompt_valid_flag = false;
    while (true) {
      char inp;
      cout << "Exit(E)/Continue(C)\n";
      cin >> inp;
      if (inp == 'E' || inp == 'e')
        goto exit_point;
      else if (inp == 'C' || inp == 'c')
        break;
      else
        cout << "Invalid Option. Please Retry.\n";
    }
    valid_id = false;
  }

exit_point:
  return 0;
}