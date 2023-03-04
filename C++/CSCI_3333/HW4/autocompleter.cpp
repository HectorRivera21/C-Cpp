#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "autocompleter.h"

Autocompleter::Autocompleter(){
    // intialize root to null
    root = nullptr;
}
int Autocompleter::size_recurse(Node* p){
    // if root is null return 0
    if(p == nullptr) return 0;
    // resurse to the right and left subtrees and add 1 for the current node
    return 1 + size_recurse(p->right) + size_recurse(p->left);
}
void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C){
    if (p == nullptr)return;
    // if the current node's string starts with x
    // add its Entry to C
    if (p->e.s.find(x) == 0) {
        C.push_back(p->e);
    }
    // the current node's string is greater than or equal to x
    // search its left subtree
    if (p->e.s >= x) {
        completions_recurse(x, p->left, C);
    }
    // the current node's string has a prefix that is less than or equal to x
    // search its right subtree
    if (p->e.s.substr(0, x.length()) <= x) {
        completions_recurse(x, p->right, C);
    }
    
}
void Autocompleter::insert_recurse(Entry e, Node* &p){
    // if p is null create a new node with Entry e
    if(p == nullptr)
    {
        p = new Node(e);
    }
    else
    {
        // if e.s is less than p->e.s move to the left subtree
        if(e.s < p->e.s)
        {
            insert_recurse(e, p->left);
        }
        // else e.s is greater than p->e.s move to the right subtree
        else
        {
            insert_recurse(e, p->right);
        }
    }
    // rebalance avl tree p
    rebalance(p);
    // update the height of the tree 
    update_height(p);
}
//O(1)
void Autocompleter::rebalance(Node* &p){
    // if the left subtree is taller than the right subtree by more than 1 
    if(height(p->left) > height(p->right)+1){
        // check if the left_left subtree is taller than left_right
        if(height(p->left->left) > height(p->left->right))
            right_rotate(p);// perform right rotation
        else
            left_right_rotate(p);// perform left_right rotation
    }
    // if the right subtree is taller than the left subtree by more than 1
    else if(height(p->right) > height(p->left)+1)
    {
        // if the right_right subtree is taller that right_left
        if(height(p->right->right) > height(p->right->left))
            left_rotate(p);// perform left rotation 
        else
           right_left_rotate(p);// perform right_left rotation
    }
}
//O(1)
void Autocompleter::right_rotate(Node* &p){
    // initialize nodes to be rotated
    Node* A = p;
	Node* B = p->left;
    Node* bright = B->right;

    // rotate nodes
    A->left = bright;
    B->right = A;
    p = B;
    // update the height of nodes A and B after rotation
    update_height(A);
    update_height(B);
}
//O(1)
void Autocompleter::left_rotate(Node* &p){
    // initialize nodes to be rotated
    Node* A = p;
    Node* B = p->right;
    Node* bleft = B->left;
    // rotate nodes
    A->right = bleft;
    B->left = A;
	p = B;
    // update the height of nodes A and B after rotation
    update_height(A);
    update_height(B);
}
//O(1)
void Autocompleter::right_left_rotate(Node* &p){
    // perform a right rotation on p's right child
    right_rotate(p->right);
    // then perform a left rotation on p
    left_rotate(p);
}
//O(1)
void Autocompleter::left_right_rotate(Node* &p){
    // perform a left rotation on p's left child
    left_rotate(p->left);
     // then perform a right rotation on p
    right_rotate(p);
}

void Autocompleter::insert(string x, int freq){
    // create an entry with the given string and frequency
    Entry e = {x, freq};
    // insert the entry into the tree recursively, starting at the root
    insert_recurse(e, root);
}

int Autocompleter::size(){
    // return result of size_recurse
    return size_recurse(root);
}

void Autocompleter::completions(string x, vector<string> &T){
    T.clear();// clear vector T
    vector<Entry> C;
    C.clear();// clear vector C 

    // recurse to find all completions of x in the tree
    completions_recurse(x, root, C);

    // sort the completions by frequency
    std::sort(C.begin(), C.end(), compareFreq);

    // add up to three most frequent completions to T
    for (int i = 0; i < min(3, (int)C.size()); i++) {
        T.push_back(C[i].s);
    }
}