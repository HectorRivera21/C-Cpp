#ifndef TRENDTRACKER_H
#define TRENDTRACKER_H

#include <cassert>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Trendtracker
{
	// For the mandatory running times below:
	// n is the number of hashtags in the Trendtracker.

	public:
		// Creates a Trendtracker containing hashtags 
		// found in the provided file.
		// The file is promised to have the following format: 
		// 
		// string1 
		// string2 
		// ...
		// stringN 
		//
		// where string1 < string2 < ... < stringN 
		// 
		// Must run in O(n) time.
		Trendtracker(string filename);
	
		// Return the number of hashtags in the Trendtracker.
		//
		// Must run in O(1) time.
		int size();

		// Adds 1 to the total number times a hashtag has been tweeted.
		// If the hashtag does not exist in TrendTracker, does nothing.
		//
		// Must run in O(log(n)) time.
		void tweeted(string ht);

		// Returns the number of times a hashtag has been tweeted.
		// If the hashtag does not exist in Trendtracker, returns -1.
		// 
		// Must run in O(log(n)) time.
		int popularity(string name);

		// Returns a most-tweeted hashtag.
		// If the Trendtracker has no hashtags, returns "".
		// 
		// Must run in O(1) time.
		string top_trend();

		// Fills the provided vector with the 3 most-tweeted hashtags, 
		// in order from most-tweeted to least-tweeted.
		// 
		// If there are fewer than 3 hashtags, then the vector is filled
		// with all hashtags (in most-tweeted to least-tweeted order).
		//
		// Must run in O(1) time.
		void top_three_trends(vector<string> &T); 

	private: 
		// A simple class representing a hashtag and 
		// the number of times it has been tweeted.
		class Entry
		{
			public:
				string hashtag;
				int pop;
		};

		// Optional helper method.
		// Returns the index of E containing an Entry with hashtag ht.
		// If no such hashtag is found, returns -1. 
		// 
		// Should run in O(log(n)).
		int search(string ht);

		// Entries sorted (lexicographically) by hashtag.
		vector<Entry> E; 

		// Stores indices of the (up to) three most-tweeted
		// entries in E.
		vector<int> S;      
};

#endif 