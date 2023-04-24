#include <iostream>
#include <queue>
#include "minpriorityqueue.h"
#include "solve.h"

using namespace std;

class directedGraph {
private:
	class vertex {
	public:
		// for the specific location of the vertex
		int row;
		int col;
		// location of the ertex within the string
		int loc;
		// weight of the vertex
		int edgeWeight = 900000000;
		//vector to store the neighbors of the vertex
		vector <vertex*> neighbors;
		// unordered map that keeps track of the weight of the edges
		unordered_map <vertex*, int> neigh;
		// constructor
		vertex(int r, int c, int l) {

			row = r;
			col = c;
			loc = l;
		}
	};
	unordered_map <int, vertex*> vertexSet;
	MinPriorityQueue<vertex*> Q1;
public:

	// adds a new vertex to the graph
	void addVertex(int w, int e, int place) {
		// adding the the location of the vertex set
		vertexSet[place] = new vertex(w, e, place);
		Q1.push(vertexSet[place], vertexSet[place]->edgeWeight);
	}

	void addDirectedEdge(int a, int b, int weight) {
		// making pointers for the locations of the vertex
		vertex* aVert = vertexSet.at(a);
		vertex* bVert = vertexSet.at(b);
		// pushing them into a vector to hold all the edges
		aVert->neighbors.push_back(bVert);
		aVert->neigh[bVert] = weight;
	}

	void addBasicEdge(int a, int b, int weight) {

		addDirectedEdge(a, b, weight);
		addDirectedEdge(b, a, weight);
	}

	string shrotestPath(int s, int d, string maze, int tru) {
		// creates pointers to the source and destination
		vertex* sVert = vertexSet[s];
		vertex* dVert = vertexSet[d];
		// make the source weight equal to 0
		sVert->edgeWeight = 0;
		//This makes the Source weight = 0 in the Min heap
		Q1.decrease_key(sVert, sVert->edgeWeight);
		// creates a hashmap that will leave the breadcrumbs
		unordered_map <vertex*, vertex*> breadcrumbs;
		// will make a copy of the maze string
		string path = maze;
		// the function call that will obtain the shortest path from source to every vertex in the graph
		breathFirstSearch(sVert, breadcrumbs);
		// makes the current pointer equal to the destination
		vertex* current = dVert;
		// traces breadcrumbs back from the destination
		while (current != sVert) {
			// puts a o in the string for the shortest path
			path[current->loc] = 'o';
			current = breadcrumbs[current];
		}
		// set start 'o'
		path[current->loc] = 'o';
		return path;
	}

	void breathFirstSearch(vertex* f, unordered_map <vertex*, vertex*>& breadcrumbs) {
		// this will hold all the vertexs that we have visited
		unordered_set < vertex*> marked;

		while (!Q1.size() == 0) {
			// makes a pointer to the front of the queue
			vertex* x = Q1.front();
			marked.insert(x);
			//This extracts the minumum value from the heap
			Q1.pop();
			// this is to visit all the unvisted neighbors of x
			for (int i = 0; i < x->neighbors.size(); i++) {
				vertex* y = x->neighbors[i];
				// check if the neighbor is in the visited set
				if (marked.find(y) == marked.end()) {
					// relaxs the neighbors 
					relax(x, y,breadcrumbs);
				}
			}
		}
	}

	void relax(vertex* &x, vertex* &y, unordered_map <vertex*, vertex*>& breadcrumbs) {
		// this is the weight that it took to get to this vertex
		int og = x->edgeWeight;
		// this is the weight of the edge
		int edge = x->neigh[y];
		// total distance that is needed to travel from one vertex to another
		int total = og + edge;
		// if the total is less than the current weight than it replaces it
		if (y->edgeWeight > total) {
			// this decreases the key
			Q1.decrease_key(y, total);
			// this changes the edgeweight of the vertex
			y->edgeWeight = total;
			// this adds the vertex to the breadcrumbs
			breadcrumbs[y] = x;
		}
	}

	int rowValue(string maze) {
		int actualRow = 1;
		for (int j = 0; j < maze.size() - 1; j++) {
			if (maze[j] == '\n') {
				actualRow++;
			}
		}
		return actualRow;
	}

	void addEdges(int row, int column, int i, int AC) {
		// finds the values of the vertex above and to the left
		int v1 = findIndex(row, column - 1, i, AC, row);
		int v2 = findIndex(row - 1, column, i, AC, row);
		// initatiles the weight of non weighted edges
		int weight = 1;
		if (vertexSet.find(v1) == vertexSet.end()) {}
		else {
			addBasicEdge(v1, i, weight);
		}
		if (vertexSet.find(v2) == vertexSet.end()) {}
		else {
			addBasicEdge(v2, i, weight);
		}
	}

	int findIndex(int row, int col, int i, int AC, int og) {
		int value = 0;

		if (row < 1 || col < 1) {
			return value = -1;
		}
		else if (row == og) {
			return value = i - 1;
		}
		else {
			return value = ((row - 1) * AC) + col + (row - 2);
		}
	}

	string stringTravel(string& maze) {
		// will hold the openings in the maze
		vector <int> openings;
		// a unordered map to hold all the positions of the gates
		unordered_map <char, int> gates;
		// these are all counters
		int row = 1;
		int column = 0;
		int acutalColumns = 1;
		int actualRow = rowValue(maze);

		// this is to go through the entire string
		for (int i = 0; i < maze.size() - 1; i++) {
			column++;
			if (maze[i] == ' ') {
				addVertex(row, column, i);
				if (row == 1 || column == 1 || acutalColumns == column || actualRow == row) {
					// pushes the openings into the vector
					openings.push_back(i);
				}
				addEdges(row, column, i, acutalColumns);
			}
			// to check if the location has a gate 
			if (maze[i] >= 48 && maze[i] <= 57) {
				addVertex(row, column, i);
				addEdges(row, column, i, acutalColumns);
				if (row == 1 || column == 1 || acutalColumns == column || actualRow == row) {
					// pushes the openings into the vector
					openings.push_back(i);
				}
				// if the gate isn't within the hash table then it will add it to it
				if (gates.find(maze[i]) == gates.end()) {
					gates[maze[i]] = i;
				}
				// if the gate already exsits 
				else {
					int weight = maze[i] - 48;
					// adds a gate edge
					addBasicEdge(i, gates[maze[i]], weight);
					// erases the gate from the unordered map
					gates.erase(maze[i]);
				}
			}
			// we will know how many columns there is in the maze
			if (maze[i] == '\n') {
				row++;
				acutalColumns = column - 1;
				column = 0;
			}

		}

		int open1 = openings[0];
		int open2 = openings[1];

		string solution = shrotestPath(open1, open2, maze, acutalColumns);
		return solution;
	}
};

string solve(string maze) {
	directedGraph stringTravel;
	return stringTravel.stringTravel(maze);
}
