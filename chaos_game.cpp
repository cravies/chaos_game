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
#include "auxillary.h"

using namespace std;

int ITERS = 10000;

void make_points_square(vector<vector<double>> &points) {
    // generate vertices
    vector<vector<double>> vertices;
    vertices.emplace_back(vector<double>{0, 0});
    vertices.emplace_back(vector<double>{0, 1});
    vertices.emplace_back(vector<double>{1, 0});
    vertices.emplace_back(vector<double>{1, 1});
    cout << "make_points_square" << endl;
    for (vector<double> v : vertices) {
        cout << "vertex:" << endl;
        for (double d : v) {
            cout << "\t" << d;
        }
        cout << endl;
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

void make_points_triangle(vector<vector<double>> &points) {
    // generate vertices
    vector<vector<double>> vertices;
    vertices.emplace_back(vector<double>{0, 0});
    vertices.emplace_back(vector<double>{0.5, (sqrt(3)*0.5)});
    vertices.emplace_back(vector<double>{1, 0});
    cout << "make_points_triangle" << endl;
    for (vector<double> v : vertices) {
        cout << "vertex:" << endl;
        for (double d : v) {
            cout << "\t" << d;
        }
        cout << endl;
    }
    // generate points
    // current point location
    vector<double> mid = {0.33,0.33};
    // previous selected vertex
    vector<double> prev = vertices[0];
    // current selected vertex
    vector<double> vertex = vertices[1];
    // random number generator object
    random_device rd;
    mt19937 gen(rd());
    // for picking vertices
    uniform_int_distribution<> choose_vertex(0, 2);
    for (int i=0; i<ITERS; i++) {
        int v = choose_vertex(gen);
        vertex = vertices[v];
        // mid = 1/2(vertex + mid)
        transform(mid.begin(), mid.end(), vertex.begin(), mid.begin(), average);
        // add to points
        points.push_back(mid);
        // set prev vertex
        prev = vertex;
    }
}

int main() {
    // vector of chaos game points
    vector<vector<double>> pointsSquare;
    vector<vector<double>> pointsTriangle;
    // 
    cout << "chaos game hello world\n";
    make_points_square(pointsSquare);
    writePointsToCsv(pointsSquare, "square.csv");
    make_points_triangle(pointsTriangle);
    writePointsToCsv(pointsTriangle, "triangle.csv");
}