
class queueLL
{
private:
	//put what you need here...
    class Node{
        public:
            int value;
            Node* next;
            Node(int n){
                value = n;
                next = NULL;
            }
    };
    Node*  head,* tail;


public:
	queueLL()
	{head = tail = NULL;}

	~queueLL()
	{}

	//add item to back of queue
	void enqueue(int x)
	{
		Node* temp = new Node(x);
		if(tail == NULL){
			head = tail = temp;
			return;
		}
		tail->next = temp;
		tail = temp;
	}

	//remove and return first item from queue
	int dequeue()
	{
		if(head == NULL)
			return -1;

		
	}

	bool empty()
	{
		if(head == NULL)
			return true;
		else
			return false;
	}

	//For the final part of the test program, template this class
	//and add a decimate method.

};