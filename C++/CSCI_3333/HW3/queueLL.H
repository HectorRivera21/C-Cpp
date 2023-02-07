template <typename T>
class queueLL
{
private:
	//put what you need here...
    class Node{
        public:
            T value;
            Node* next;
            Node(T n){
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
		Node* temp;
		while(head!=NULL){
			temp = head;
			head = head->next;
			delete(temp);
		}
	}

	//add item to back of queue
	void enqueue(T x)
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
	T dequeue()
	{
		if(head == NULL)
			return head->value;
		
		Node* del = head;
		T val = head->value;
		head = head->next;

		if(head == NULL)
			tail = NULL;

		delete(del);
		return val;
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
	void decimate(){
		Node* temp = head;
		Node* prev = NULL;
		int count=1;

		while(temp!=NULL){
			if(count % 10 == 0)
			{
				prev->next = temp->next;
				delete temp;
				temp = prev->next;
			}
			else 
			{
				prev = temp;
				temp = temp->next;
			}
			count++;
		}
		
	}

};