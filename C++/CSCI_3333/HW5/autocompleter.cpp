#include "autocompleter.h"

Autocompleter::Autocompleter(){
    root = new Node;
    count = 0;
}
void Autocompleter::insert(string x, int freq){
    Node* temp = root;
    for(char c : x)
    {
        if(temp->children[c] == nullptr)
            temp->children[c] = new Node;
        temp = temp->children[c];
    }
    if(temp->marked)
    {
        for(Entry& e : temp->top)
        {
            if(e.s == x)
            {
                e.freq += freq;
                return;
            }
        }
    }
    else
    {
        Entry e = {x, freq};
        temp->top.push_back(e);
        temp->marked = true;
        count ++;
    }
    
}
int Autocompleter::size(){
    return count;
}
void Autocompleter::completions(string x, vector<string> &T)
{
    T.clear();
    
    Node* temp = root;

    for(char c : x){
        temp = temp->children[c];
        if(temp == nullptr)return;
    }
    
}