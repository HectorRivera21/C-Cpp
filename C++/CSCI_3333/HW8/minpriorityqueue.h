#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap
using namespace std;
//Template Value
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
			// nothing is needed since its empty already
			H.clear();
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.//return the size of the vector heap
		

		int size(){return H.size();}

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
			//push our pair into the heap
			H.push_back(pair<T,int>{x, p});
			//track our index in the heap for the key 
			I[x] = H.size() - 1;
			//keep the heap property by bubble up method passing the index of the newly inserted item in the heap
			bubbleUp(H.size() - 1);
		}

		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		
		//return the string item in our vector pair in the index 0 being our front
		T front() {return H[0].first;}

		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{
			//if our vector is empty leave function
			if(H.empty())
				return;
			
			H[0]=H[H.size()-1];
			//remove from vector
			H.pop_back();
			//if the heap is not empty perform bubble-down operation on the new root

			bubbleDown(0);
		}

		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			//gain our index i for the heap from using the key to locate it inside our map
			//if the priority of the element is greater than the new priority
			//then assign the new priority
			
			int i = I[x];
    		H[i].second = new_p;
			//and bubble up
			bubbleUp(i);
			
						
		}
		bool Empty(){
			return H.size() == 0;
		}
	private:
		void bubbleUp(int i){
			// initilize the parent node index
			int parent = (i-1)/2;
			//if parent node is greater than current node in the heap
			while (i > 0 && H[(i-1)/2].second > H[i].second) {
        		// Swap the current node with its parent
				I[H[i].first] = (i-1)/2;
				I[H[(i-1)/2].first] = i;
				swap(H[i], H[(i-1)/2]);
				// Move up to the parent node
				i = (i-1)/2;
			}
		}
		void bubbleDown(int i){
			//calculate indices of left and right children
			int leftChild = 2 * i + 1;
			int rightChild = 2 * i + 2;
			int smallest = leftChild;
			if(H.size()<leftChild)
				return;
			else{
				if(H.size()>rightChild){
					if(H[leftChild].second>H[rightChild].second)
						smallest = H[leftChild].second > H[rightChild].second? rightChild:leftChild;
				}
				
				if(H[i].second > H[smallest].second){
					I[H[i].first] = smallest;
					I[H[smallest].first] = i;

					swap(H[i], H[smallest]);
					bubbleDown(smallest);
				}
			}

		}
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.
		
};

#endif 