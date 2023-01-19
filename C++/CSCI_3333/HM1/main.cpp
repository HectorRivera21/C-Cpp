
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


	// Test size(), insert()
	Trendtracker T1;
	test(T1.size() == 0);
	test(T1.popularity("#algorithms") == -1);
	test(T1.popularity("#cs4all") == -1);
	test(T1.popularity("#programming") == -1);

	T1.insert("#cs4all");
	test(T1.size() == 1);
	test(T1.popularity("#algorithms") == -1);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == -1);

	T1.insert("#algorithms");
	test(T1.size() == 2);
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == -1);

	T1.insert("#programming");
	test(T1.size() == 3);
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == 0);

	T1.insert("#algorithms");
	test(T1.size() == 3);
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == 0);


	// Test tweeted()
	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == 1);

	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == 2);

	T1.tweeted("#programming");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#cs4all");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 1);
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#algorithms");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 1);
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#cs4all");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#datastructures");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == -1);
	test(T1.popularity("#programming") == 3);

	T1.insert("#datastructures");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == 0);
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#datastructures");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == 1);
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#datastructures");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == 2);
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#datastructures");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == 3);
	test(T1.popularity("#programming") == 3);

	T1.tweeted("#datastructures");
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == 4);
	test(T1.popularity("#programming") == 3);


	Trendtracker T2;
	T2.insert("#3333");
	T2.insert("#programming");
	T2.insert("#cs4all");
	T2.insert("#C++");
	T2.insert("#algorithms");
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
	T2.tweeted("#3333");
	test(T2.popularity("#programming") == 5);
	test(T2.popularity("#cs4all") == 3);
	test(T2.popularity("#algorithms") == 2);
	test(T2.popularity("#C++") == 4);
	test(T2.popularity("#3333") == 1);
	T2.insert("#3333");
	T2.insert("#programming");
	T2.insert("#cs4all");
	T2.insert("#C++");
	T2.insert("#algorithms");
	test(T2.popularity("#programming") == 5);
	test(T2.popularity("#cs4all") == 3);
	test(T2.popularity("#algorithms") == 2);
	test(T2.popularity("#C++") == 4);
	test(T2.popularity("#3333") == 1);


	// Enforce no usage of global variables
	test(T1.popularity("#algorithms") == 1);
	test(T1.popularity("#cs4all") == 2);
	test(T1.popularity("#datastructures") == 4);
	test(T1.popularity("#programming") == 3);


	Trendtracker T3;
	test(T3.top_trend() == "");
	T3.top_three_trends(R);
	test(R.size() == 0);

	T3.insert("#programming");
	test(T3.top_trend() == "#programming");
	T3.top_three_trends(R);
	test(R.size() == 1);
	test(R[0] == "#programming");

	T3.tweeted("#programming");
	test(T3.top_trend() == "#programming");
	T3.top_three_trends(R);
	test(R.size() == 1);
	test(R[0] == "#programming");

	// At this point:
	// programming: 1

	T3.insert("#C++");
	T3.tweeted("#C++");
	T3.tweeted("#C++");
	test(T3.top_trend() == "#C++");

	T3.top_three_trends(R);
	test(R.size() == 2);
	test(R[0] == "#C++");
	test(R[1] == "#programming");

	// At this point:
	// C++: 2
	// programming: 1

	T3.insert("#3333");
	T3.tweeted("#3333");
	T3.tweeted("#3333");
	T3.tweeted("#3333");
	test(T3.top_trend() == "#3333");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#3333");
	test(R[1] == "#C++");
	test(R[2] == "#programming");

	// At this point:
	// 3333: 3
	// C++: 2
	// programming: 1

	T3.insert("#cs4all");
	T3.tweeted("#cs4all");
	T3.tweeted("#cs4all");
	T3.tweeted("#cs4all");
	T3.tweeted("#cs4all");
	test(T3.top_trend() == "#cs4all");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#cs4all");
	test(R[1] == "#3333");
	test(R[2] == "#C++");

	// At this point:
	// cs4all: 4
	// 3333: 3
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
	test(R[2] == "#3333");

	// At this point:
	// programming: 5
	// cs4all: 4
	// 3333: 3
	// C++: 2

	T3.tweeted("#cs4all");
	T3.tweeted("#cs4all");
	T3.tweeted("#3333");
	test(T3.top_trend() == "#cs4all");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#cs4all");
	test(R[1] == "#programming");
	test(R[2] == "#3333");

	// At this point:
	// cs4all: 6
	// programming: 5
	// 3333: 4
	// C++: 2

	for (int i = 0; i < 10000; ++i)
		T3.tweeted("#C++");
	test(T3.top_trend() == "#C++");
	T3.top_three_trends(R);
	test(R.size() == 3);
	test(R[0] == "#C++");
	test(R[1] == "#cs4all");
	test(R[2] == "#programming");


	//Testing remove()
	T3.remove("#C++");
	T3.remove("#programming");
	T3.top_three_trends(R);
	test(R.size() == 2);
	test(R[0] == "#cs4all");
	test(R[1] == "#3333");
	test(T3.size() == 2);

	Trendtracker T4;

	ifstream f;
	f.open("common.txt");
	assert(f.is_open()); // If this fails, you're missing common.txt
	while (getline(f, line))
		T4.insert(line);
	f.close();
	test(T4.size() == 3597);

	f.open("common.txt");
	while (getline(f, line))
		T4.tweeted(line);
	f.close();

	for (int i = 0; i < 1000; ++i)
	{
		test(T4.popularity("#finishing") == 6);
		test(T4.popularity("#completely") == 5);
		test(T4.popularity("#is") == 4);
		test(T4.popularity("#sometimes") == 3);
		test(T4.popularity("#quieting") == 2);

		test(T4.top_trend() == "#finishing");

		T4.top_three_trends(R);
		test(R[0] == "#finishing");
		test(R[1] == "#completely");
		test(R[2] == "#is");
	}

	//Test top_k_trends
	string weird = "#";
	for (int i = 'a'; i <= 'z'; i++)
	{
		for (int j = 'a'; j <= 'z'; j++)
		{
			weird += i;
			weird += j;
			for (int i = 0; i < 3 * (weird[1] - 'a') + (weird[2] - 'a'); i++)
				T4.tweeted(weird);
			weird = "#";
		}
	}

	T4.top_k_trends(R, 50);

	test(R[2] == "#up");
	test(R[5] == "#so");
	test(R[10] == "#ok");
	test(R[15] == "#me");
	test(R[29] == "#finishing");
	test(R[32] == "#quieting");

	cout << "Assignment complete." << endl;
}