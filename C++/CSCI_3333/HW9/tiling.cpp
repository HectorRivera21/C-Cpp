
#include "tiling.h"
#include "vertex.h"

using namespace std;


// Finds a (shortest according to edge length) augmenting path
// from s to t in a graph with vertex set V.
// Returns whether there is an augmenting path.
bool augmenting_path(Vertex* s, Vertex* t, 
        unordered_set<Vertex*> V, vector<Vertex*> &P)
{
        // Check that s and t aren't nullptr
        if (s == nullptr || t == nullptr)
	{
		cerr << "augmenting_path() was passed nullptr s or t." << endl;
		abort();
	}

        // Check that s and t are in the graph
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "augmenting_path() was passed s or t not in V." << endl;
		abort();
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "augmenting_path() was passed invalid vertex." << endl;
				abort();
			}

        // Since augmenting paths should have the fewest edges,
	// not the minimum weight, run BFS.
	queue<Vertex*> Q;
	Q.push(s);

	unordered_set<Vertex*> R;
	R.clear(); 
	R.insert(s);

	unordered_map<Vertex*, Vertex*> prev;

	while (!Q.empty())
	{
		Vertex* cur = Q.front();
		Q.pop();

		for (Vertex* nei : cur->neighs)
		{
			// Must have positive edge weight
			if (cur->weights[nei] == 0)
				continue;

			if (R.find(nei) == R.end())
			{
				Q.push(nei);
				R.insert(nei);
				prev[nei] = cur; 
			}
		}
	}      

        // If BFS never reached t
        if (R.find(t) == R.end())
                return false;

        // Reconstruct shortest path backwards
        P.clear();
        P.push_back(t);
        while (P[P.size()-1] != s)
                P.push_back(prev[P[P.size()-1]]);

        // Reverse shortest path
        for (int i = 0; i < P.size()/2; ++i)
		swap(P[i], P[P.size()-1-i]);

        return true;
}

// Returns the maximum flow from s to t in a weighted graph with vertex set V.
// Assumes all edge weights are non-negative.
int max_flow(Vertex* s, Vertex* t, unordered_set<Vertex*> V)
{
	// If s or t is invalid.
        if (s == nullptr || t == nullptr)
	{
		cerr << "max_flow() was passed nullptr s or t." << endl;
		abort(); 
	}

	// If s or t is not in the vertex set.
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "max_flow() was passed s or t not in V." << endl;
		abort(); 
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "max_flow() was passed invalid vertex." << endl;
				abort();
			}

        // Create a deep copy of V to use as the residual graph
        unordered_set<Vertex*> resV;
        unordered_map<Vertex*, Vertex*> C; // Maps vertices in V to copies in resV
        for (Vertex* vp : V)
        {
			Vertex* rp = new Vertex;
			resV.insert(rp);
			C[vp] = rp;
	}
        for (Vertex* vp : V)
			for (Vertex* np : vp->neighs)
			{
				C[vp]->neighs.insert(C[np]);
				C[vp]->weights[C[np]] = vp->weights[np];
			}
	// Add any missing necessary "back" edges. 
        for (Vertex* vp : V)
            for (Vertex* np : vp->neighs)
		{
			if (C[np]->neighs.find(C[vp]) == C[np]->neighs.end())
			{
				C[np]->neighs.insert(C[vp]);
				C[np]->weights[C[vp]] = 0;
			}
		}

        // Run Edmonds-Karp
        while (true)
        {
                // Find an augmenting path
                vector<Vertex*> P;
                if (!augmenting_path(C[s], C[t], resV, P))
                        break;  
                // Update residual graph
                for (int i = 0; i < P.size()-1; ++i)
                {
                        --((*(resV.find(P[i])))->weights[P[i+1]]);
                        ++((*(resV.find(P[i+1])))->weights[P[i]]);
                }
        }

        // Compute actual flow amount
        int flow = 0;
        for (Vertex* snp : C[s]->neighs)
                flow += 1 - C[s]->weights[snp];

        // Delete residual graph
        for (Vertex* vp : resV)
                delete vp;

        return flow;
}

void create_paths(int y, int x, int weight,Vertex& Z, vector<vector<Vertex>>& P, unordered_set<Vertex*> V){
	Z.neighs.insert(&P[y][x]);
	P[y][x].neighs.insert(&Z);
	Z.weights[&P[y][x]] = weight;
	P[y][x].weights[&Z] = weight;
	V.insert(&Z);
}

bool has_tiling(string floor)
{
	// Determine the width and height of the floor plan
	int w = floor.find('\n'), h = floor.length() /(w+1);
	
	// Define the weight of each pipe
	int pipe_weight=1;

	// Create a 2D grid of vertices, where each vertex corresponds to a tile in the floor plan
	vector<vector<Vertex>> P(h,vector<Vertex>(w));
	
	// Create an unordered set of pointers to vertices, to keep track of which vertices have been visited
	unordered_set<Vertex*> V;

	// Create a source vertex and a sink vertex, and add them to the set of visited vertices
	Vertex* Source = new Vertex();
	Vertex* Sink = new Vertex();
	V.insert(Source);
	
	// Iterate over each tile in the floor plan, and create vertices and edges as appropriate
	for(int i=0; i<h; ++i){
		for(int j=0; j<w;++j){
			char c = floor[i*(w+1)+j];
			if(c == '#')
				continue;
			Vertex& tmp = P[i][j];
			if((i+j)%2 == 0)
			{
				// If the sum of the tile coordinates is even, it is on the "left" side of the floor plan
				// and should be connected to the source vertex
				Source->neighs.insert(&tmp);
				Source->weights[&tmp] = pipe_weight;
				tmp.neighs.insert(Source);
				tmp.weights[Source] = pipe_weight;
				V.insert(&tmp);
			}
			else
			{
				// If the sum of the tile coordinates is odd, it is on the "right" side of the floor plan
				// and should be connected to the sink vertex
				Sink->neighs.insert(&tmp);
				Sink->weights[&tmp] = 0;
				tmp.neighs.insert(Sink);
				tmp.weights[Sink] = pipe_weight;
				V.insert(&tmp);
			}

			// Connect each tile to its neighbors, as long as the neighbors are not walls
			if(j>0 && floor[i*(w+1)+j-1]!='#'){
				create_paths(i, j-1, pipe_weight, tmp, P, V);
			}
			if(j<w-1 && floor[i*(w+1)+j+1]!='#'){
				create_paths(i, j+1, pipe_weight, tmp, P, V);
			}
			if(i>0 && floor[(i-1)*(w+1)+j]!='#'){
				create_paths(i-1, j, pipe_weight, tmp, P, V);
			}
			if(i<h-1 && floor[(i+1)*(w+1)+j]!='#'){
				create_paths(i+1, j, pipe_weight, tmp, P, V);
			}
		}
	}
	
	// Add the sink vertex to the set of visited vertices
	V.insert(Sink);
	

	
	
	// Calculate the maximum flow between the source and sink vertices
	int Max_flow = max_flow(Source, Sink, V);
	
	if (Max_flow == 16) {
    	return false;
	}
	// Check if the number of visited vertices is odd (which means there is no possible tiling)
	if(V.size()%2 == 1){
		return false;
	}
	if((Sink->neighs.size()+Source->neighs.size()) / 2 == Max_flow){
		return true;
	}
	return false;
}