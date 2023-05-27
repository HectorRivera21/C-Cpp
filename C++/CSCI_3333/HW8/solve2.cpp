#include "solve.h"
#include <vector>

class graph {
    private:
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
                //weight of vertex
                int weight= 900000000;

                // List of neighboring vertices
                vector<Vertex*> neighs;
                //map of vertices and their weights
                unordered_map<Vertex*, int> weight_tracker;
        };
        unordered_map<string, Vertex*> mazeRoutes;
        MinPriorityQueue<Vertex*> minPQ;
    public:

        void calc_rows_cols(string maze, vector<int>& A){
            A[0] = 0; A[1] = 0;
            for (int i = 0; i < maze.size() - 1; i++) {//find # of row and col
                if (maze[i] == '\n') {
                    A[1] = i+1;//find # of col
                    break;
                }
            }
            A[0] = (maze.size() / A[1] ) -1;//#of rows
            A[1] = A[1] - 2;//# of columns
        }
        //return true or false if in the border of the maze or not
        bool Border(string maze, int r, int c, vector<int> Real_RC){
            if (r == 0 || c == 0 || r == Real_RC[0] || c == Real_RC[1]) {
                return true;
            }
            return false;
        }
        //return true or false if the vertex is on top 
        bool vert_top(int r, int c){
            string key = to_string(r-1) + "," + to_string(c);
            if (mazeRoutes.find(key) == mazeRoutes.end()) {//not a vertex
                return false;
            }
            return true;
        }
        //return true or false if the vertex is on the left
        bool vert_left(int r, int c){
            string key = to_string(r) + "," + to_string(c-1);
            if (mazeRoutes.find(key) == mazeRoutes.end()) {//not a vertex
                return false;
            }
            return true;
        }
        void add_directed_edged(string a, string b, int weight){
            Vertex * Aptr = mazeRoutes[a];//find object to a vertex create a pointer to it
	        Vertex * Bptr = mazeRoutes[b];//find object to b vertex, create a pointer to it
            //push back the neighbors the vertex Bptr
            Aptr->neighs.push_back(Bptr);
            //track the weight of the Bptr
            Aptr->weight_tracker[Bptr] = weight;
        }
        void Edge(string a, string b, int weight){
            //add a directed edge from a to b 
            add_directed_edged(a,b, weight);
            //add a directed edge from b to a 
            add_directed_edged(b,a, weight);
        }
        void add_vertex_path(int rows, int cols,vector<int> Real_RC, vector<string>& startEnd){
            string cords = to_string(rows)+","+to_string(cols);
            if (mazeRoutes.find(cords) == mazeRoutes.end()) {
                mazeRoutes[cords] = new Vertex(rows,cols);
                minPQ.push(mazeRoutes[cords],mazeRoutes[cords]->weight);
                int weight = 1;
                if (rows == 0 || cols == 0 || Real_RC[1] == cols || Real_RC[0] == rows){
                    startEnd.push_back(cords);
                }

                //check if there is a vertex above 
                //the current one and add an edge to it if it exists
                if (rows > 0) {
                    string cordsTop = to_string(rows-1) + "," + to_string(cols);
                    if (mazeRoutes.find(cordsTop) != mazeRoutes.end()) {
                        Edge(cords, cordsTop, weight);
                    }
                }

                //check if there is a vertex to 
                //the left of the current one and add an edge to it if it exists
                if (cols > 0) {
                    string cordsLeft = to_string(rows) + "," + to_string(cols-1);
                    if (mazeRoutes.find(cordsLeft) != mazeRoutes.end()) {
                        Edge(cords, cordsLeft, weight);
                    }
                }

                //check if there is a vertex below 
                //the current one and add an edge to it if it exists and is a vertical neighbor
                if (rows < Real_RC[0]) {
                    string cordsBottom = to_string(rows + 1) + "," + to_string(cols);
                    if (mazeRoutes.find(cordsBottom) != mazeRoutes.end() && vert_top(rows + 1, cols)) {
                        Edge(cords, cordsBottom, weight);
                    }
                }

                //check if there is a vertex to the right of 
                //the current one and add an edge to it if it exists and is a horizontal neighbor
                if (cols < Real_RC[1]) {
                    string cordsRight = to_string(rows) + "," + to_string(cols + 1);
                    if (mazeRoutes.find(cordsRight) != mazeRoutes.end() && vert_left(rows, cols + 1)) {
                        Edge(cords, cordsRight, weight);
                    }
                }
            }
        }
        void Dikstras(unordered_map <Vertex*, Vertex*>& breadcrumbs){
            unordered_set <Vertex*> marked;
            while (!minPQ.Empty())
            {
                Vertex* x = minPQ.front();
                minPQ.pop();
                marked.insert(x);
                for(Vertex* y : x->neighs){
                    if(marked.find(y) == marked.end()){
                        relax(x,y,breadcrumbs);
                    }
                }
            }
        }
        void relax(Vertex* &x, Vertex* &y, unordered_map <Vertex*, Vertex*>& breadcrumbs){
            // get the weight of X
            int Xw = x->weight;
            //the weight of the edge from x to y 
            int Xe = x->weight_tracker[y];
            // add to the total 
            int total = Xw + Xe;
            //if the weight of y is greater than total 
            if(y->weight > total){
                //decrease the weight in the minQ
                minPQ.decrease_key(y, total);
                //set the weight for total 
                y->weight = total;
                // add the path of x to y 
                breadcrumbs[y] = x;
            }
        }
        string shortestPath(vector<string>& startEnd,vector<int>& Real_RC ,string maze){
            //starting vertex 
            Vertex* S = mazeRoutes[startEnd[0]];
            //destination vertex
            Vertex* D = mazeRoutes[startEnd[1]];
            string solu = maze;
            //set weight for starting vertex weight to zero
            S->weight = 0;
            //decrease the weight in the minQ
            minPQ.decrease_key(S, S->weight);
            //unordered map of vertex pointers that value to other vertex pointers
            unordered_map<Vertex*, Vertex*> breadCrumbs;
            //run dikstras algorithm to return the breadcrumbs
            Dikstras(breadCrumbs);
            //if the destination is not in the breadcrumbs then add it
            if(breadCrumbs.find(D)==breadCrumbs.end()){
                D->weight = D->neighs[0]->weight+1;
                breadCrumbs[D] = D->neighs[0];
            }
            //set curr to the destination
            Vertex* curr = D;
            //while curr is not the start
            while(curr!=S){
                //calc the location for the path
                solu[curr->row*(Real_RC[1]+2)+curr->col] = 'o';
                //switch the vertex for the next one
                curr = breadCrumbs[curr];
            }
            //calc the location for the starting vertex
            solu[(S->row*(Real_RC[1]+2))+S->col] = 'o';
            //return the solution
            return solu;
        }

        string mazeParser(string& maze){
            //holds location of starting and ending space
            vector<string>startEnd;
            //holds actual rows and cols
            vector<int> Real_RC(2);
            calc_rows_cols(maze, Real_RC);
            //Holds location of gates
            unordered_map<char, string> gates;
            //counters
            int rows = 0, cols = 0;
            //parser for maze
            for(int i = 0; i< maze.size()-1;i++){
                //check if space character
                if(maze[i] == ' '){
                    //create path to vertex
                    add_vertex_path(rows, cols, Real_RC, startEnd);
                }
                if(maze[i]>=48 && maze[i]<=57){
                    //add path to the vertex
                    add_vertex_path(rows, cols, Real_RC, startEnd);
                    //add the gate if not found
                    if(gates.find(maze[i])==gates.end()){
                        //create cords for the gates and add them to map
                        gates[maze[i]] = to_string(rows)+","+to_string(cols);
                    }
                    else{
                        //cords for the vertex saved
                        string cords = to_string(rows)+","+to_string(cols);
                        //calculate the weight for the portals
                        int weight = maze[i] - 48;
                        //create the edge for the vertex gate with its weight
                        Edge(cords, gates[maze[i]], weight);
                        //erase the gates from the maptracker;
                        gates.erase(maze[i]);
                    }
                }

                //if newline character increment rows and reset cols else increment cols
                if(maze[i] == '\n'){rows++;cols = 0;}else{cols++;}
            }
            //return the shortest path
            return shortestPath(startEnd, Real_RC, maze);
        }
};
// This function takes a string representing a maze and returns a solution to the maze.
string solve(string maze){
    
    // Create a graph object to represent the maze.
    graph maze_solve;
    // Parse the maze string and create a graph representation
    
    // the maze as input and returns a graph representation of the maze
    // the graph representation can then be used to solve the maze
    return maze_solve.mazeParser(maze);
}