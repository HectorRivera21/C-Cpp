

class stackLL
{
private:
	class node
	{
	public:
		//put what you need in here
	};

	node * top;

public:

	stackLL()
	{}

	//Take care of memory leaks...
	~stackLL()
	{}

	//return true if empty, false if not
	bool empty()
	{}

	//add item to top of stack
	void push(int x)
	{}

	//remove and return top item from stack
	int pop()
	{}

	//add item x to stack, but insert it
	//right after the current ith item from the top
	//(and before the i+1 item).
	void insertAt(int x, int i)
	{}

};