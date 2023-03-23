#include <algorithm>
#include "autocompleter.h"

Autocompleter::Autocompleter(){
    root = new Node();
    count = 0;
}
void Autocompleter::insert(string x, int freq){
    Node* temp = root;
    Entry e = {x,freq};
    root->top.push_back(e);
    sort(root->top.begin(),root->top.end(),compareFreq);
    if (temp->top.size() > 3){
        root->top.pop_back();
    }
    for (char c : x) {
        if (temp->children[c] == nullptr) {
            temp->children[c] = new Node();
        }
        temp = temp->children[c];
        // check if we need to add the current string to the top completions
        bool found = false;
        for (Entry& e : temp->top) {
            if (e.s == x) {
                e.freq = freq;
                found = true;
                break;
            }
        }
        if (!found) {
            Entry entry = {x, freq};
            temp->top.push_back(entry);
        }
        // sort the top completions in descending order by frequency
        sort(temp->top.begin(), temp->top.end(), compareFreq);
        // truncate the top completions to three entries
        if (temp->top.size() > 3) {
            temp->top.resize(3);
        }
    }
    // mark the end of the string
    if (!temp->marked) {
        temp->marked = true;
        count++;
    }

}

int Autocompleter::size(){
    return count;
}
void Autocompleter::completions(string x, vector<string> &T)
{
    T.clear();
    
    Node* temp = root;

    for (char c : x) {
        temp = temp->children[c];
        if (temp == nullptr) return;
    }

    for (Entry& e : temp->top) {
        T.push_back(e.s);
    }
}