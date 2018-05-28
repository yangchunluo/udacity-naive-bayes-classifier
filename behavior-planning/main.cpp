#include "road.h"
#include "vehicle.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

//impacts default behavior for most states
int SPEED_LIMIT = 10;

//all traffic in lane (besides ego) follow these speeds
vector<int> LANE_SPEEDS = {6, 7, 8, 9};

//Number of available "cells" which should have traffic
double TRAFFIC_DENSITY = 0.15;

// At each timestep, ego can set acceleration to value between 
// -MAX_ACCEL and MAX_ACCEL
int MAX_ACCEL = 2;

// s value and lane number of start and goal.
pair<int, int> START = {0, 2};
pair<int, int> GOAL = {300, 0};

// These affect the visualization
int FRAMES_PER_SECOND = 4;
int AMOUNT_OF_ROAD_VISIBLE = 40;

int main() {

    Road road = Road(SPEED_LIMIT, TRAFFIC_DENSITY, LANE_SPEEDS);

    road.update_width = AMOUNT_OF_ROAD_VISIBLE;

    road.populate_traffic();

    road.add_ego(START, GOAL, MAX_ACCEL);

    int timestep = 0;
    while (road.get_ego().s <= GOAL.first) {
        timestep++;
        if (timestep > 100) {
            break;
        }
        road.advance();
        road.display(timestep);
        //time.sleep(float(1.0) / FRAMES_PER_SECOND);
    }
    Vehicle ego = road.get_ego();
    if (ego.lane == GOAL.second) {
        cout << "You got to the goal in " << timestep << " seconds!" << endl;
        if (timestep > 35) {
            cout << "But it took too long to reach the goal. Go faster!" << endl;
        }
    } else {
        cout << "You missed the goal. You are in lane " << ego.lane << " instead of " << GOAL.second << "." << endl;
    }

    return 0;
}
