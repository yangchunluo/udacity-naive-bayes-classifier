#include <iostream>
#include <random>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iterator>
#include "vehicle.h"

#define EGO_KEY (-1)

using namespace std;

class Road {
public:

	int update_width = 70;

  	string ego_rep = " *** ";

    vector<int> lane_speeds;

    int speed_limit;

    double density;

    int camera_center;

    map<int, Vehicle> vehicles;

    /**
  	* Constructor
  	*/
  	Road(int speed_limit, double traffic_density, vector<int> lane_speeds);

  	/**
  	* Destructor
  	*/
  	virtual ~Road() = default;

  	Vehicle get_ego();

  	void populate_traffic();

  	void advance();

  	void display(int timestep);

  	void add_ego(pair<int, int> start, pair<int, int> goal, int max_accel);

  	void cull();

};

