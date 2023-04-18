#include <iostream>
#include <chrono>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <math.h>
#include <utility>
#include "minpriorityqueue.h"
#include "vertex.h"

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))

// void D(int n)
// {
//     int time = 0;
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < i * i; j++)
//             for (int k = 0; k < j*j; k++)
//                 time++;
//     // std::cout<<time<< std::endl;
// }
// void ncubed (int n){
//     int time = 0;
//     for(int i = 0; i < n;i++)
//         for(int j=0;j<n;j++)
//             for(int k = 0; k<n;k++)
//                 time++;
// //    std::cout<<time;
// }
// void showMap(std::unordered_map<std::string, int> &M){
//     std::cout<< "num items: "<< M.size()<<std::endl;
//     std::cout<<"num buckets: "<< M.bucket_count()<<std::endl;
//     std::cout<<"load factor: "<< (M.load_factor()*100)<<std::endl;
//     std:: cout<< "max load: "<< M.max_load_factor()<<std::endl;
// }

int rc[2];
unordered_map<string, Vertex*> Routes;
unordered_map<Vertex*, Vertex*> breadCrumbs;
MinPriorityQueue<Vertex*> Q;
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
                Q.push(tmp,0); 
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
                Q.push(tmp,(int)INFINITY);
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
                Q.push(tmp,1);
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
	
    solu = shortestPath(startEnd, maze);
    
    return solu;
}



int main(){	

	
	//MAZE HW7 STUFF
    srand(2023 + 's');
	string maze, soln;
	maze = "";
	maze += "##### #\n";
	maze += "#     #\n";
	maze += "# #####\n";
	soln = "";
	soln += "#####o#\n";
	soln += "#ooooo#\n";
	soln += "#o#####\n";
	test(solve(maze) == soln);
	
	//// MinQ STUFF ideas
    // MinPriorityQueue<int> Q1;
    // Q1.push(24, 3);
    // Q1.push(7, 23);
    // Q1.push(55, 37);
    // Q1.push(12, 6);
    // Q1.push(31, 15);
    // // 24 12 31 7 55
    // while(Q1.size() != 0){
    //     Q1.pop();
    // }



    //MAP IDEAS//
    // std:: vector<std::pair<std::string, int>> vHeap;
    // std::unordered_map<std::string, int> uMap;
    // uMap.max_load_factor(.10);
    // std::string* cool = new std::string[100000];
    // showMap(uMap);
    // vHeap.push_back({"lol", 23});
    // vHeap.push_back({"nice", 39});
    // vHeap.push_back({"too", 2});
    // vHeap.push_back({"hi", 20000});
    // vHeap.push_back({"boy", 52});
    // vHeap.push_back({"girl", 51});
    // vHeap.push_back({"er", 57});
    // vHeap.push_back({"wqe", 55});
    // vHeap.push_back({"we", 58}); 
    // vHeap.push_back({"ce", 59});
    // vHeap.push_back({"re", 5012});
    // vHeap.push_back({"lov", 5012});
    // vHeap.push_back({"e", 5012});
    // vHeap.push_back({"wwe", 5012});
    // vHeap.push_back({"gen", 5012});
    // auto compare = [](auto a, auto b){return a.second<b.second;};
    // std::sort(vHeap.begin(), vHeap.end(), compare);

    // for(int i = 0; i < vHeap.size();i++){
    //     uMap.insert({vHeap[i].first,i});
    // }

    // showMap(uMap);
    // for(int i = 0; i< vHeap.size();i++){
    //     uMap.erase(vHeap[i].first);
    // }
    // for(auto i: uMap){
    //     std::cout<< i.first<<i.second<<std::endl;
    // }


    // auto start = std::chrono::high_resolution_clock::now();
    // D(10);
    // auto finish = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = finish-start;
    // std::cout<< elapsed.count()<<std::endl;    

    // auto s = std::chrono::high_resolution_clock::now();
    // ncubed(10);
    // auto f = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<long double> nice = f-s;
    // std::cout<< nice.count();

    return 0;
}