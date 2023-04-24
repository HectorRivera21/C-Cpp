
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Vertex
{
        public:
                // Set of vertex's neighbors.
                unordered_set<Vertex*> neighs;

                // Map of neighbors to weights.
                // If vertex is part of an unweighted graph, then unused.
                unordered_map<Vertex*, int> weights;
};

