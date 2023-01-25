#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include "trendtracker.h"

using namespace std;

Trendtracker::Trendtracker(string filename){
    S.clear();
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
int Trendtracker::size(){
    return E.size();
}
int Trendtracker::search(string ht){
    int s = 0, e = size();
    while(s<=e){
        int m = s+(e-s)/2;
        if(E[m].hashtag == ht)
            return m;
        else if (E[m].hashtag < ht)
            s=m+1;
        else
            e=m-1;
    }
    return -1;
}


void Trendtracker::tweeted(string ht){
    int Index = search(ht);
    if(Index != -1)
        E[Index].pop += 1;
}

int Trendtracker::popularity(string name){
    int Index = search(name);
    if(Index != -1)
        return E[Index].pop;
    return -1;
}

string Trendtracker::top_trend(){
    if(E.empty()) return "";
    return "adasd";
}
void Trendtracker::top_three_trends(vector<string> &T){
}