#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>

using namespace std;

int ITERS = 10000;

// average of two points
double average(const double& a, const double& b) {
    return 0.5*(a + b);
}

void make_points_square(float lower, float upper, vector<vector<double>> &points) {
    // generate vertices
    vector<vector<double>> vertices;
    vertices.emplace_back(vector<double>{lower, lower});
    vertices.emplace_back(vector<double>{lower, upper});
    vertices.emplace_back(vector<double>{upper, lower});
    vertices.emplace_back(vector<double>{upper, upper});
    cout << "make_points_square\n";
    for (vector<double> v : vertices) {
        cout << "vertex:\n";
        for (double d : v) {
            cout << "\t" << d;
        }
        cout << "\n";
    }
    // generate points
    // current point location
    vector<double> mid = {0.5,0.5};
    // previous selected vertex
    vector<double> prev = vertices[0];
    // current selected vertex
    vector<double> vertex = vertices[1];
    // random number generator object
    random_device rd;
    mt19937 gen(rd());
    // for picking vertices
    uniform_int_distribution<> choose_vertex(0, 3);
    // for generating x and y points inside the square
    uniform_real_distribution<> choose_coord(lower, upper);
    for (int i=0; i<ITERS; i++) {
        int v = choose_vertex(gen);
        vertex = vertices[v];
        // only write when we have picked a new vertex
        // otherwise we won't generate fractal
        if (vertex!=prev) {
            // mid = 1/2(vertex + mid)
            transform(mid.begin(), mid.end(), vertex.begin(), mid.begin(), average);
            // add to points
            points.push_back(mid);
            // set prev vertex
            prev = vertex;
        }
    }
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

int main() {
    // vector of chaos game points
    vector<vector<double>> points;
    // 
    cout << "chaos game hello world\n";
    make_points_square(0.0,1.0,points);
    writePointsToCsv(points, "out.csv");
}