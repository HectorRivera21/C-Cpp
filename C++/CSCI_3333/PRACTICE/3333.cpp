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

double medium(std::vector<double>& A, std::vector<double>& B){
    int n = A.size();
    int m = B.size();

    if(n < m){
        return medium(B, A); //make sure b is the smaller one
    }
    int low = 0;
    int high = n;
    while(high >= low){
        int mid = (low + high)/2;
        int Cmid = (n+m+1)/2 - mid; 
        double leftA = (mid == 0) ? -1 : A[mid-1];
        double rightA = (mid == n) ? INT_MAX : A[mid];
        double leftB = (Cmid == 0) ? -1 : B[Cmid -1];
        double rightB = (Cmid == m) ? INT_MAX : B[Cmid];

        if(leftA <= rightB && leftB <= rightA){
            if((n+m)%2==0){
                return (std::max(leftA, leftB)+ std::min(rightA, rightB)) / 2;
            }else {
                return std::max(leftA,leftB);
            }
        }
        else if(leftA > rightB){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return -1;
}
 bool compareFreq(double a, double b){
    return a < b;

}

int main(){
    
    std::vector<double> A;
    std::vector<double> B;
    
    
    for(int i  = rand()%50+1;i <= 50; i++){
        A.push_back(i);
        B.push_back(i);
    }
    A.push_back(23);
    B.push_back(24);
    B.push_back(25);
    std::sort(A.begin(),A.end(),compareFreq);
    std::sort(B.begin(),B.end(),compareFreq);
    std::cout << medium(A, B);



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