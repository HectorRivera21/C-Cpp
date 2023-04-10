#include "solve.h"
#include "vertex.h"
string solve(string maze){
    int rows, cols = 0;
    unordered_map<int, Vertex*> g;
    unordered_set<int> s;
    for(auto x: maze){
        if(x == '\n'){
            rows++;
        }
        if(x == ' '){
            cols++;
            Vertex* tmp = new Vertex(rows,cols);
            g[rows*100+cols] = tmp;
            s.insert(rows*100+cols);
        }
        cols++;
    }
}