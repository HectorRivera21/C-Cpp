#include <iostream>
#include <vector>
#include <string>
#include "autocompleter.h"

Autocompleter::Autocompleter(){
    root = nullptr;
}
int Autocompleter::size_recurse(Node* p){
    if(p == nullptr) return 0;

    return 1 + size_recurse(p->right) + size_recurse(p->left);
}
// void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C){

// }
void Autocompleter::insert_recurse(Entry e, Node* &p){
    if(p == nullptr)
    {
        p = new Node(e);
    }
    else
    {
        if(e.s< p->e.s)
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
            left_rotate(p);
    }
    else if(height(p->right) > height(p->left)+1)
    {
        if(height(p->right->right) > height(p->right->left))
            left_rotate(p);
        else
            right_rotate(p);
    }
}
void Autocompleter::right_rotate(Node* &p){
    Node* A = p->left;
    Node* B = A->right;
    p->left = B;
    B = p;
    p = A;
    update_height(p->right);
    update_height(p);
}
void Autocompleter::left_rotate(Node* &p){
    Node* A = p->right;
    Node* B = A->left;
    p->right = B;
    B = p;
    p = A;
    update_height(p->left);
    update_height(p);
}

void Autocompleter::insert(string x, int freq){
    Entry e = {x, freq};
    insert_recurse(e, root);
}

int Autocompleter::size(){
    return size_recurse(root);
}

// void Autocompleter::completions(string x, vector<string> &T){

// }