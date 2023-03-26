#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <algorithm>


// void D(int n)
// {
//     int time = 0;
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < i * i; j++)
//             for (int k = 0; k < j*j; k++)
//                 time++;
//     // std::cout<<time<< std::endl;
// }
// void ncubed (int n){
//     int time = 0;
//     for(int i = 0; i < n;i++)
//         for(int j=0;j<n;j++)
//             for(int k = 0; k<n;k++)
//                 time++;
// //    std::cout<<time;
// }
int main(){
    //MAP IDEAS//
    // std:: vector<std::pair<std::string, int>> vHeap;
    // std::unordered_map<std::string, int> uMap;
    // uMap.insert({"lol", 23});
    // uMap.insert({"nice", 39});
    // uMap.insert({"too", 2});
    // uMap.insert({"hi", 20000});
    // uMap.insert({"cool", 50});

    // auto i = uMap.find("hi");
    // if(i != uMap.end()){
    //     i->second = 10;
    //     std::cout <<i->first <<i->second;
    // }


    // auto start = std::chrono::high_resolution_clock::now();
    // D(10);
    // auto finish = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = finish-start;
    // std::cout<< elapsed.count()<<std::endl;    

    // auto s = std::chrono::high_resolution_clock::now();
    // ncubed(10);
    // auto f = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<long double> nice = f-s;
    // std::cout<< nice.count();

     return 0;
}