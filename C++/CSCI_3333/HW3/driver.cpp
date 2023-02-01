
#include <iostream>
#include <string>
#include "stackLL.h"
#include "queueLL.h"
#include "priorityQueueLL.h"
using namespace std;

int main()
{
	/////////////Test code for stack ///////////////
	stackLL stk;

	stk.push(5);
	stk.push(13);
	stk.push(7);
	stk.push(3);
	stk.push(2);
	stk.push(11);

	cout << "Popping: " << stk.pop() << endl;
	cout << "Popping: " << stk.pop() << endl;

	stk.push(17);
	stk.push(19);
	stk.push(23);

	while( ! stk.empty() )
	{
		cout << "Popping: " << stk.pop() << endl;
	}

	// output order: 11,2,23,19,17,3,7,13,5


	stackLL stkx;

	stkx.push(5);
	stkx.push(10);
	stkx.push(15);
	stkx.push(20);
	stkx.push(25);
	stkx.push(30);

	// stkx.insertAt(-100, 3);
	// stkx.insertAt(-200, 7);
	// stkx.insertAt(-300, 0);

	// //output order: -300,30,25,20,-100,15,10,5,-200
	// while( ! stkx.empty() )
	// 	cout << "Popping: " << stkx.pop() << endl;


	// ///////////////////////////////////////

	// //////////Test code for queue ///////////

	// queueLL Q;

	// Q.enqueue(1);
	// Q.enqueue(2);
	// Q.enqueue(3);
	// cout << "Dequeuing: " << Q.dequeue() << endl; //1
	// cout << "Dequeuing: " << Q.dequeue() << endl; //2
	// Q.enqueue(4);
	// Q.enqueue(5);

	// //3 4 5
	// while( ! Q.empty() )
	// {
	// 	cout << "Dequeuing: " << Q.dequeue() << endl;
	// }

	// /////////////////////////////////////////



	// //////////Test code for priority queue/////

	// priorityQueueLL<int> pQueue;

	// const int SIZE = 20;

	// //insert a bunch of random numbers
	// for(int i=0; i<SIZE; i++)
	// {
	// 	pQueue.insert( rand() );
	// }

	// //pull them back out..
	// //They must come out in order from smallest to largest
	// while( ! pQueue.empty() )
	// {
	// 	cout << pQueue.extractMin() << endl;
	// }


	// priorityQueueLL<string> pqs;

	// pqs.insert("whale");
	// pqs.insert("snake");
	// pqs.insert("buffalo");
	// pqs.insert("elmo");
	// pqs.insert("fire");
	// pqs.insert("waffle");

	// //buffalo elmo fire snake waffle whale
	// while( !pqs.empty() )
	// {
	// 	cout << pqs.extractMin() << endl;
	// }

	// ///////////////////////////////////////////
	// //1) Template your queue class
	// //2) Add a decimate method to your queue class
	// queueLL<int> qx;

	// for(int i=1; i<=100; i++)
	// 	qx.enqueue( i );

	// //Eliminate every 10th item from list
	// //https://en.wikipedia.org/wiki/Decimation_(punishment)
	// qx.decimate();

	// //1 2 3 4 5 6 7 8 9 11 12 13 14 15 16 17 18 19 21 22... 98 99
	// while( ! qx.empty() )
	// 	cout << qx.dequeue() << endl;


	// queueLL<string> qy;
	// qy.enqueue("sparticus");
	// qy.enqueue("maximus");
	// qy.enqueue("killicus");
	// qy.enqueue("awesomeicus");
	// qy.enqueue("gannicus");
	// qy.enqueue("varro");
	// qy.enqueue("oenomous");
	// qy.enqueue("slayicus");
	// qy.enqueue("bladeicus");
	// qy.enqueue("ted");
	// qy.enqueue("smashicus");
	// qy.enqueue("mallicus");
	// qy.enqueue("wussicus");
	// qy.enqueue("wimpicus");
	// qy.enqueue("crixus");

	// qy.decimate();

	// //Everyone but Ted.
	// while( ! qy.empty() )
	// 	cout << qy.dequeue() << endl;

	return 0;
}