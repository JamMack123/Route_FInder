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
void readGraph(string filename, WDigraph& graph, unordered_map<int>, Point& points) {
	// Initializing of variables
	WDigraph* newGraph = new WDigraph;
	string line;
	fstream file;
	file.open(filename);

	unordered_map<int,Point> storedVals;
	Point pt1;

	// Reading the file line by line until there are no lines left
	int i = 0;
	while(getline(file, line)){
		string str2 = line.substr(0,1);

		// If the first char in the line is V then a vertex will be added
		if(str2 == "V"){
			
			int start = line.find(',');
			int end = line.find(',', start + 1);

			string subS = line.substr(start+1, end-start-1);

			start = end;
			end = line.find(',', start+1);

			string lon = line.substr(start+1, end-start-1);

			start = end;

			end = line.find('\n', start +1);

			string lat = line.substr(start+1, end-start-1);


			int vertex = stoi(str3);
			double latDoub = stod(lat);
			double lonDoub = stod(lon);

			long long newLon = static_cast<long long>(lonDoub*100000);
			long long newLat = static_cast<long long>(latDoub*100000);

			pt1.lat = newLat;
			pt1.lon = newLon;

			storedVals[vertex] = pt1;

			newGraph->addVertex(vertex);
			i++;
			

		// Else if the first char in the line is E then an edge will be added
		} else if(str2 == "E"){
			int startingPos1 = line.find(",", 2) - 2;
			int startingPos2 = line.find(",", line.find(",", 2) + 1) - 3 - startingPos1;

			string str3 = line.substr(2,startingPos1);
			string str4 = line.substr(line.find(",", 2) + 1,startingPos2);

			int vertex1 = stoi(str3);
			int vertex2 = stoi(str4);

			long long cost = manhattan(storedVals[vertex1], storedVals[vertex2]);

			newGraph->addEdge(vertex1, vertex2, cost);
			newGraph->addEdge(vertex2, vertex1, cost);
		}
	}
	file.close();
	
}

int main(int argc, char *argv[])
{
    char *file = argv[1];

    return 0;
}
