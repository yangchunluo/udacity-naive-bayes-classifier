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

void GNB::get_features(const vector<double> raw, vector<double> features)
{
    // feature engineering.
    assert(raw.size() == 4);
    double s = raw[0], d = raw[1], s_dot = raw[2], d_dot = raw[3];
    features.push_back(fmod(d, lane_width));
    features.push_back(s_dot); 
    features.push_back(d_dot);
}

void GNB::train(vector<vector<double>> data, vector<string> labels)
{

	/*
		Trains the classifier with N data points and labels.

		INPUTS
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
    assert(data.size() == labels.size());
    for (int i = 0; i < data.size(); i ++) {
        vector<double> features;
        get_features(data[i], features);

        string label = labels[i];
       /* 
        if (p_labels.find(label) == p_labels.cend()) {
            p_labels[label] = 0;
        } else {
            p_labels[label] ++;
        }*/
    }
}

string GNB::predict(vector<double> sample)
{
	/*
		Once trained, this method is called and expected to return 
		a predicted behavior for the given observation.

		INPUTS

		observation - a 4 tuple with s, d, s_dot, d_dot.
		  - Example: [3.5, 0.1, 8.5, -0.2]

		OUTPUT

		A label representing the best guess of the classifier. Can
		be one of "left", "keep" or "right".
		"""
		# TODO - complete this
	*/

	return this->possible_labels[1];
}
