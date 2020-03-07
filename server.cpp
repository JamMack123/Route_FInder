// -------------------------------------------------------------------------------
// Names: Paige Lekach & Justin Mackenzie
// CMPUT 275, Winter 2020
//
// Assignment #2 Route finder Part #1
// --------------------------------------------------------------------------------

#include "digraph.cpp"
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <cmath>
using namespace std;

struct Point {
    long long lat; // latitude of the point
    long long lon; // longitude of the point
};

long long manhattan(const Point& pt1, const Point& pt2) {
    long long dist = 0;
    long long x = abs(pt1.lat - pt2.lat);
    long long y = abs(pt1.lon - pt2.lon);
    dist = x+y;
    return dist;
}


int main(int argc, char *argv[])
{
    char *file = argv[1];

    return 0;
}
