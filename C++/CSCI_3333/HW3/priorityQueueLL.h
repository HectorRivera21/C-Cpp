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
		while(head!=NULL)
		{
			Node* temp = head;
			head = head->next;
			delete(temp);
		}
	}

	//return true if empty, false if not
	bool empty()
	{
		return head == NULL;
	}

	//add item
	void insert(T x)
	{
		Node* temp = new Node(x);
		if(head == NULL || head->value > x)
		{
			temp->next = head;
			head = temp;
		}
		else
		{
			Node* copy = head;
			Node* p = NULL;
			while(copy != NULL && copy->value < x)
			{
				p = copy;
				copy= copy->next;
			}

			
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
	T extractMin()
	{  
		T Min = head->value;
		Node* temp = head;
		head = head->next;
		delete temp;
		return Min;
	}

};