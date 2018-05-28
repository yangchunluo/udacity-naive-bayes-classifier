#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <random>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Vehicle {
public:

    map<string, int> lane_direction = {{"PLCL", 1},
                                       {"LCL",  1},
                                       {"LCR",  -1},
                                       {"PLCR", -1}};

    struct collider {

        bool collision; // is there a collision?
        int time; // time collision happens

    };

    int L = 1;

    int preferred_buffer = 6; // impacts "keep lane" behavior.

    int lane;

    int s;

    float v;

    float a;

    float target_speed;

    int lanes_available;

    float max_acceleration;

    int goal_lane;

    int goal_s;

    string state;

    /**
    * Constructor
    */
    Vehicle() = default;
    Vehicle(int lane, int s, float v, float a, string state);

    /**
    * Destructor
    */
    virtual ~Vehicle() = default;

    vector<Vehicle> choose_next_state(map<int, vector<Vehicle>> predictions);

    vector<string> successor_states();

    vector<Vehicle> generate_trajectory(string state, map<int, vector<Vehicle>> predictions);

    vector<float> get_kinematics(map<int, vector<Vehicle>> predictions, int lane);

    vector<Vehicle> constant_speed_trajectory();

    vector<Vehicle> keep_lane_trajectory(map<int, vector<Vehicle>> predictions);

    vector<Vehicle> lane_change_trajectory(string state, map<int, vector<Vehicle>> predictions);

    vector<Vehicle> prep_lane_change_trajectory(string state, map<int, vector<Vehicle>> predictions);

    void increment(int dt);

    float position_at(int t);

    bool get_vehicle_behind(map<int, vector<Vehicle>> predictions, int lane, Vehicle &rVehicle);

    bool get_vehicle_ahead(map<int, vector<Vehicle>> predictions, int lane, Vehicle &rVehicle);

    vector<Vehicle> generate_predictions();

    void realize_next_state(vector<Vehicle> trajectory);

    void configure_ego(int target_speed, int num_lanes, int goal_lane, int goal_dist, int max_acc);

};

#endif
