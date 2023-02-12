template <class T>
class priorityQueueLL
{
private:
	class Node
	{	
		public:
			//put what you need here..
			T value;
			Node* next;
			Node(T n)
			{
				value = n;
				next = NULL;
			}
	};
	Node* head;
	//add what you wish here
	

public:

	priorityQueueLL()
	{head = NULL;}

	~priorityQueueLL()
	{
        // free up memory by deleting all nodes
		//O(n) since we need to delete all nodes so we need to traverse though the priorityQueueLL
		while(head!=NULL)
		{
			Node* temp = head;
			head = head->next;
			delete(temp);
		}
	}

	//return true if empty, false if not
	// O(1) since were returning true or false if head is NULL
	bool empty()
	{
		return head == NULL;
	}

	//add item
	/*
		the running time of the insert function in a is O(n) in the worst case scenario
		this is because in the worst case, the function needs to traverse the entire
		linked list to find the correct position for the new node, resulting in a linear time complexity.
	*/
	void insert(T x)
	{
		Node* temp = new Node(x);
		if(head == NULL || head->value > x)
		{
            // If the head is NULL or the value of the 
            // new node is smaller than the head,
            // make the new node the head
			temp->next = head;
			head = temp;
		}
		else
		{
            // Else, traverse the list to find 
            // the correct position for the new node
			Node* copy = head;
			Node* p = NULL;
			while(copy != NULL && copy->value < x)
			{
				p = copy;
				copy= copy->next;
			}

			// Insert the node at the correct position
            if(p == NULL){
                temp->next = head;
                head = temp;
            }else{
                p->next = temp;
                temp->next = copy;
            }
		}
    }

	//remove and return smallest item
	/*
		since we already have out priority queue sorted from our insert method we
		can just return the value of our head everytime and delte it then move pointers 
		in O(1) constant time
	*/
	T extractMin()
	{  
		T Min = head->value;
		Node* temp = head;
		head = head->next;
		delete temp;
		return Min;
	}

};