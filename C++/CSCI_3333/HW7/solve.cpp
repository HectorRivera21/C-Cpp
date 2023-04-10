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
	for (int i = 0; i < maze.size() - 1; i++) {//find #of row and col
		if (maze[i] == '\n') {
			rc[1] = i+1;//find # of col
			break;
		}
	}
	rc[0] = (maze.size() / rc[1] ) -1;//#of rows
	rc[1] = rc[1] - 2;//# of columns
}
void addEdge(string a, string b)
{
	Vertex * Aptr = Routes[a];//find object to a vertex create a pointer to it
	Vertex * Bptr = Routes[b];

	Aptr->neighs.push_back(Bptr);//add b to the list of a's neighbors
	Bptr->neighs.push_back(Aptr);//add a to the list of b's neighbors
}
bool inBorder(string maze, int r, int c) {
	if (r == 0 || c == 0 || r == rc[0] || c == rc[1]) {
		return true;
	}
	return false;
}
bool checkTop(int r, int c) {
	string key = to_string(r-1) + "," + to_string(c);
	if (Routes.find(key) == Routes.end()) {//not a vertex
		return false;
	}
	return true;
}

bool checkLeft(int r, int c) {
	string key = to_string(r) + "," + to_string(c-1);
	if (Routes.find(key) == Routes.end()) {//not a vertex
		return false;
	}
	return true;
}
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

string shortestPath(string* startEnd, string maze){
    Vertex* S = Routes[startEnd[0]];
    Vertex* D = Routes[startEnd[1]];

    BFS(startEnd[0]);

    Vertex* curr = D;

    while(curr != S){
        maze[(curr->row*(rc[1]+2))+curr->col] = 'o';
        curr = breadCrumbs[curr];
    }
    maze[(S->row*(rc[1]+2))+S->col] = 'o';
    return maze;
}
string solve(string maze){
    Routes.clear();
	breadCrumbs.clear();
    findRowCol(maze);
    int rows = 0, cols = 0, border = 0;
    string solu=""; 
    string startEnd[2]; startEnd[0] = "", startEnd[1] ="";
    for(auto x: maze){
        if(x == ' '){
            if (inBorder(maze, rows, cols) && border==0){
                Vertex* tmp = new Vertex(rows,cols);
                string cords = to_string(rows)+","+to_string(cols);
                Routes[cords] = tmp;
                startEnd[0] = cords; 
                if(checkTop(rows, cols)){
                    string cordsTop = to_string(rows-1)+","+to_string(cols);
                    addEdge(cords, cordsTop);
                }
                if(checkLeft(rows, cols)){
                    string cordsLeft = to_string(rows)+","+to_string(cols-1);
                    addEdge(cords, cordsLeft);
                }
                border++;
            }else if(inBorder(maze, rows, cols) && border == 1){
                Vertex* tmp = new Vertex(rows,cols);
                string cords = to_string(rows)+","+to_string(cols); 
                Routes[cords] = tmp;
                startEnd[1] = cords;
                if(checkTop(rows, cols)){
                    string cordsTop = to_string(rows-1)+","+to_string(cols);
                    addEdge(cords, cordsTop);
                }
                if(checkLeft(rows, cols)){
                    string cordsLeft = to_string(rows)+","+to_string(cols-1);
                    addEdge(cords, cordsLeft);
                }
            }
            else{
                Vertex* tmp = new Vertex(rows,cols);
                string cords = to_string(rows)+","+to_string(cols);
                Routes[cords] = tmp;
                if(checkTop(rows, cols)){
                    string cordsTop = to_string(rows-1)+","+to_string(cols);
                    addEdge(cords, cordsTop);
                }
                if(checkLeft(rows, cols)){
                    string cordsLeft = to_string(rows)+","+to_string(cols-1);
                    addEdge(cords, cordsLeft);
                }
            }
        }
        if(x == '\n'){rows++;cols = 0;}else{cols++;}
    }
    return shortestPath(startEnd, maze);
}