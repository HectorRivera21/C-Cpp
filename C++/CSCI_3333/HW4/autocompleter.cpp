#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "autocompleter.h"

Autocompleter::Autocompleter(){
    root = nullptr;
}
int Autocompleter::size_recurse(Node* p){
    if(p == nullptr) return 0;

    return 1 + size_recurse(p->right) + size_recurse(p->left);
}

void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C){
    if (p == nullptr)
        return;

    if (p->e.s.find(x) == 0) {
        C.push_back(p->e);
    }

    if (p->e.s >= x) {
        completions_recurse(x, p->left, C);
    }
    if (p->e.s.substr(0, x.length()) <= x) {
        completions_recurse(x, p->right, C);
    }
    
}
void Autocompleter::insert_recurse(Entry e, Node* &p){
    if(p == nullptr)
    {
        p = new Node(e);
    }
    else
    {
        if(e.s < p->e.s)
        {
            insert_recurse(e, p->left);
        }
        else if (e.s > p->e.s)
        {
            insert_recurse(e, p->right);
        }
    }
    rebalance(p);
    update_height(p);
}
void Autocompleter::rebalance(Node* &p){
    if(height(p->left) > height(p->right)+1){
        if(height(p->left->left) > height(p->left->right))
            right_rotate(p);
        else
            left_right_rotate(p);
    }
    else if(height(p->right) > height(p->left)+1)
    {
        if(height(p->right->right) > height(p->right->left))
            left_rotate(p);
        else
           right_left_rotate(p);
    }
}
void Autocompleter::right_rotate(Node* &p){
    Node* A = p;
	Node* B = p->left;
    Node* bright = B->right;

    A->left = bright;
    B->right = A;
    p = B;

    update_height(A);
    update_height(B);
}
void Autocompleter::left_rotate(Node* &p){
    Node* A = p;
    Node* B = p->right;
    Node* bleft = B->left;
    
    A->right = bleft;
    B->left = A;
	p = B;

    update_height(A);
    update_height(B);
}
void Autocompleter::right_left_rotate(Node* &p){
    right_rotate(p->right);
    left_rotate(p);
}
void Autocompleter::left_right_rotate(Node* &p){
    left_rotate(p->left);
    right_rotate(p);
}

void Autocompleter::insert(string x, int freq){
    Entry e = {x, freq};
    insert_recurse(e, root);
}

int Autocompleter::size(){
    return size_recurse(root);
}

void Autocompleter::completions(string x, vector<string> &T){
    T.clear();
    vector<Entry> C;
    C.clear();
    completions_recurse(x, root, C);

    std::sort(C.begin(), C.end(), compareFreq);

    for (int i = 0; i < min(3, (int)C.size()); i++) {
        T.push_back(C[i].s);
    }
}