#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <set>
#include <vector>
#include <string>

# define INF 1000000
  
// This class represents a directed graph using  
// adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // In a weighted graph, we need to store vertex  
    // and weight pair for every edge 
    std::list< std::pair<int, int> > *adj; 
  
public: 
    Graph(int V);  // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int u, int v, int w); 
  
    // prints shortest path from s 
    void shortestPath(int s, int* verts, int size); 
}; 
  
// Allocates memory for adjacency list 
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new std::list< std::pair<int, int> >[V]; 
} 
  
void Graph::addEdge(int u, int v, int w) 
{ 
    adj[u].push_back(std::make_pair(v, w)); 
    adj[v].push_back(std::make_pair(u, w)); 
} 
  
// Prints shortest paths from src to all other vertices 
void Graph::shortestPath(int src, int* verts, int size) 
{ 
    // Create a set to store vertices that are being 
    // prerocessed 
    std::set< std::pair<int, int> > setds; 
  
    // Create a vector for distances and initialize all 
    // distances as infinite (INF) 
    std::vector<int> dist(V, INF); 
  
    // Insert source itself in Set and initialize its 
    // distance as 0. 
    setds.insert(std::make_pair(0, src)); 
    dist[src] = 0; 
  
    /* Looping till all shortest distance are finalized 
       then setds will become empty */
    while (!setds.empty()) 
    { 
        // The first vertex in Set is the minimum distance 
        // vertex, extract it from set. 
        std::pair<int, int> tmp = *(setds.begin()); 
        setds.erase(setds.begin()); 
  
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted distance (distance must be first item 
        // in pair) 
        int u = tmp.second; 
  
        // 'i' is used to get all adjacent vertices of a vertex 
        for (auto i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            // Get vertex label and weight of current adjacent 
            // of u. 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            //  If there is shorter path to v through u. 
            if (dist[v] > dist[u] + weight) 
            { 
                /*  If distance of v is not INF then it must be in 
                    our set, so removing it and inserting again 
                    with updated less distance.   
                    Note : We extract only those vertices from Set 
                    for which distance is finalized. So for them,  
                    we would never reach here.  */
                if (dist[v] != INF) 
                    setds.erase(setds.find(std::make_pair(dist[v], v))); 
  
                // Updating distance of v 
                dist[v] = dist[u] + weight; 
                setds.insert(std::make_pair(dist[v], v)); 
            } 
        } 
    } 
  
    // Print shortest distances stored in dist[] 
    printf("Vertex   Distance from Source\n"); 
    for (int i = 0; i < size; ++i) 
        printf("%d \t\t %d\n", verts[i], dist[verts[i]]); 
} 
  
// Driver program to test methods of graph class 
int main() 
{ 
    // create the graph given in above fugure 
    int V = 200; 
    Graph graph(V); 

    std::ifstream input_file("./dijkstraData.txt");
    std::string line;
    while(getline(input_file, line)) {
        for(int i = 0; i < line.size(); ++i) {
            if(line[i] == '\t' || line[i] == ',') {
                line[i] = ' ';
            }
        }
        std::stringstream ss(line);
        int node1, node2;
        int weight;
        ss >> node1;
        while(ss >> node2 >> weight) {
            if(node1 < node2) {
                graph.addEdge(node1-1, node2-1, weight);
            }
        }
        line.clear();
        ss.str("");
        ss.clear();
    }
  	int verts[10] = {6,36,58,81,98,114,132,164,187,196};
    graph.shortestPath(0, verts, 10); 
    return 0; 
} 

