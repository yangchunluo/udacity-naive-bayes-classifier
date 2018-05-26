#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

class GNB {
public:

	vector<string> possible_labels = {"left","keep","right"};

	/**
  	* Constructor
  	*/
 	GNB();

	/**
 	* Destructor
 	*/
 	virtual ~GNB();

 	void train(vector<vector<double> > data, vector<string>  labels);

  	string predict(vector<double>);
private:
    void get_features(const vector<double> &raw, vector<double> &features);

    map<string, vector<double>> means;
    map<string, vector<double>> stderrs;
    map<string, double> num_labels;

};

#endif
