#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cassert>
#include "classifier.h"

/**
 * Initializes GNB
 */
GNB::GNB() {

}

GNB::~GNB() {}

const int lane_width = 4;

void GNB::get_features(const vector<double> &raw, vector<double> &features)
{
    // feature engineering.
    assert(raw.size() == 4);
    double s = raw[0], d = raw[1], s_dot = raw[2], d_dot = raw[3];
    features.push_back(s);
    //features.push_back(fmod(d, lane_width));
    features.push_back(d);
    features.push_back(s_dot); 
    features.push_back(d_dot);
}

/*
    Trains the classifier with N data points and labels.
    data - array of N observations
      - Each observation is a tuple with 4 values: s, d, 
        s_dot and d_dot.
      - Example : [
            [3.5, 0.1, 5.9, -0.02],
            [8.0, -0.3, 3.0, 2.2],
            ...
        ]
    labels - array of N labels
      - Each label is one of "left", "keep", or "right".
*/
void GNB::train(vector<vector<double>> data, vector<string> labels)
{
    assert(data.size() == labels.size());
    // Count the labels.
    for (int i = 0; i < labels.size(); i ++) {
        string label = labels[i];
        if (num_labels.find(label) == num_labels.cend()) {
            num_labels[label] = 0;
        } else {
            num_labels[label] ++;
        }
    }

    // Compute the mean per feature and label.
    for (int i = 0; i < data.size(); i ++) {
        vector<double> features;
        get_features(data[i], features);
        string label = labels[i];

        if (means.find(label) == means.cend()) {
            means[label] = vector<double>(features.size());
            for (int j = 0; j < means[label].size(); j++) {
                means[label][j] = 0;
            }
        }
        for (int j = 0; j < features.size(); j++) {
            means[label][j] += features[j] / num_labels[label];
        }
    }
    cout << "means" << endl;
    for (auto const &p : means) {
        cout << "  " << p.first << ": ";
        for (auto const x : p.second) {
            cout << x << " ";
        }
        cout << endl;
    }

    // Compute the standard deviation per feature and label.
    for (int i = 0; i < data.size(); i ++) {
        vector<double> features;
        get_features(data[i], features);
        string label = labels[i];

        if (stderrs.find(label) == stderrs.cend()) {
            stderrs[label] = vector<double>(features.size());
            for (int j = 0; j < stderrs[label].size(); j++) {
                stderrs[label][j] = 0;
            }
        }
        for (int j = 0; j < features.size(); j++) {
            stderrs[label][j] += pow(features[j] - means[label][j], 2) / num_labels[label];
        }
    }
    cout << "stderr" << endl;
    for (auto const &p : stderrs) {
        cout << "  " << p.first << ": ";
        for (auto const x : p.second) {
            cout << x << " ";
        }
        cout << endl;
    }

}

/*
    Once trained, this method is called and expected to return 
    a predicted behavior for the given observation.

    INPUTS

    observation - a 4 tuple with s, d, s_dot, d_dot.
      - Example: [3.5, 0.1, 8.5, -0.2]

    OUTPUT

    A label representing the best guess of the classifier. Can
    be one of "left", "keep" or "right".
*/

string GNB::predict(vector<double> sample) {
    vector<double> features;
    get_features(sample, features);

    map<string, double> probs;

    for (auto const &label : possible_labels) {
        probs[label] = 1.0;
    }

    for (auto const &label : possible_labels) {
        for (int i = 0; i < features.size(); i++) {
            probs[label] *= 1.0 / sqrt(2.0 * 3.1415926 * stderrs[label][i]) *
                            exp(-0.5 * pow(features[i] - means[label][i], 2) / stderrs[label][i]);
        }
    }

    for (auto const &label : possible_labels) {
        probs[label] *= num_labels[label];
    }

    double max = 0;
    string max_label = "";
    for (auto const &p : probs) {
        if (p.second > max) {
            max = p.second;
            max_label = p.first;
        }
    }
    return max_label;
}
