// template t to dynamically change the value of data
// and certain functions
template <class T>
class queueLL
{
private:
	//put what you need here...
    class Node{
        public:
            T value;
            Node* next;
            Node(T n)
			{
                value = n;
                next = NULL;
            }
    };
    Node*  head,* tail;


public:
	queueLL()
	{head = tail = NULL;}

	~queueLL()
	{
		// free up memory by deleting all nodes
		Node* temp;
		while(head!=NULL)
		{
			temp = head;
			head = head->next;
			delete(temp);
		}
		tail = NULL;
	}

	//add item to back of queue
	void enqueue(T x)
	{
		// temp node creation for our value
		Node* temp = new Node(x);
		// if tail is NULL we make our head and tail equal to temp
		if(tail == NULL)
		{
			head = tail = temp;
			return;
		}
		// since were pushing from the back of the queue we must add our items through our tail
		tail->next = temp;
		tail = temp;
	}

	//remove and return first item from queue
	T dequeue()
	{
		if(head == NULL)
			return head->value;
		// store head in deletion node
		Node* del = head;
		// store value of head
		T val = head->value;
		// move pointer head to next node
		head = head->next;
		// if head is null set tail to null
		if(head == NULL)
			tail = NULL;
		// delete old head
		delete(del);
		// return value of removed node
		return val;
	}

	//return true if empty, false if not
	bool empty()
	{
		return head==NULL;
	}

	//For the final part of the test program, template this class
	//and add a decimate method.
	void decimate(){
		Node* temp = head;
		Node* prev = NULL;
		int count=1;
		// Traverse through the QueueLinkList
		while(temp!=NULL){
			if(count % 10 == 0)
			{
				/* 
					If counts remainder is 0
					We have our next item after the 10th saved
					then delete the 10th items
					replace the next for our 9th items for 11th items
				*/
				prev->next = temp->next;
				delete temp;
				temp = prev->next;
			}
			else 
			{
				// else we move our pointers and save it with prev
				prev = temp;
				temp = temp->next;
			}
			// up our count to follow the node were on
			count++;
		}
		
	}

};