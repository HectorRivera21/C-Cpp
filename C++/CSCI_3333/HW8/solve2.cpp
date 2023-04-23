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
                unordered_map<Vertex*, int> weight_tracker;
        };
        unordered_map<string, Vertex*> mazeRoutes;
        MinPriorityQueue<Vertex*> minQ;
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
        bool Border(string maze, int r, int c, vector<int> Real_RC){
            if (r == 0 || c == 0 || r == Real_RC[0] || c == Real_RC[1]) {
                return true;
            }
            return false;
        }
        bool vert_top(int r, int c){
            string key = to_string(r-1) + "," + to_string(c);
            if (mazeRoutes.find(key) == mazeRoutes.end()) {//not a vertex
                return false;
            }
            return true;
        }
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

            Aptr->neighs.push_back(Bptr);
            Aptr->weight_tracker[Bptr] = weight;
        }
        void Edge(string a, string b, int weight){
            add_directed_edged(a,b, weight);
            add_directed_edged(b,a, weight);
        }

        void add_vertex_path(int rows, int cols,vector<int> Real_RC, vector<string>& startEnd){
            string cords = to_string(rows)+","+to_string(cols);
            if (mazeRoutes.find(cords) == mazeRoutes.end()) {
                mazeRoutes[cords] = new Vertex(rows,cols);
                minQ.push(mazeRoutes[cords],mazeRoutes[cords]->weight);
                int weight = 1;
                if (rows == 0 || cols == 0 || Real_RC[1] == cols || Real_RC[0] == rows){
                    startEnd.push_back(cords);
                }
                if (rows > 0) {
                    string cordsTop = to_string(rows-1) + "," + to_string(cols);
                    if (mazeRoutes.find(cordsTop) != mazeRoutes.end()) {
                        //add edge to the vertex above it
                        Edge(cords, cordsTop, weight);
                    }
                }
                if (cols > 0) {
                    string cordsLeft = to_string(rows) + "," + to_string(cols-1);
                    if (mazeRoutes.find(cordsLeft) != mazeRoutes.end()) {
                        //add edge to the vertex to the left of it
                        Edge(cords, cordsLeft, weight);
                    }
                }
                if (rows < Real_RC[0]) {
                    string cordsBottom = to_string(rows + 1) + "," + to_string(cols);
                    if (mazeRoutes.find(cordsBottom) != mazeRoutes.end() && vert_top(rows + 1, cols)) {
                        //add edge to the vertex below it
                        Edge(cords, cordsBottom, weight);
                    }
                }
                if (cols < Real_RC[1]) {
                    string cordsRight = to_string(rows) + "," + to_string(cols + 1);
                    if (mazeRoutes.find(cordsRight) != mazeRoutes.end() && vert_left(rows, cols + 1)) {
                        //add edge to the vertex to the right of it
                        Edge(cords, cordsRight, weight);
                    }
                }
            }
        }
        void Dikstras(Vertex* S, Vertex* D,unordered_map <Vertex*, Vertex*>& breadcrumbs){
            unordered_set <Vertex*> marked;
            while (!minQ.Empty())
            {
                Vertex* x = minQ.front();
                minQ.pop();
                if(x == D){
                    return;
                }
                marked.insert(x);
                for(Vertex* y : x->neighs){
                    if(marked.find(y) == marked.end()){
                        relax(x,y,breadcrumbs);
                    }
                }
            }
        }
        void relax(Vertex* &x, Vertex* &y, unordered_map <Vertex*, Vertex*>& breadcrumbs){
            int Xw = x->weight;
            int Xe = x->weight_tracker[y];
            int total = Xw + Xe;
            if(y->weight > total){
                minQ.decrease_key(y, total);
                
                y->weight = total;
                
                breadcrumbs[y] = x;
            }
        }
        string shortestPath(vector<string>& startEnd,vector<int>& Real_RC ,string maze){
            Vertex* S = mazeRoutes[startEnd[0]];
            Vertex* D = mazeRoutes[startEnd[1]];
            string solu = maze;
            S->weight = 0;
            minQ.decrease_key(S, S->weight);
            unordered_map<Vertex*, Vertex*> breadCrumbs;
            Dikstras(S,D,breadCrumbs);
            if(breadCrumbs.find(D)==breadCrumbs.end()){
                D->weight = D->neighs[0]->weight+1;
                breadCrumbs[D] = D->neighs[0];
            }
            Vertex* curr = D;
            while(curr!=S){
                solu[curr->row*(Real_RC[1]+2)+curr->col] = 'o';
                curr = breadCrumbs[curr];
            }
            solu[(S->row*(Real_RC[1]+2))+S->col] = 'o';
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
                    add_vertex_path(rows, cols, Real_RC, startEnd);
                }
                if(maze[i]>=48 && maze[i]<=57){
                    add_vertex_path(rows, cols, Real_RC, startEnd);
                    if(gates.find(maze[i])==gates.end()){
                        gates[maze[i]] = to_string(rows)+","+to_string(cols);
                    }
                    else{
                        string cords = to_string(rows)+","+to_string(cols);
                        int weight = maze[i] - 48;
                        Edge(cords, gates[maze[i]], weight);
                        gates.erase(maze[i]);
                    }
                }

                //if newline character increment rows and reset cols else increment cols
                if(maze[i] == '\n'){rows++;cols = 0;}else{cols++;}
            }
            return shortestPath(startEnd, Real_RC, maze);
        }
};
string solve(string maze){
    graph maze_solve;
    return maze_solve.mazeParser(maze);
}