#include <iostream>
#include <vector>
#include <string>
#include "trendtracker.h"

using namespace std;
Trendtracker::Trendtracker(){

}
//////////////////////////////////////////
void Trendtracker::insert(string ht){
    Entry e;
    /* 
        looping through vector provided in class to check if
        the hashtag is already in the vector if so just return dont do anything
    */
    for(auto i : E){
        if(i.hashtag == ht){
            return;
        }
    }
    // how heavy are your dumbells
    /* 
        e is set to ht
        e pop is set to 0 since none have been tweeted yet
        then we push the new entry object into E
    */
    e.hashtag = ht;
    e.pop = 0;
    E.push_back(e);

}
//////////////////////////////////////////
int Trendtracker::size(){
    // return the size of the vector E
    return E.size();
}
//////////////////////////////////////////
void Trendtracker::tweeted(string ht){
    // we loop through the vector check if the hashtag is in the vector
    for(auto &i: E)
        if(i.hashtag == ht)
            //we then increment pop for that hashtag
            i.pop +=1;
}
//////////////////////////////////////////
int Trendtracker::popularity(string name){
    //we loop through the vector 
    for(auto i: E)
     //check if hashtag is equal to name
      if(i.hashtag == name)
        //then we return the popularity
        return i.pop;
    return -1;
    
}
//////////////////////////////////////////
string Trendtracker::top_trend(){
    // size zero do nothing
    if(E.size()==0){
        return "";
    }
    //placeholder for current highest popularity
    int tempPR = -1;
    //empty string for current trending hashtag
    string Top_Trending;
    //iterate through E
    for(auto i : E){
        // if i elements pop is greater than tempPR
        // set tempPR to i.pop and top_tending to i.hashtag 
        if(i.pop > tempPR){
            tempPR = i.pop;
            Top_Trending = i.hashtag;
        }
    }
    //return the top trending hashtag
    return Top_Trending;
}
void Trendtracker::top_three_trends(vector<string> &T){
    T.clear();
    // keep track of popularity and hashtags
    int max1=-1, max2=-1, max3=-1;
    string trend1, trend2, trend3;
    // iterate through E
    for(auto &i : E)
    {
        // checking the top 3 trends 
        // then updating top 3 accordingly 
        if(i.pop > max1)
        {
            max3 = max2;
            trend3 = trend2;
            max2 = max1;
            trend2 = trend1;
            max1 = i.pop;
            trend1 = i.hashtag;
        }
        else if(i.pop > max2){
            max3 = max2;
            trend3 = trend2;
            max2 = i.pop;
            trend2 = i.hashtag;
        }
        else if(i.pop>max3){
            max3 = i.pop;
            trend3 = i.hashtag;
        }
        
    }
    /* 
        Add the top 3 trending hashtags to the input 
        vector T if the max1, max2 and max3 are not -1
    */
    if(max1!=-1)
        T.push_back(trend1);
    if(max2 != -1)
        T.push_back(trend2);
    if(max3 != -1)
        T.push_back(trend3);

}
void Trendtracker::remove(string ht){
    //iterate through vector 
    for(int i = 0; i < E.size(); i++)
        // check for ht in the vector
        if (E[i].hashtag == ht)
            //remove the element at the specified index
            E.erase(E.begin() + i); 
}
void Trendtracker::top_k_trends(vector<string> &T, int k){
    //makesure vector has nothing in it
    T.clear();
    //iterate through k times
    for(int i = 0; i < k ;i++){
        //placeholders for top trending hashtags and idex of hashtag
        int bigPOP = 0, idx_max = -1;
        //iterate through E
        for(int j = 0; j < E.size();j++){
            // check if the popularity has a higher pop than current
            if(E[j].pop > bigPOP){
                //update bigPOP and idx_max
                bigPOP = E[j].pop;
                idx_max = j;
            }
        }
        //add the current top trend to vector T
        T.push_back(E[idx_max].hashtag);
        //set pop to zero to avoid duplicate top hashtags
        E[idx_max].pop = 0;
    }
}