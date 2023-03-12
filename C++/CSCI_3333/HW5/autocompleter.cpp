#include "autocompleter.h"

Autocompleter::Autocompleter(){
    root = new Node();
    count = 0;
}
void Autocompleter::insert(string x, int freq){
    Node* temp = root;
    Entry e = {x,freq};
    temp->top.push_back(e);
    sort(temp->top.begin(), temp->top.end(), [](const Entry& a, const Entry& b) {
        return a.freq > b.freq;
    });
    while(temp->top.size()>3){
        temp->top.pop_back();
    }
    for (char c : x) {
        if (temp->children[c] == nullptr) {
            temp->children[c] = new Node();
        }
        temp =temp->children[c];
        // check if we need to add the current string to the top completions
        bool found = false;
        for (Entry& e : temp->top) {
            if (e.s == x) {
                e.freq += freq;
                found = true;
                break;
            }
        }
        if (!found) {
            Entry entry = {x, freq};
            temp->top.push_back(entry);
        }
        // sort the top completions in descending order by frequency
        sort(temp->top.begin(), temp->top.end(), [](const Entry& a, const Entry& b) {
            return a.freq > b.freq;
        });
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

    Node *temp = root;

    // Traverse down the trie, following the prefix 'x'.
    for (char c : x) {
        if (temp->children[c] == nullptr) {
            return;
        temp = temp->children[c];
    }

    // Traverse down the trie, collecting the top 3 most frequent completions.
    vector<Entry> completions = temp->top;
    sort(completions.begin(), completions.end(), [](const Entry &a, const Entry &b) {
        return a.freq > b.freq;
    });

    // If there are less than 3 completions, add all of them to T.
    for (int i = 0; i < min((int)completions.size(), 3); i++) {
        T.push_back(completions[i].s);
    }
}