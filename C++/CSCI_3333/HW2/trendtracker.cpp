#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include "trendtracker.h"

using namespace std;

Trendtracker::Trendtracker(string filename){
    // clear E 
    E.clear();
    // string placeholderf for the hashtags
    string hashtag;
    // open the file 
    ifstream file(filename);
    // while in the file we output each line to hashtag
    while(file >> hashtag){
        // create a new entry for the hashtag
        Entry e;
        // assign the hashtag to the property of hashtag
        // and pop to zero
        e.hashtag = hashtag;
        e.pop = 0;
        // push it to our E vector
        E.push_back(e);
    }
    // close the file
    file.close();
}
int Trendtracker::size(){
    // return the size of E
    return E.size();
}
int Trendtracker::search(string ht){
    // we set out size parameters for our search 
    // since our function size is O(1) we can use it here to find out vector max size
    int s = 0, e = size();
    // we set the condition for if the search size become to small or big 
    // then we exit since it hasnt been found
    while(s<=e){
        // we find our mid point in vector
        int m = s+(e-s)/2;
        // here if our mid is the hashtag found we return
        if(E[m].hashtag == ht)
            return m;
        // else we check if mid is less than the given string 
        // we then increment our start to be mid+1 
        else if (E[m].hashtag < ht)
            s=m+1;
        // else we just make our end = mid-1 if our mid 
        // is bigger than the given string 
        else
            e=m-1;
    }
    // we return -1 if its not found
    return -1;
}


void Trendtracker::tweeted(string ht){
    // we will be searching for the ht in our seach func O(log n)
    int Index = search(ht);
    if(Index != -1){
        // when found we go to the index and add 1 to pop 
        E[Index].pop += 1;
        // here were going to check if the index of the hashtag is already in S
        bool dup = false;
        for(int i = 0; i<S.size();i++){
            if(S[i]==Index)
                dup = true;
        }
        // if its not in S then we push it 
        if(!dup)
            S.push_back(Index);
        // sort S based on the popularity of the hashtags
        for(int i =0; i<S.size();i++){ 
            int j=i;
            while(j>0 && E[S[j]].pop>E[S[j-1]].pop){
                int temp = S[j-1];
                S[j-1]=S[j];
                S[j] = temp;
                j--;
            }
        }
        // we check if size is greater than 3
        if(S.size()>3)
            // remove the least popular hashtag
            S.pop_back();
    }
}

int Trendtracker::popularity(string name){
    // since we need to look for a name we can use
    // our handy seach function which is O(log(n)) 
    int Index = search(name);
    // here were checking weather we werent given -1 meaning it was found
    if(Index != -1)
        // so here we go to the index that was given and return the popularity
        return E[Index].pop;
    // else we return -1 meaning its not in the vector
    return -1;
}

string Trendtracker::top_trend(){
    // if our S vector holding 3 top trending hashtags
    // empty then return empty string
    if(S.empty()) 
        return "";
    // else we need to return the top trending hashtag in index 0 of S
    else 
        return E[S[0]].hashtag;
}
void Trendtracker::top_three_trends(vector<string> &T){
    T.clear();

    if(E.size() == 1)
        // for this check we are testing for only 1 hashtag being the top 3 trend 
        T.push_back(E[0].hashtag);
    else{
        if(S.size() == 0){
            // if empty then we just add first hashtags in E to T
            T.push_back(E[0].hashtag);
            T.push_back(E[1].hashtag);
            T.push_back(E[1].hashtag);
        }
        else if(S.size() == 1){
            // if S is size 1 then we add S[0] to find the hashtag in E and it to T
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[1].hashtag);
            T.push_back(E[2].hashtag);
        }
        else if(S.size() == 2){
            // when S is size two then we add the have S[0] and S[1] to E to then add to T
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[S[1]].hashtag);
            T.push_back(E[2].hashtag);

        }else if(S.size() == 3){
            // here if S is size 3 we have top 3 trends so we add those to T 
            T.push_back(E[S[0]].hashtag);
            T.push_back(E[S[1]].hashtag);
            T.push_back(E[S[2]].hashtag);
        }
    }
}