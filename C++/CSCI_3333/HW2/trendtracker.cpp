#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include "trendtracker.h"

using namespace std;

Trendtracker::Trendtracker(string filename){
    E.clear();
    Entry e;
    string hashtag;
    ifstream file(filename);
    if(file.is_open()){
        while(!file.eof()){
            getline(file, hashtag);
            
            e.hashtag = hashtag;
            e.pop = 0;

            E.push_back(e);
        }
        file.close();
    }
   
}