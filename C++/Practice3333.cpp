#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
void printList(vector<double>X){
    for(auto i: X){
        cout<<i<<endl;
    }
}

int main()
{
    vector<double> X;
    
    X.push_back(15.3);
    X.push_back(8);
    X.push_back(568);
    X.push_back(45);
    X.push_back(3.14);
    X.push_back(93.7);
    X.push_back(703);
    X.push_back(57);
    X.push_back(347.2);
    X.push_back(1.5);
    X.push_back(752);
    X.push_back(57);
    X.push_back(12);
    X.push_back(53);

    printList(X);
    return 0;
}