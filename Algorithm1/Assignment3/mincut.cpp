#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

// a structure to represent a unweighted edge in graph 
struct Edge 
{ 
    int src, dest; 
    Edge(int src, int dest): src(src), dest(dest) {}
}; 
  
// a structure to represent a connected, undirected 
// and unweighted graph as a collection of edges. 
class Graph 
{ 
public:
    // V-> Number of vertices
    int V; 
    // graph is represented as an array of edges. 
    // Since the graph is undirected, the edge 
    // from src to dest is also edge from dest 
    // to src. Both are counted as 1 edge here. 
    std::vector<Edge> edge;
    Graph(int V): V(V){}
    Graph() {}
}; 
  
// A structure to represent a subset for union-find 
struct subset 
{ 
    int parent; 
    int rank; 
}; 
  
// Function prototypes for union-find (These functions are defined 
// after kargerMinCut() ) 
int find(struct subset subsets[], int i); 
void Union(struct subset subsets[], int x, int y); 
  
// A very basic implementation of Karger's randomized 
// algorithm for finding the minimum cut. Please note 
// that Karger's algorithm is a Monte Carlo Randomized algo 
// and the cut returned by the algorithm may not be 
// minimum always 
int kargerMinCut(Graph* graph) 
{ 
    // Get data of given graph 
    int V = graph->V, E = graph->edge.size(); 
    auto edge = graph->edge;
    // Edge *edge = graph->edge; 
  
    // Allocate memory for creating V subsets. 
    struct subset *subsets = new subset[V]; 
  
    // Create V subsets with single elements 
    for (int v = 0; v < V; ++v) 
    { 
        subsets[v].parent = v; 
        subsets[v].rank = 0; 
    } 
  
    // Initially there are V vertices in 
    // contracted graph 
    int vertices = V; 
  
    // Keep contracting vertices until there are 
    // 2 vertices. 
    while (vertices > 2) 
    { 
       // Pick a random edge 
       int i = rand() % E; 
  
       // Find vertices (or sets) of two corners 
       // of current edge 
       int subset1 = find(subsets, edge[i].src); 
       int subset2 = find(subsets, edge[i].dest); 
  
       // If two corners belong to same subset, 
       // then no point considering this edge 
       if (subset1 == subset2) 
         continue; 
  
       // Else contract the edge (or combine the 
       // corners of edge into one vertex) 
       else { 
          vertices--; 
          Union(subsets, subset1, subset2); 
       } 
    } 
  
    // Now we have two vertices (or subsets) left in 
    // the contracted graph, so count the edges between 
    // two components and return the count. 
    int cutedges = 0; 
    for (int i=0; i<E; i++) 
    { 
        int subset1 = find(subsets, edge[i].src); 
        int subset2 = find(subsets, edge[i].dest); 
        if (subset1 != subset2) 
          cutedges++; 
    } 
  
    return cutedges; 
} 
  
// A utility function to find set of an element i 
// (uses path compression technique) 
int find(struct subset subsets[], int i) 
{ 
    // find root and make root as parent of i 
    // (path compression) 
    if (subsets[i].parent != i) 
      subsets[i].parent = 
             find(subsets, subsets[i].parent); 
  
    return subsets[i].parent; 
} 
  
// A function that does union of two sets of x and y 
// (uses union by rank) 
void Union(struct subset subsets[], int x, int y) 
{ 
    int xroot = find(subsets, x); 
    int yroot = find(subsets, y); 
  
    // Attach smaller rank tree under root of high 
    // rank tree (Union by Rank) 
    if (subsets[xroot].rank < subsets[yroot].rank) 
        subsets[xroot].parent = yroot; 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
        subsets[yroot].parent = xroot; 
  
    // If ranks are same, then make one as root and 
    // increment its rank by one 
    else
    { 
        subsets[yroot].parent = xroot; 
        subsets[xroot].rank++; 
    } 
} 
  
// Creates a graph with V vertices and E edges 
Graph* createGraph(int V) 
{ 
    Graph* graph = new Graph; 
    graph->V = V; 

    return graph; 
} 
  
// Driver program to test above functions 
int main(int argc, char* argv[]) 
{ 
    if(argc != 2){
        std::cout << "usage: " << argv[0] << " <repeat>\n";
        exit(1);
    }
    int V = 200;  // Number of vertices in graph 
    Graph* graph = createGraph(V); 

    std::ifstream file("./kargerMinCut.txt");
            
    if (file.is_open())
    {
        std::string rawInput;
        while (getline(file, rawInput))
        {
            std::istringstream is(rawInput);
            int src, dest;
            is >> src;
            while(is >> dest){
                if(src < dest){
                    graph->edge.emplace_back(src-1, dest-1); 
                }
            }
        }
        file.close();
    }
    
    // Use a different seed value for every run. 
    // srand(time(NULL)); 
    int repeat = std::atoi(argv[1]);
    std::vector<int> count;
    for(int i = 0; i < repeat; ++i){
        // srand(time(NULL)); 
        count.push_back(kargerMinCut(graph));
    }
    auto it = std::min_element(count.begin(), count.end());
    printf("Cut found by Karger's randomized algo is %d\n", *it); 
    
    return 0; 
} 
