

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
	// O(n) since were are going through the stack linked list
	// and delete each node
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
	// O(1) since we are returning whether top is null or not
	bool empty()
	{return top==NULL;}

	//add item to top of stack
	/*
		The big O run time for the push method would be O(1)since
		were adding to the top of the stack and dont have to go through
		each item in the stack to place it
	*/
	void push(int x)
	{
		// create a temp new node
		node* temp = new node(x);
		//temp next to be our top since current temp is new top
		temp->next = top;
		top = temp;
	}

	//remove and return top item from stack
	/*
		POP method comes out to the same O(1) since were taking the top
		of the stack and returning its value and delteing the node this 
		all run in constant time since we dont need to go throught the items
		in the stack
	*/
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
	///////////////////////////
	/*
		My runtime here would be O(n) since i have to traverse
		through the stack linked list to be able to determine where i should
		put the item
	*/
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