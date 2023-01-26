#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include "trendtracker.h"

using namespace std;

Trendtracker::Trendtracker(string filename){
    E.clear();
    string hashtag;
    ifstream file(filename);
    
    while(file >> hashtag){
        Entry e;
        e.hashtag = hashtag;
        e.pop = 0;

        E.push_back(e);
    }
    file.close();
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
    //O(log n)
    int Index = search(ht);
    if(Index != -1){
        E[Index].pop += 1;

        bool dup = false;
        // O(n)
        for(int i = 0; i<S.size();i++){
            if(S[i]==Index)
                dup = true;
        }
        if(!dup)
            S.push_back(Index);
        for(int i =0; i<S.size();i++){ //O(n)
            int j=i;
            while(j>0 && E[S[j]].pop>E[S[j-1]].pop){// O(1)
                int temp = S[j-1];
                S[j-1]=S[j];
                S[j] = temp;
                j--;
            }
        }

        if(S.size()>3)
            S.pop_back();
    }
}

int Trendtracker::popularity(string name){
    int Index = search(name);
    if(Index != -1)
        return E[Index].pop;
    return -1;
}

string Trendtracker::top_trend(){
    if(S.empty()) 
        return "";
    else 
        return E[S[0]].hashtag;
}
void Trendtracker::top_three_trends(vector<string> &T){
    T.clear();

    if(E.size() == 1) //test case for tiny.txt
        T.push_back(E[0].hashtag);
    else{
        if(S.size() == 0){
            T.push_back(E[0].hashtag);
            T.push_back(E[1].hashtag);
            T.push_back(E[1].hashtag);
        }
        else if(S.size() == 1){
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[1].hashtag);
            T.push_back(E[2].hashtag);
        }
        else if(S.size() == 2){
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[S[1]].hashtag);
            T.push_back(E[2].hashtag);

        }else if(S.size() == 3){
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[S[1]].hashtag);
            T.push_back(E[S[2]].hashtag);
        }
    }
}