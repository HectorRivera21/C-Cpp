#include "solve.h"
#include "vertex.h"
//hold values for rows and cols
int rc[2];
// holds the cords and vertexes
unordered_map<string, Vertex*> Routes;
// our breadcrumbs to follow
unordered_map<Vertex*, Vertex*> breadCrumbs;
void findRowCol(string maze) {
	rc[0] = 0; rc[1] = 0;
	for (int i = 0; i < maze.size() - 1; i++) {//find # of row and col
		if (maze[i] == '\n') {
			rc[1] = i+1;//find # of col
			break;
		}
	}
	rc[0] = (maze.size() / rc[1] ) -1;//#of rows
	rc[1] = rc[1] - 2;//# of columns
}
// add an edge between vertices a and b
void addEdge(string a, string b)
{
	Vertex * Aptr = Routes[a];//find object to a vertex create a pointer to it
	Vertex * Bptr = Routes[b];//find object to b vertex, create a pointer to it

	Aptr->neighs.push_back(Bptr);//add b to the list of a's neighbors
	Bptr->neighs.push_back(Aptr);//add a to the list of b's neighbors
}
// check if a coordinate is on the border of the maze
bool inBorder(string maze, int r, int c) {
	if (r == 0 || c == 0 || r == rc[0] || c == rc[1]) {
		return true;
	}
	return false;
}
// check if the top coordinate is a vertex
bool checkTop(int r, int c) {
	string key = to_string(r-1) + "," + to_string(c);
	if (Routes.find(key) == Routes.end()) {//not a vertex
		return false;
	}
	return true;
}
// check if the left coordinate is a vertex
bool checkLeft(int r, int c) {
	string key = to_string(r) + "," + to_string(c-1);
	if (Routes.find(key) == Routes.end()) {//not a vertex
		return false;
	}
	return true;
}
// perform a bfs on the maze, starting at vertex s
void BFS(string s){
    queue<Vertex*>Q;
    unordered_set<Vertex*> marked;
    
    Vertex* S = Routes[s];

    marked.insert(S);
    Q.push(S);

    while(!Q.empty()){
        Vertex* tmp = Q.front();
        Q.pop();

        for(int i = 0; i< tmp->neighs.size();i++){
            Vertex* y = tmp->neighs[i];
            if(marked.find(y) == marked.end()){
                marked.insert(y);
                Q.push(y);
                breadCrumbs[y] = tmp;
            }
        }
    }

}
// this function takes a maze string and a startEnd 
// array which contains the start and end coordinates
string shortestPath(string* startEnd, string maze){
    // set the start and destination vertex
    Vertex* S = Routes[startEnd[0]];
    Vertex* D = Routes[startEnd[1]];
    // perform bfs to calculate shortest path from start to all other vertices
    BFS(startEnd[0]);
    // shortest path from destination to start using breadCrumbs map
    Vertex* curr = D;
    while(curr != S){
        // mark the path with 'o'
        maze[(curr->row*(rc[1]+2))+curr->col] = 'o';
        curr = breadCrumbs[curr];
    }
    // mark the starting point as well
    maze[(S->row*(rc[1]+2))+S->col] = 'o';
    // return updated maze
    return maze;
}
// takes a maze string and finds the shortest path from the start to the end
string solve(string maze){
    //clear our graph and map
    Routes.clear();
	breadCrumbs.clear();
    // find cols and rows in maze
    findRowCol(maze);
    int rows = 0, cols = 0, border = 0;
    string solu="";
    string startEnd[2]; startEnd[0] = "", startEnd[1] ="";
    // loop through maze
    for(auto x: maze){
        //check if space character
        if(x == ' '){
            //check if in the top or left border
            if (inBorder(maze, rows, cols) && border==0){
                //create new vertex save cords in string and input to our map
                Vertex* tmp = new Vertex(rows,cols);
                string cords = to_string(rows)+","+to_string(cols);
                Routes[cords] = tmp;
                //starting vertex
                startEnd[0] = cords; 
                if(checkTop(rows, cols)){
                    string cordsTop = to_string(rows-1)+","+to_string(cols);
                    //add edge to the vertex above it
                    addEdge(cords, cordsTop);
                }
                if(checkLeft(rows, cols)){
                    string cordsLeft = to_string(rows)+","+to_string(cols-1);
                    //add edge to the vertex above it
                    addEdge(cords, cordsLeft);
                }
                border++;//increment the border count
            }
            //if the vertex is on the bottom or right border it is the destination
            else if(inBorder(maze, rows, cols) && border == 1){
                //create new vertex save cords in string and input to our map
                Vertex* tmp = new Vertex(rows,cols);
                string cords = to_string(rows)+","+to_string(cols); 
                Routes[cords] = tmp;
                //store the destination coordinates
                startEnd[1] = cords;
                if(checkTop(rows, cols)){
                    string cordsTop = to_string(rows-1)+","+to_string(cols);
                    //add edge to the vertex above it
                    addEdge(cords, cordsTop);
                }
                if(checkLeft(rows, cols)){
                    string cordsLeft = to_string(rows)+","+to_string(cols-1);
                    //add edge to the vertex above it
                    addEdge(cords, cordsLeft);
                }
            }
            //if it is not on the border create a new vertex and add edges to any adjacent vertices
            else{
                Vertex* tmp = new Vertex(rows,cols);
                string cords = to_string(rows)+","+to_string(cols);
                Routes[cords] = tmp;//add the new vertex to the map of all
                //check if the vertex above the current one is in the border and add an edge if so 
                if(checkTop(rows, cols)){
                    string cordsTop = to_string(rows-1)+","+to_string(cols);
                    addEdge(cords, cordsTop);
                }
                //check if the vertex to the left of the current one is in the border and add an edge if so
                if(checkLeft(rows, cols)){
                    string cordsLeft = to_string(rows)+","+to_string(cols-1);
                    addEdge(cords, cordsLeft);
                }
            }
        }
        //if newline character increment rows and reset cols else increment cols
        if(x == '\n'){rows++;cols = 0;}else{cols++;}
    }
    //find and return the shortest path from start to end
    return shortestPath(startEnd, maze);
}