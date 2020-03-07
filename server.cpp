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

//Taking the latitude and longitude finds the nearest vertex
int findVertex(long long lat, long long lon, unordered_map<int, Point>& vertice){
    long long oldLon = 10000;
    long long oldLat = 10000;
    int vertex = -1;
    for(auto i = vertice.begin(); i != vertice.end(); i++){
        int key = i->first;
        Point p = vertice[key];
        int x = abs(p.lat - lat);
        int y = abs(p.lon - lon);
        if(x < oldLat && y < oldLon){
            oldLat = x;
            oldLon = y;
            vertex = key;
        }

    }
    return vertex;
}

void readGraph(string filename, WDigraph& graph, unordered_map<int, Point>& points) {
	// Initializing of variables
	
	string line;
	fstream file;
	file.open(filename);

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

			points[vertex] = pt1;

			graph->addVertex(vertex);
			i++;
			

		// Else if the first char in the line is E then an edge will be added
		} else if(str2 == "E"){
			int startingPos1 = line.find(",", 2) - 2;
			int startingPos2 = line.find(",", line.find(",", 2) + 1) - 3 - startingPos1;

			string str3 = line.substr(2,startingPos1);
			string str4 = line.substr(line.find(",", 2) + 1,startingPos2);

			int vertex1 = stoi(str3);
			int vertex2 = stoi(str4);

			long long cost = manhattan(points[vertex1], points[vertex2]);

			graph->addEdge(vertex1, vertex2, cost);
			graph->addEdge(vertex2, vertex1, cost);
		}
	}
	file.close();
	
}

void server(char inputFile[], char outputFile[]){
    string inFile = inputFile;
    string outFile = outputFile;
    ifstream input;
    ifstream output;
    input.open(inFile, ifstream::in);
    output.open(outFile, ifstream::out);
    while(true){
        char line[200];
        string dataLine;
        input.getline(line, 200);
        dataLine = line;
        if(dataLine[0] == 'R'){
            int space1 = dataLine.find(" ");
            int space2 = dataLine.find(" ", space1 + 1);
            long long lat1 = stoi(dataLine.substr(space1 + 1, space2-space1));
            int space3 = dataLine.find(" ", space2+1);
            long long lon1 = stoi(dataLine.substr(space2+2, space3-space1));
            int space4 = dataLine.find(" ", space3+1);
            long long lat2 = stoi(dataLine.substr(space3+1, space4-space3));
            int end = dataLine.find("\n", space4+1);
            long long lon2 = stoi(dataLine.substr(space4+1, end-space4));
            cout << lat1 << " " << lon1 << " " << lat2 <<" " << lon2 << endl;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char *file = argv[1];

    return 0;
}
