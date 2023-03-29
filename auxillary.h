#ifndef AUXILLARY_H
#define AUXILLARY_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <math.h>

using namespace std;

// average of two points
double average(const double& a, const double& b) {
    return 0.5*(a + b);
}

// write our points to a csv
void writePointsToCsv(const vector<vector<double>>& points, const string& filename) {
    ofstream csvFile(filename);

    if (!csvFile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    for (const auto& point : points) {
        for (size_t i = 0; i < point.size(); ++i) {
            csvFile << point[i];
            if (i != point.size() - 1) {
                csvFile << ",";
            }
        }
        csvFile << endl;
    }

    csvFile.close();
}

#endif