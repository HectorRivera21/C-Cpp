
template <class T>
class priorityQueueLL
{
private:
	class node
	{	
	public:
		//put what you need here..
		T value;
		node* next;
		node(T n){
			value = n;
			next = NULL;
		}
	}

	//add what you wish here
	node* head,* tail;

public:

	priorityQueueLL()
	{head = tail = NULL;}

	~priorityQueueLL()
	{}

	//return true if empty, false if not
	bool empty()
	{
		if(head == NULL){
			return true;
		}
		else 
		{
			return false;
		}
	}

	//add item
	void insert(T x)
	{

    }

	//remove and return smallest item
	T extractMin()
	{
        return 'nothing';
    }

};