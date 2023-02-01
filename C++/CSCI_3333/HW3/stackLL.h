

class stackLL
{
private:
	class node
	{
	public:
		//put what you need in here
		int val;
		node* next;
		node(int n){
			this->val=n;
			this->next=nullptr;
		}
	};

	node * top;

public:

	stackLL()
	{top = NULL;}


	//Take care of memory leaks...
	~stackLL()
	{
		node* temp;
		while(top != NULL){
			temp = top;
			top = top->next;
			delete temp;
		}
	}

	//return true if empty, false if not
	bool empty()
	{
		if(top == NULL)
			return true;
		else
			return false;
	}

	//add item to top of stack
	void push(int x)
	{
		node* temp = new node(x);
		temp->next = top;
		top = temp;
	}

	//remove and return top item from stack
	int pop()
	{
		node* del;
		int temp;
		if(top==NULL){
			return -1;
		}
		del = top;
		top = top->next;
		temp = del->val;
		delete del;// check wheather free or delete is better
		return temp;
	}

	//add item x to stack, but insert it
	//right after the current ith item from the top
	//(and before the i+1 item).
	void insertAt(int x, int i)
	{}

};