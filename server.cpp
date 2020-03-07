// -------------------------------------------------------------------------------
// Names: Paige Lekach & Justin Mackenzie
// CMPUT 275, Winter 2020
//
// Assignment #2 Route finder Part #1
// --------------------------------------------------------------------------------

#include "digraph.cpp"
#include "wdigraph.h"
#include "dijkstra.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <cmath>
#include <list>
#include <utility>
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
    long long oldLon = 1000000000;
    long long oldLat = 1000000000;
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
    
    while(getline(file, line)){
        
        string str2 = line.substr(0,1);

        // If the first char in the line is V then a vertex will be added
        if(str2 == "V"){
            
            int start = line.find(',');
            int end = line.find(',', start + 1);

            string subS = line.substr(start+1, end-start-1);

            start = end;
            end = line.find(',', start+1);
            //cout<<end<<endl;
            //cout<<"_____"<<endl;
            string lat = line.substr(start+1, end-start-1);
            //cout<<"lat "<< lat<<endl;

            start = end;

            //end = line.find('\n', start +1);
            //cout<<end<<endl;
            //cout<<"_____"<<endl;
            string lon = line.substr(start+1, line.length()-1);
            //cout<<"lon "<<lon<<endl;

            int vertex = stoi(subS);
            double latDoub = stod(lat);
            double lonDoub = stod(lon);
            //cout<<vertex<<endl;

            long long newLon = static_cast<long long>(lonDoub*100000);
            long long newLat = static_cast<long long>(latDoub*100000);

            pt1.lat = newLat;
            pt1.lon = newLon;
            //cout<<pt1.lat<< " " <<pt1.lon<<endl;
            points[vertex] = pt1;
            //cout<<"here11"<<endl;
            graph.addVertex(vertex);
            //break;
            
            

        // Else if the first char in the line is E then an edge will be added
        } else if(str2 == "E"){
            int startingPos1 = line.find(",", 2) - 2;
            int startingPos2 = line.find(",", line.find(",", 2) + 1) - 3 - startingPos1;

            string str3 = line.substr(2,startingPos1);
            string str4 = line.substr(line.find(",", 2) + 1,startingPos2);
            //cout<<str3<<" "<<str4<<endl;
            int vertex1 = stoi(str3);

            int vertex2 = stoi(str4);

            long long cost = manhattan(points[vertex1], points[vertex2]);

            graph.addEdge(vertex1, vertex2, cost);
            //graph.addEdge(vertex2, vertex1, cost);
            
        }
    }
    file.close();
    
}

void dijkstra(const WDigraph& graph, int startVertex, 
    unordered_map<int, PIL>& searchTree) {

    // All active fires stored as follows:
    // say an entry is (v, (u, d)), then there is a fire that started at u
    // and will burn the u->v edge, reaching v at time d
    list<PIPIL> fires;

    // at time 0, the startVertex burns, we use -1 to indicate there is
    // no "predecessor" of the startVertex

    fires.push_back(PIPIL(startVertex, PIL(-1, 0)));

    // while there is an active fire
    while (!fires.empty()) {
        // find the fire that reaches its endpoint "v" earliest,
        // represented as an iterator into the list
        auto earliestFire = fires.begin();
        for (auto iter = fires.begin(); iter != fires.end(); ++iter) {
            if (iter->second.second < earliestFire->second.second) {
                earliestFire = iter;
            }
        }

        // to reduce notation in the code below, this u,v,d agrees with
        // the intuition presented in the comment when PIPIL is typedef'ed
        int v = earliestFire->first, u = earliestFire->second.first, d = earliestFire->second.second;
        // remove this fire
        fires.erase(earliestFire);

        // if u is already "burned", there nothing to do
        if (searchTree.find(v) != searchTree.end()) {
            continue;
        }
        // declare that v is "burned" at time d with a fire that spawned from u
        searchTree[v] = PIL(u, d);
        // now start fires from all edges exiting vertex v
        for (auto iter = graph.neighbours(v); iter != graph.endIterator(v); iter++) {
            int nbr = *iter;

            // the fire starts at v at time d and will reach nbr
            // at time d + (length of v->nbr edge)
            int burn = d + graph.getCost(v, nbr);
            fires.push_back(PIPIL(nbr, PIL(v, burn)));
        }
    }
}

void server(char inputFile[], char outputFile[], unordered_map<int, Point>& nodes, WDigraph graph){
    unordered_map<int, PIL> searchTree;
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
            int startVertex = findVertex(lat1, lon1, nodes);
            dijkstra(graph, startVertex,searchTree);

            int endVertex = findVertex(lat2, lon2, nodes);


            list<int> path;
            if (searchTree.find(endVertex) == searchTree.end()) {
              cout << "Vertex " << endVertex << " not reachable from " << startVertex << endl;
            }
            else {
              int stepping = endVertex;
              while (stepping != startVertex) {
                path.push_front(stepping);

                // crawl up the search tree one step
                stepping = searchTree[stepping].first;
              }
              path.push_front(startVertex);

              cout << "Cost of cheapest path from " << startVertex << " to "
                   << endVertex << " is: " << searchTree[endVertex].second << endl;
              cout << "Path:";
              for (auto it : path) {
                cout << ' ' << it;
              }
              cout << endl;
            }
            break;
        }
    }
}



int main(int argc, char *argv[])
{
    unordered_map<int, Point> test; 
    WDigraph graph;
    char *inputFile = argv[1];
    char *outputFile = argv[2];
    readGraph("edmonton-roads-2.0.1.txt", graph, test);
    server(inputFile, outputFile, test, graph);


    return 0;
}
