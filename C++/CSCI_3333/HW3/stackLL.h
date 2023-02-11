

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
		// free up memory by deleteing all nodes
		node* temp;
		while(top != NULL){
			temp = top;
			top = top->next;
			delete temp;
		}
	}

	//return true if empty, false if not
	bool empty()
	{return top==NULL;}

	//add item to top of stack
	void push(int x)
	{
		// create a temp new node
		node* temp = new node(x);
		//temp next to be our top since current temp is new top
		temp->next = top;
		top = temp;
	}

	//remove and return top item from stack
	int pop()
	{
		// delteion node
		node* del;
		// temp int to hold value
		int temp;
		//if top is null return -1
		if(top==NULL)
			return -1;
		// set our deletion node to our top
		del = top;
		// our temp val will be the del
		temp = top->val; 
		// top will now be the next top
		top = top->next;
		// delete our deletion node
		delete del;
		// return our temp val
		return temp;
	}

	//add item x to stack, but insert it
	//right after the current ith item from the top
	//(and before the i+1 item).
	void insertAt(int x, int i)
	{
		// create a temp new node 
		node* temp = new node(x);
		// position in stack
		int pos = 1;
		// if i is zero then it will be our new top
		if(i==0)
		{
			temp->next = top;
			top = temp;
			return;
		}
		// get a pointer to the current node
		node* ptr = top;
		// traverse the list until desired position is reached or end of list is reached
		while(ptr!=NULL && pos < i)
		{	
			ptr = ptr->next;
			pos++;
		}
		// set the next pointer of the new node to the next node of the current node
		temp->next = ptr->next;
		// set the next pointer of the current node to the new node
		ptr->next = temp;
	} 
};