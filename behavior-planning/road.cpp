#include <iostream>
#include "road.h"
#include "vehicle.h"
#include <cmath>
#include <map>
#include <string>
#include <iterator>


/**
 * Initializes Road
 */
Road::Road(int speed_limit, double traffic_density, vector<int> lane_speeds) {
    this->lane_speeds = lane_speeds;
    this->speed_limit = speed_limit;
    this->density = traffic_density;
    this->camera_center = this->update_width / 2;
}

Vehicle Road::get_ego() {
    return this->vehicles.find(EGO_KEY)->second;
}

void Road::populate_traffic() {

    int start_s = max(this->camera_center - this->update_width / 2, 0);
    int vehicles_added = 0;
    for (int l = 0; l < this->lane_speeds.size(); l++) {
        int lane_speed = this->lane_speeds[l];
        for (int s = start_s; s < start_s + this->update_width; s++) {
            if ((double) rand() / RAND_MAX < this->density) {
                Vehicle vehicle = Vehicle(l, s, lane_speed, 0, "CS");
                this->vehicles.insert(std::pair<int, Vehicle>(++vehicles_added, vehicle));
            }
        }
    }
}

void Road::advance() {
    map<int, vector<Vehicle> > predictions;

    auto it = this->vehicles.begin();
    while (it != this->vehicles.end()) {
        predictions[it->first] = it->second.generate_predictions();
        it++;
    }

    it = this->vehicles.begin();
    while (it != this->vehicles.end()) {
        if (it->first == EGO_KEY) {
            vector<Vehicle> trajectory = it->second.choose_next_state(predictions);
            it->second.realize_next_state(trajectory);
        } else {
            it->second.increment(1);
        }
        it++;
    }

}


void Road::add_ego(pair<int, int> start, pair<int, int> goal, int max_accel) {
    auto it = this->vehicles.begin();
    while (it != this->vehicles.end()) {
        int v_id = it->first;
        Vehicle v = it->second;
        if (v.lane == start.second && v.s == start.first) {
            this->vehicles.erase(v_id);
        }
        it++;
    }
    Vehicle ego = Vehicle(start.second, start.first, this->lane_speeds[start.second],
                          0 /* acceleration*/, "KL");
    ego.configure_ego(this->speed_limit, (int) this->lane_speeds.size(), goal.second, goal.first, max_accel);
    this->vehicles.insert(std::pair<int, Vehicle>(EGO_KEY, ego));

}

void Road::display(int timestep) {

    Vehicle ego = this->vehicles.find(EGO_KEY)->second;
    int s = ego.s;
    string state = ego.state;

    this->camera_center = max(s, this->update_width / 2);
    int s_min = max(this->camera_center - this->update_width / 2, 0);
    int s_max = s_min + this->update_width;

    vector<vector<string> > road;

    for (int i = 0; i < this->update_width; i++) {
        vector<string> road_lane;
        for (int ln = 0; ln < this->lane_speeds.size(); ln++) {
            road_lane.emplace_back("     ");
        }
        road.push_back(road_lane);

    }

    auto it = this->vehicles.begin();
    while (it != this->vehicles.end()) {

        int v_id = it->first;
        Vehicle v = it->second;

        if (s_min <= v.s && v.s < s_max) {
            string marker;
            if (v_id == EGO_KEY) {
                marker = this->ego_rep;
            } else {

                stringstream oss;
                stringstream buffer;
                buffer << " ";
                oss << v_id;
                for (long buffer_i = oss.str().length(); buffer_i < 3; buffer_i++) {
                    buffer << "0";

                }
                buffer << oss.str() << " ";
                marker = buffer.str();
            }
            road[v.s - s_min][v.lane] = marker;
        }
        it++;
    }
    ostringstream oss;
    oss << "+Meters ======================+ step: " << timestep << endl;
    int i = s_min;
    for (int lj = 0; lj < road.size(); lj++) {
        if (i % 20 == 0) {
            stringstream buffer;
            stringstream dis;
            dis << i;
            for (long buffer_i = dis.str().length(); buffer_i < 3; buffer_i++) {
                buffer << "0";
            }

            oss << buffer.str() << dis.str() << " - ";
        } else {
            oss << "      ";
        }
        i++;
        for (int li = 0; li < road[0].size(); li++) {
            oss << "|" << road[lj][li];
        }
        oss << "|";
        oss << "\n";
    }

    cout << oss.str();

}



