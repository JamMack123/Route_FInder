// -------------------------------------------------------------------------------
// Names: Paige Lekach & Justin Mackenzie
// CMPUT 275, Winter 2020
//
// Assignment #2 Route finder Part #1
// --------------------------------------------------------------------------------
#include "digraph.h"
#include "wdigraph.h"
#include "dijkstra.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <cmath>
#include <list>
#include <utility>
using namespace std;


struct Point
{
    long long lat; // latitude of the point
    long long lon; // longitude of the point
};

unordered_map<int, Point> points;

long long manhattan(const Point &pt1, const Point &pt2)
{
    long long dist = 0;
    long long x = abs(pt1.lat - pt2.lat);
    long long y = abs(pt1.lon - pt2.lon);
    dist = x + y;
    return dist;
}
//Taking the latitude and longitude finds the nearest vertex
long long findVertex(long long lat, long long lon)
{
    // Initialized the variables that will be used
    long long oldVal = 100000000000000;
    long long vertex = -1;

    // Iterating through the point struct
    for(auto i = points.begin(); i != points.end(); i++)
    {
        long long key = i->first;
        Point p = points[key];
        long long x = abs(p.lat - lat);
        long long y = abs(p.lon - lon);

        // Calculating the distance
        long long final = x + y;
        if(final < oldVal)
        {
            oldVal = final;
            vertex = key;
        }
    }
    return vertex;
}

void readGraph(string filename, WDigraph &graph, unordered_map<int, Point> &points)
{
    // Initializing of variables
    string line;
    fstream file;
    file.open(filename);
    Point pt1;
    // Reading the file line by line until there are no lines left
    while(getline(file, line))
    {
        string str2 = line.substr(0, 1);
        // If the first char in the line is V then a vertex will be added
        if(str2 == "V")
        {
            int start = line.find(',');
            int end = line.find(',', start + 1);
            string subS = line.substr(start + 1, end - start - 1);
            start = end;
            end = line.find(',', start + 1);
            string lat = line.substr(start + 1, end - start - 1);
            start = end;
            string lon = line.substr(start + 1, line.length() - 1);
            int vertex = stoi(subS);
            double latDoub = stod(lat);
            double lonDoub = stod(lon);
            long long newLon = static_cast<long long>(lonDoub * 100000);
            long long newLat = static_cast<long long>(latDoub * 100000);
            pt1.lat = newLat;
            pt1.lon = newLon;
            points[vertex] = pt1;
            graph.addVertex(vertex);

        }
        // Else if the first char in the line is E then an edge will be added
        else if(str2 == "E")
        {
            int startingPos1 = line.find(",", 2) - 2;
            int startingPos2 = line.find(",", line.find(",", 2) + 1) - 3 - startingPos1;
            string str3 = line.substr(2, startingPos1);
            string str4 = line.substr(line.find(",", 2) + 1, startingPos2);
            int vertex1 = stoi(str3);
            int vertex2 = stoi(str4);
            long long cost = manhattan(points[vertex1], points[vertex2]);
            graph.addEdge(vertex1, vertex2, cost);
        }
    }
    file.close();
}

//Contains bulk code for handling server retrievial of data and calculations
void server(char inputFile[], char outputFile[], WDigraph graph)
{
    unordered_map<int, PIL> searchTree;
    string inFile = inputFile;
    string outFile = outputFile;
    ifstream input;
    ofstream output;
    input.open(inFile, ifstream::in);
    output.open(outFile, ifstream::out);
    while(true)
    {
        char line[200];
        string dataLine;
        input.getline(line, 200);
        dataLine = line;
        // if the server has read in an R then the data will be processed and the path will be found
        if(dataLine[0] == 'R')
        {
            int space1 = dataLine.find(" ");
            int space2 = dataLine.find(" ", space1 + 1);
            long long lat1 = stoi(dataLine.substr(space1 + 1, space2 - space1));
            int space3 = dataLine.find(" ", space2 + 1);
            long long lon1 = stoi(dataLine.substr(space2 + 1, space3 - space1));
            int space4 = dataLine.find(" ", space3 + 1);
            long long lat2 = stoi(dataLine.substr(space3 + 1, space4 - space3));
            int end = dataLine.find("\n", space4 + 1);
            long long lon2 = stoi(dataLine.substr(space4 + 1, end - space4));
            long long startVertex = findVertex(lat1, lon1);
            dijkstra(graph, startVertex, searchTree);
            long long endVertex = findVertex(lat2, lon2);
            list<long long> path;
            if (searchTree.find(endVertex) == searchTree.end())
            {
                cout << "Vertex " << endVertex << " not reachable from " << startVertex << endl;
            }
            else
            {
                long long stepping = endVertex;
                while (stepping != startVertex)
                {
                    path.push_front(stepping);
                    stepping = searchTree[stepping].first;
                }
                path.push_front(startVertex);
            }
            

            output << "N " << path.size() << endl;
            int count = path.size();
            clock_t timer = clock();
            
            // Processing the data from the input file and including a delay option
            // for when the server has waited for over 10 secs
            while(true)
            {
                char line[2];
                input.getline(line, 2);
                if(line[0] == 'A' && count != 0)
                {
                    int key = path.front();
                    path.pop_front();
                    Point p = points[key];
                    output << "W " << p.lat << " " << p.lon << endl;
                    count --;
                }
                if(count == 0)
                {
                    output << "E" << endl;
                    break;
                }
                //Checks for timeout
                clock_t time = clock() - timer;
                if((time / CLOCKS_PER_SEC) >= 10)
                {
                    cout << "Timeout has occured" << endl;
                    break;
                }

            }
            input.close();
            output.close();
            break;
        }else{
            break;
        }
    }
}



int main(int argc, char *argv[])
{
    WDigraph graph;
    char *inputFile = argv[1];
    char *outputFile = argv[2];
    readGraph("edmonton-roads-2.0.1.txt", graph, points);
    server(inputFile, outputFile, graph);
    return 0;
}
