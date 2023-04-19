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
                int weight = INT_MAX;

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
        void addPath(int rows, int cols, vector<int>& Real_RC, vector<string>& startEnd){
            string cords = to_string(rows)+","+to_string(cols);
            mazeRoutes[cords] = new Vertex(rows,cols);
            minQ.push(mazeRoutes[cords],mazeRoutes[cords]->weight);
            if (rows == 1 || cols == 1 || Real_RC[1] == cols || Real_RC[0] == rows){
                startEnd.push_back(cords);
            }
            if(vert_top(rows, cols)){
                string cordsTop = to_string(rows-1)+","+to_string(cols);
                //add edge to the vertex above it
                Vertex* Aptr = mazeRoutes[cords];//find object to a vertex create a pointer to it
                Vertex* Bptr = mazeRoutes[cordsTop];//find object to b vertex, create a pointer to it


                Aptr->neighs.push_back(Bptr);//add b to the list of a's neighbors
                Aptr->weight = 1;
                Aptr->weight_tracker[Bptr] = 1;
                Bptr->neighs.push_back(Aptr);//add a to the list of b's neighbors
                Bptr->weight = 1;
                Bptr->weight_tracker[Bptr] = 1;
            }
            if(vert_left(rows, cols)){
                string cordsLeft = to_string(rows)+","+to_string(cols-1);
                Vertex* Aptr = mazeRoutes[cords];//find object to a vertex create a pointer to it
                Vertex* Bptr = mazeRoutes[cordsLeft];//find object to b vertex, create a pointer to it


                Aptr->neighs.push_back(Bptr);//add b to the list of a's neighbors
                Aptr->weight = 1;
                Aptr->weight_tracker[Bptr] = 1;
                Bptr->neighs.push_back(Aptr);//add a to the list of b's neighbors
                Bptr->weight = 1;
                Bptr->weight_tracker[Bptr] = 1;
            }
        }
        string shortestPath(){
            
        }

        string mazeParser(string& maze){
            //holds location of starting and ending space
            vector<string>startEnd(2);
            //holds actual rows and cols
            vector<int> Real_RC(2);
            calc_rows_cols(maze, Real_RC);
            //Holds location of gates
            unordered_map<char, int> gates;
            //counters
            int rows = 1, cols = 0;
            //parser for maze
            for(int i = 0; i< maze.size()-1;i++){
                //check if space character
                if(maze[i] == ' '){
                    addPath(rows, cols, Real_RC, startEnd);
                }
                if(isdigit(maze[i])){
                    addPath(rows, cols, Real_RC, startEnd);
                    if(gates.find(maze[i])==gates.end()){
                        gates[maze[i]] = i;
                    }
                    else{
                        int weight = maze[i] - 48;
                        Vertex* Aptr = mazeRoutes[];
                        Vertex* Bptr = mazeRoutes[];

                        Aptr->neighs.push_back(Bptr);//add b to the list of a's neighbors
                        Aptr->weight = weight;
                        Aptr->weight_tracker[Bptr] = weight;
                        Bptr->neighs.push_back(Aptr);//add a to the list of b's neighbors
                        Bptr->weight = weight;
                        Bptr->weight_tracker[Bptr] = weight;

                        gates.erase(maze[i]);
                    }
                }

                //if newline character increment rows and reset cols else increment cols
                if(maze[i] == '\n'){rows++;cols = 0;}else{cols++;}
            }
        }
};
string solve(string maze){
    graph maze_solve;
    return maze_solve.mazeParser(maze);
}