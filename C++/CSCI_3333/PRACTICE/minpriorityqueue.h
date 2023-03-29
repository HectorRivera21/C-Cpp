#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
	// (they are average case, but not worst-case).

	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
			// TODO
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size()
		{return H.size();}	

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
			// TODO
			H.push_back({x, p});
			I[x] = H.size() - 1;
			bubbleUp(H.size() - 1);
		}

		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front(){return H[0].first;}

		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{
			if(H.empty()){
				return;
			}
			// TODO	
			swap(H.front(), H.back());
			I.erase(H[0].first);
			cout << H.back().first << endl;
			H.pop_back();
			if(!H.empty()){
				bubbleDown(0);
			}
		}

		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			// TODO
			int i = I[x];
			if(H[i].second > new_p){
				H[i].second = new_p;
				bubbleUp(i);
			}
			
		}

	private:
		void bubbleUp(int i){
			if(i == 0)
				return;
			int parent = (i-1)/2;
			if(H[parent].second> H[i].second){
				swap(H[parent], H[i]);
				I[H[parent].first] = parent;
				I[H[i].first] = i;
				bubbleUp(parent);
			}
		}
		void bubbleDown(int i){
			int leftChild = 2 * i + 1;
			int rightChild = 2 * i + 2;
			int smallest = i;
			if(leftChild < H.size() && H[leftChild].second < H[smallest].second){
				smallest = leftChild;
			}
			if(rightChild < H.size() && H[rightChild].second < H[smallest].second){
				smallest = rightChild;
			}
			if(smallest != i){
				swap(H[i], H[smallest]);
				I[H[i].first] = i;
				I[H[smallest].first] = smallest;
				bubbleDown(smallest);
			}
		}
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.
		
};

#endif 