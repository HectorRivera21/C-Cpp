#include "tiling.h"
#include "vertex.h"
#include <algorithm>

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
bool has_tiling(string floor)
{
    int n = floor.size();
  if (n % 2 == 1) {
    return false;
  }
  int total_cells = n * n / 4;
  int target_cells = total_cells - count(floor.begin(), floor.end(), 'B');

  Vertex* source = new Vertex;
  Vertex* sink = new Vertex;
  unordered_set<Vertex*> V = {source, sink};

  vector<vector<Vertex*>> grid(n/2, vector<Vertex*>(n/2));
  for (int i = 0; i < n/2; i++) {
    for (int j = 0; j < n/2; j++) {
      Vertex* v = new Vertex;
      grid[i][j] = v;
      V.insert(v);
      if ((i+j) % 2 == 0) {
        // white cell
        v->weights[sink] = 1;
        for (int di : {-1, 1}) {
          for (int dj : {-1, 1}) {
            int ni = i + di;
            int nj = j + dj;
            if (ni >= 0 && ni < n/2 && nj >= 0 && nj < n/2) {
              Vertex* u = grid[ni][nj];
              v->neighs.insert(u);
              v->weights[u] = 1;
            }
          }
        }
      } else {
        // black cell
        v->weights[source] = 1;
        target_cells--;
      }
    }
  }

  // Check if we already know the answer
  if (target_cells < 0) {
    return false;
  }

  // Add edges from source to white cells and from black cells to sink
  for (auto& row : grid) {
    for (Vertex* v : row) {
      if (v->weights.find(sink) != v->weights.end()) {
        continue;
      }
      if (v->weights.find(source) != v->weights.end()) {
        continue;
      }
      if ((v->neighs.size() % 2) == 0) {
        // even-degree vertex
        v->weights[source] = v->weights[sink] = v->neighs.size() / 2;
      } else {
        // odd-degree vertex
        v->weights[source] = (v->neighs.size() - 1) / 2;
        v->weights[sink] = (v->neighs.size() + 1) / 2;
      }
    }
  }

  // Run max flow and check if it equals total_cells
  int flow = max_flow(source, sink, V);
  return flow == total_cells;
}