#include <iostream>
#include <cstdlib>
#include <string>
#include "minpriorityqueue.h"

using namespace std;

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))

int priority2(string s)
{
	int p = 0;
	for (int i = 0; i < s.length()/2; ++i)
		p += static_cast<int>(s[i]);
	return p;
} 

int priority(string s)
{
	int p = 0;
	for (int i = 0; i < s.length(); ++i)
		p += static_cast<int>(s[i]);
	return p;
}


int main()
{
	// Setup
	string* S = new string[100000];
	for (int i = 0; i < 100000; ++i)
		S[i] = to_string(i+1);


	// Test size(), push(), front(), pop()
	// with "nice" priorities
	MinPriorityQueue<string> Q1;
	test(Q1.size() == 0);

	Q1.push("hello", 1);
	test(Q1.front() == "hello");
	test(Q1.size() == 1);

	Q1.push("dog", 3);
	test(Q1.front() == "hello");
	test(Q1.size() == 2);

	Q1.push("tree", 6);
	test(Q1.front() == "hello");
	test(Q1.size() == 3);

	Q1.push("phone", 11);
	test(Q1.front() == "hello");
	test(Q1.size() == 4);

	Q1.pop(); 
	test(Q1.front() == "dog");
	test(Q1.size() == 3);

	Q1.pop(); 
	test(Q1.front() == "tree");
	test(Q1.size() == 2);

	Q1.pop(); 
	test(Q1.front() == "phone");
	test(Q1.size() == 1);

	Q1.pop(); 
	test(Q1.size() == 0);

	Q1.pop(); 
	test(Q1.size() == 0);

	Q1.pop(); 
	test(Q1.size() == 0);

	Q1.push("hello2", 2);
	test(Q1.size() == 1);
	test(Q1.front() == "hello2");


	// Test size(), push(), front(), pop()
	// with "not nice" priorities
	MinPriorityQueue<string> Q2;
	test(Q2.size() == 0);

	Q2.push("goodbye", 11);
	test(Q2.front() == "goodbye");
	test(Q2.size() == 1);

	Q2.push("frog", 6);
	test(Q2.front() == "frog");
	test(Q2.size() == 2);

	Q2.push("bee", 4);
	test(Q2.front() == "bee");
	test(Q2.size() == 3);

	Q2.push("tone", 2);
	test(Q2.front() == "tone");
	test(Q2.size() == 4);

	test(Q1.front() == "hello2"); // Forbid globals
	test(Q1.size() == 1);         // Forbid globals

	Q2.pop(); 
	test(Q2.front() == "bee");
	test(Q2.size() == 3);

	Q2.pop(); 
	test(Q2.front() == "frog");
	test(Q2.size() == 2);

	Q2.pop();
	test(Q2.front() == "goodbye");
	test(Q2.size() == 1);

	Q2.pop();
	test(Q2.size() == 0);

	Q2.push("hello3", 1);
	test(Q2.front() == "hello3");
	test(Q2.size() == 1);


	// Test size(), push(), front(), pop()
	// with "not nice" priorities
	MinPriorityQueue<string> Q3;
	test(Q3.size() == 0);

	Q3.push("pear", 6);
	test(Q3.front() == "pear");
	test(Q3.size() == 1);

	Q3.push("palm", 10);
	test(Q3.front() == "pear");
	test(Q3.size() == 2);

	Q3.push("pop", 8);
	test(Q3.front() == "pear");
	test(Q3.size() == 3);

	Q3.push("push", 4);
	test(Q3.front() == "push");
	test(Q3.size() == 4);

	test(Q2.front() == "hello3"); // Forbid globals
	test(Q2.size() == 1);         // Forbid globals

	Q3.pop(); 
	test(Q3.front() == "pear");
	test(Q3.size() == 3);

	Q3.pop(); 
	test(Q3.front() == "pop");
	test(Q3.size() == 2);

	Q3.pop();
	test(Q3.front() == "palm");
	test(Q3.size() == 1);

	Q3.pop();
	test(Q3.size() == 0);


	// Big test of size(), push(), front(), pop()
	MinPriorityQueue<string> Q4;

	for (int i = 0; i < 100000; ++i)
		Q4.push(S[i], priority(S[i]));

	int prev_p = 0;
	for (int l = 100000; l > 90000; --l)
	{
		string s = Q4.front();
		int p = priority(s);

		test(Q4.size() == l);
		Q4.pop();

		test(p >= prev_p);
		prev_p = p;
	}


	// Test decrease_key() in a very simple case
	MinPriorityQueue<string> Q5;

	Q5.push("hare", 5);
	Q5.push("tortoise", 10);
	test(Q5.front() == "hare");
	test(Q5.size() == 2);

	Q5.decrease_key("tortoise", 3);
	test(Q5.front() == "tortoise");
	test(Q5.size() == 2);

	Q5.pop();
	test(Q5.front() == "hare");
	test(Q5.size() == 1);


	// Test decrease_key() in more complex cases
	MinPriorityQueue<string> Q6;

	Q6.push("e", 50);
	Q6.push("d", 40);
	Q6.push("c", 30);
	Q6.push("b", 20);
	Q6.push("a", 10);
	// [(e, 50), (d, 40), (c, 30), (b, 20), (a, 10)]

	test(Q6.front() == "a"); 
	test(Q6.size() == 5);

	Q6.decrease_key("e", 35);
	// [(d, 40), (e, 35), (c, 30), (b, 20), (a, 10)]
	Q6.decrease_key("c", 15);
	// [(d, 40), (e, 35), (b, 20), (c, 15), (a, 10)]
	Q6.decrease_key("d", 8);
	// [(e, 35), (b, 20), (c, 15), (a, 10), (d, 8)]
	Q6.decrease_key("b", 5);
	// [(e, 35), (c, 15), (a, 10), (d, 8), (b, 5)]

	test(Q6.front() == "b"); 
	test(Q6.size() == 5);

	// [(e, 35), (c, 15), (a, 10), (d, 8)]
	Q6.pop();
	test(Q6.front() == "d"); 
	test(Q6.size() == 4);

	// [(e, 35), (c, 15), (a, 10)]
	Q6.pop();
	test(Q6.front() == "a"); 
	test(Q6.size() == 3);

	// [(e, 35), (c, 15)]
	Q6.pop();
	test(Q6.front() == "c"); 
	test(Q6.size() == 2);

	// [(e, 35)]
	Q6.pop();
	test(Q6.front() == "e"); 
	test(Q6.size() == 1);


	// Another test of decrease_key() in more complex cases
	MinPriorityQueue<string> Q7;

	string s;
	for (char c = 'a'; c <= 'z'; ++c)
	{
		s.clear();
		s += c;
		Q7.push(s, static_cast<int>(c)*10);
	}

	Q7.decrease_key("z", static_cast<int>('a')*10-1);
	// [y, x, ..., b, a, z]
	test(Q7.front() == "z");
	
	Q7.decrease_key("m", static_cast<int>('a')*10-2);
	// [y, x, ..., b, a, z, m]
	test(Q7.front() == "m");

	Q7.decrease_key("q", static_cast<int>('a')*10-3);
	// [y, x, ..., b, a, z, m, q]
	test(Q7.front() == "q");

	Q7.decrease_key("h", static_cast<int>('a')*10-4);
	// [y, x, ..., b, a, z, m, q, h]
	test(Q7.front() == "h");

	Q7.decrease_key("y", static_cast<int>('a')*10-5);
	// [x, ..., b, a, z, m, q, h, y]
	test(Q7.front() == "y");

	Q7.decrease_key("c", static_cast<int>('a')*10-6);
	// [x, ..., b, a, z, m, q, h, y, c]
	test(Q7.front() == "c");

	Q7.decrease_key("r", static_cast<int>('a')*10-7);
	// [x, ..., b, a, z, m, q, h, y, c, r]
	test(Q7.front() == "r");

	Q7.pop();
	// [x, ..., b, a, z, m, q, h, y, c]
	test(Q7.front() == "c");

	Q7.pop();
	// [x, ..., b, a, z, m, q, h, y]
	test(Q7.front() == "y");

	Q7.pop();
	// [x, ..., b, a, z, m, q, h]
	test(Q7.front() == "h");

	Q7.pop();
	// [x, ..., b, a, z, m, q]
	test(Q7.front() == "q");

	Q7.pop();
	// [x, ..., b, a, z, m]
	test(Q7.front() == "m");

	Q7.decrease_key("a", static_cast<int>('a')*10-8);
	// [x, ..., b, z, m, a]
	test(Q7.front() == "a");

	Q7.decrease_key("b", static_cast<int>('a')*10-9);
	// [x, ..., z, m, a, b]
	test(Q7.front() == "b");

	Q7.pop();
	// [x, ..., z, m, a]
	test(Q7.front() == "a");

	Q7.pop();
	// [x, ..., z, m]
	test(Q7.front() == "m");

	Q7.pop();
	// [x, ..., z]
	test(Q7.front() == "z");

	test(Q7.size() == 18);


	// Big test of decrease_key()
	MinPriorityQueue<string> Q8;

	for (int i = 0; i < 100000; ++i)
		Q8.push(S[i], priority(S[i]));

	for (int i = 0; i < 100000; ++i)
		Q8.decrease_key(S[i], priority2(S[i]));

	prev_p = 0;
	for (int l = 100000; l > 90000; --l)
	{
		string s = Q8.front();
		int p = priority2(s);

		test(Q8.size() == l);
		Q8.pop();

		test(p >= prev_p);
		prev_p = p;
	}

	
	// Small test of everything with a different type (char)
	MinPriorityQueue<char> Q9;

	test(Q9.size() == 0);
	Q9.push('a', 10);
	test(Q9.size() == 1);
	Q9.push('c', 6);
	test(Q9.size() == 2);
	Q9.push('f', 8);
	test(Q9.size() == 3);
	Q9.push('m', 7);
	test(Q9.size() == 4);
	Q9.push('z', 15);
	test(Q9.size() == 5);
	Q9.push('q', 11);
	test(Q9.size() == 6);
	Q9.push('d', 3);
	test(Q9.size() == 7);
	
	test(Q9.front() == 'd');
	Q9.pop(); 
	test(Q9.size() == 6);

	test(Q9.front() == 'c');
	Q9.pop(); 
	test(Q9.size() == 5);

	test(Q9.front() == 'm');
	Q9.pop(); 
	test(Q9.size() == 4);

	test(Q9.front() == 'f');
	Q9.decrease_key('q', 2);

	test(Q9.front() == 'q');
	Q9.pop(); 
	test(Q9.size() == 3);

	test(Q9.front() == 'f');
	Q9.pop(); 
	test(Q9.size() == 2);

	test(Q9.front() == 'a');
	Q9.pop(); 
	test(Q9.size() == 1);

	test(Q9.front() == 'z');
	Q9.pop(); 
	test(Q9.size() == 0);


	cout << "Assignment complete." << endl;
}