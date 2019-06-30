#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std; 
  
// Creating shortcut for an integer pair 
typedef  pair<int, int> iPair; 
  
// Structure to represent a graph 
struct Graph 
{ 
    int V; 
    vector< pair<int, iPair> > edges; 
  
    // Constructor 
    Graph(int V) 
    { 
        this->V = V; 
    } 
  
    // Utility function to add an edge 
    void addEdge(int u, int v, int w) 
    { 
        edges.push_back({w, {u, v}}); 
    } 
  
    // Function to find MST using Kruskal's 
    // MST algorithm 
    int kruskalMST(int cluster); 
}; 
  
// To represent Disjoint Sets 
struct DisjointSets 
{ 
    int *parent, *rnk; 
    int n; 
  
    // Constructor. 
    DisjointSets(int n) 
    { 
        // Allocate memory 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 
  
        // Initially, all vertices are in 
        // different sets and have rank 0. 
        for (int i = 0; i <= n; i++) 
        { 
            rnk[i] = 0; 
  
            //every element is parent of itself 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' 
    // Path Compression 
    int find(int u) 
    { 
        /* Make the parent of the nodes in the path 
           from u--> parent[u] point to parent[u] */
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void merge(int x, int y) 
    { 
        x = find(x), y = find(y); 
  
        /* Make tree with smaller height 
           a subtree of the other tree  */
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 
  
 /* Functions returns weight of the MST*/ 
  
int Graph::kruskalMST(int cluster) 
{ 
  
    // Sort edges in increasing order on basis of cost 
    sort(edges.begin(), edges.end()); 
  
    // Create disjoint sets 
    DisjointSets ds(V); 

    int count = 0;
  
    // Iterate through all sorted edges 
    vector< pair<int, iPair> >::iterator it; 
    for (it=edges.begin(); it!=edges.end(); it++) 
    { 
        int u = it->second.first; 
        int v = it->second.second; 
  
        int set_u = ds.find(u); 
        int set_v = ds.find(v); 
  
        // Check if the selected edge is creating 
        // a cycle or not (Cycle is created if u 
        // and v belong to same set) 
        if (set_u != set_v) 
        { 
            // Current edge will be in the MST 
            // so print it 
            cout << u << " - " << v << endl; 
  
            // Merge two sets 
            ds.merge(set_u, set_v); 
	    count += 1;
        } 
	
	if (count == V - cluster + 1)
	    break;
    } 
  
    return it->first; 
} 
  
// Driver program to test above functions 
int main() 
{ 
    ifstream f("clustering1.txt");
    int V;
    f >> V;
    /* Let us create above shown weighted 
       and unidrected graph */
    Graph g(V); 

    int u, v, w;
    while(f >> u){
	f >> v;
	f >> w;
	g.addEdge(u - 1, v - 1, w);
    }

    cout << "Edges of MST are \n"; 
    int mst_ms = g.kruskalMST(4); 
  
    cout << "\nWeight of MST is " << mst_ms << "\n";
  
    return 0; 
} 
