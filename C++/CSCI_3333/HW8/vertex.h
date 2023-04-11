
#include <vector>

using namespace std;

// A helper class implementing a vertex in 
// an adjacency-list-based graph.
class Vertex
{
        public:
                Vertex(int r, int c)
                {
                        row = r;
                        col = c;
                }

                // Corresponding row and column location in maze
                int row;
                int col;

                // List of neighboring vertices
                vector< pair<Vertex*, int> > neighs;
};

