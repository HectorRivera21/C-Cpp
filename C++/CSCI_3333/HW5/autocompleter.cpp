#include "autocompleter.h"

Autocompleter::Autocompleter(){
    root = new Node();
    count = 0;
}
void Autocompleter::insert(string x, int freq){
    Node* temp = root;
    Entry e = {x, freq};
    for(int i = 0; i< x.size();i++){
        if(temp->children[x[i]] == nullptr){
            temp->children[x[i]] == new Node();
        }
        temp = temp->children[x[i]];
    }
    temp->marked == true;
    count += 1;
}
int Autocompleter::size(){
    return count;
}

// void Autocompleter::completions(string x, vector<string> &T)
// {
//     Node* temp = root;
//     if(temp == nullptr){

//     }
//     else{
//         for(int i = 0; i< 256; i++){
//             if(temp->children[x[i]]==nullptr){
                
//             }
//             else{
//                 temp = temp->children[x[i]];
//             }

//         }
//     }
// }