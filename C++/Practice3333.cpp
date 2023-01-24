#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;


//Run time: O(n)
// void printList(vector<double> &X)
// {
//     for(auto i: X)
//         cout<<i<<endl;
    
// }
// int findSmallest(vector<double> &X, int begin, int end)
// {
//     int n = begin;
//     for(int i= begin;i<end;i++){
//         if(X[i]<X[n]){
//             n = i;
//         }
//     }  
//     return n;
// }
// //runtime: O(n^2)
// void SelectionSort(vector<double> &X)
// {
//     for(int i = 0;i<X.size();i++){
//         int smallIdx = findSmallest(X, i, X.size()-1);
//         swap(X[i], X[smallIdx]);
//     }
// }
//runtime: n log n
void heapSort(vector<double>&X){
    priority_queue<double> H;// a heap data structure
    //runtime step 1: O(n*log n)
    for(auto i: X)
        H.push(i);//O(log n)
    
    //runtime: O(n*log n)
    for(int i = 0; i<X.size();i++){
        X[i]=H.top(); //O(1)
        H.pop();      //O(log n)
    }
}
int linearSearch(vector<double> &X, int start, int end, double key){
    for(int i = start; i< end; i++)
        if(X[i] == key)
            return i;

    return -1;
}
int binarySearch(vector<double> &X, int start, int end, double key){
    int s = start;
    int e =  end;
    while(s <= e){
        int mid = (s + e)/2;
        if(X[mid] == key)
            return mid;
        else if(X[mid] > key)
           e = mid-1;
        else
            s = mid+1;
    }
    return -1;
}
int RecursiveBinarySearch(vector<double> &X, int start, int end, double key){

    if(end<start)
    {    
        return -1;
    }
    else{
        int mid = (start + end)/2;

        if(X[mid] == key)
            return mid;
        else if(X[mid] > key)
            return RecursiveBinarySearch(X,start,mid-1,key);
        else
            return RecursiveBinarySearch(X, mid+1, end, key);     
    }
}

int main()
{
    vector<double> X;
    //warmup 1
    // X.push_back(15.3);
    // X.push_back(8);
    // X.push_back(568);
    // X.push_back(45);
    // X.push_back(3.14);
    // X.push_back(93.7);
    // X.push_back(703);
    // X.push_back(57);
    // X.push_back(347.2);
    // X.push_back(1.5);
    // X.push_back(752);
    // X.push_back(57);
    // X.push_back(12);
    // X.push_back(53);

    X.push_back(1);
    X.push_back(2.3);
    X.push_back(3);
    X.push_back(4);
    X.push_back(5);
    X.push_back(6);
    X.push_back(7);
    X.push_back(8);
    X.push_back(9);
    X.push_back(10);
    X.push_back(11);
    X.push_back(12);

    // printList(X);

    cout<<endl<<endl;
    /*
        Class Warmup 1
    */
    // findSmallest(X, 0, X.size());
    // findSmallest(X, 5,8);
    // heapSort(X);

    // printList(X);

    // int huge = 1000000;
    // vector<double> giantList;
    // for(int i =0;i< huge;i++){
    //     giantList.push_back(rand());
    // }
    // auto start = chrono::high_resolution_clock::now();
    // heapSort(giantList);
    // auto finish = chrono::high_resolution_clock::now();

    // chrono::duration<double> elapsed = finish-start;
    // cout<<"nice "<< elapsed.count();    
    /*
        Class Warmup 2
    */
    cout<< linearSearch(X, 0, 12, 8) <<" Linear Search"<<endl;

    cout<< binarySearch(X, 0, 12, 4) <<" Binary Search"<<endl;

    cout<< RecursiveBinarySearch(X, 0, 12, 2.3)<<" Recursive Binary Search";

    return 0;
}