#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "trendtracker.h"

using namespace std;

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


int main()
{
	// Setup
	vector<string> R;
	string s, line;


	// Test constructor, size(), popularity(), tweeted()
	Trendtracker T1("small.txt");
	test(T1.size() == 4);
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 0);
	test(T1.popularity("#C++") == 0);

	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 1);
	test(T1.popularity("#C++") == 0);

	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 2);
	test(T1.popularity("#C++") == 0);

	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 3);
	test(T1.popularity("#C++") == 0);

	T1.tweeted("#cs4all");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 1);
	test(T1.popularity("#programming") == 3);
	test(T1.popularity("#C++") == 0);

	T1.tweeted("#algorithms");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 1);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 3);
	test(T1.popularity("#C++") == 0);

	T1.tweeted("#cs4all");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 3);
	test(T1.popularity("#C++") == 0);

	T1.tweeted("#datastructures");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 3);
	test(T1.popularity("#C++") == 0);


	Trendtracker T2("small.txt");
	T2.tweeted("#programming");
	T2.tweeted("#programming");
	T2.tweeted("#programming");
	T2.tweeted("#programming");
	T2.tweeted("#programming");
	T2.tweeted("#C++");
	T2.tweeted("#C++");
	T2.tweeted("#C++");
	T2.tweeted("#C++");
	T2.tweeted("#cs4all");
	T2.tweeted("#cs4all");
	T2.tweeted("#cs4all");
	T2.tweeted("#algorithms");
	T2.tweeted("#algorithms");
	test(T2.popularity("#algorithms") == 2);
	test(T2.popularity("#cs4all") == 3);
	test(T2.popularity("#programming") == 5);
	test(T2.popularity("#C++") == 4);

        
	// Enforce no usage of global variables
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#programming") == 3);
	test(T1.popularity("#C++") == 0);
        

	// Test top_trend(), top_three_trends()
	Trendtracker T3("small.txt");
	T3.top_three_trends(R);
	test(R.size() == 3);

	T3.tweeted("#programming");
	test(T3.top_trend() == "#programming");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#programming");

	T3.tweeted("#C++");
	T3.tweeted("#C++"); 
	test(T3.top_trend() == "#C++"); 
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#C++");
	test(R[1] == "#programming");

	T3.tweeted("#algorithms");
	T3.tweeted("#algorithms");
	T3.tweeted("#algorithms");
	test(T3.top_trend() == "#algorithms"); 
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#algorithms");
	test(R[1] == "#C++");
	test(R[2] == "#programming");

	T3.tweeted("#cs4all");
	T3.tweeted("#cs4all");
	T3.tweeted("#cs4all");
	T3.tweeted("#cs4all");
	test(T3.top_trend() == "#cs4all");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#cs4all");
	test(R[1] == "#algorithms");
	test(R[2] == "#C++");
        
	// At this point:
	// cs4all: 4
	// algorithms: 3
	// C++: 2
	// programming: 1

	T3.tweeted("#programming");
	T3.tweeted("#programming");
	T3.tweeted("#programming");
	T3.tweeted("#programming");
	test(T3.top_trend() == "#programming");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#programming");
	test(R[1] == "#cs4all");
	test(R[2] == "#algorithms");

	// At this point:
	// programming: 5
	// cs4all: 4
	// algorithms: 3
	// C++: 2

	T3.tweeted("#cs4all");
	T3.tweeted("#cs4all");
	T3.tweeted("#algorithms");
	test(T3.top_trend() == "#cs4all");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#cs4all");
	test(R[1] == "#programming");
	test(R[2] == "#algorithms");
	 
	// At this point:
	// cs4all: 6
	// programming: 5
	// algorithms: 4
	// C++: 2

	for (int i = 0; i < 10000; ++i)
		T3.tweeted("#C++");
	test(T3.top_trend() == "#C++");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#C++");
	test(R[1] == "#cs4all");
	test(R[2] == "#programming");



	Trendtracker T4("hashtags.txt");
	test(T4.size() == 300000); 

	ifstream f;
	f.open("tweeted.txt");
	assert(f.is_open()); // If this fails, you're missing tweeted.txt
	while (getline(f, line))
		T4.tweeted(line);
	f.close();

	test(T4.popularity("#programming") == 10);
	test(T4.popularity("#computer") == 9);
	test(T4.popularity("#is") == 8);
	test(T4.popularity("#very") == 7);
	test(T4.popularity("#fun") == 6);
	test(T4.popularity("#but") == 5);
	test(T4.popularity("#sometimes") == 5);
	test(T4.popularity("#can") == 5);
	test(T4.popularity("#be") == 5);
	test(T4.popularity("#challenging") == 5);

	test(T4.top_trend() == "#programming");

	T4.top_three_trends(R);
	test(R[0] == "#programming");
	test(R[1] == "#computer");
	test(R[2] == "#is");

	
	// Test a Trendtracker with a single hashtag
	Trendtracker T5("tiny.txt");
	test(T5.size() == 1);
	test(T5.popularity("#solo") == 0);
	test(T5.popularity("#duo") == -1);
	T5.tweeted("#solo");
	test(T5.popularity("#solo") == 1);
	test(T5.popularity("#duo") == -1);
	test(T5.top_trend() == "#solo");
	T5.top_three_trends(R);
	test(R.size() == 1);
	test(R[0] == "#solo");


	cout << "Assignment complete." << endl;
}