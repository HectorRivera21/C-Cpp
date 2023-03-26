#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <algorithm>

double medium(std::vector<double>& A, std::vector<double>& B){
    int n = A.size();
    int m = B.size();

    if(n > m){
        return medium(B, A); //make sure b is the smaller one
    }
    int low = 0;
    int high = n;
    while(high >= low){
        int Amid = (low + high)/2;
        int Bmid = (n+m+1)/2 - Amid; 
        double leftA = (Amid == 0) ? -1 : A[Amid-1];
        double rightA = (Amid == n) ? INT_MAX : A[Amid];
        double leftB = (Bmid == 0) ? -1 : B[Bmid-1];
        double rightB = (Bmid == m) ? INT_MAX : B[Bmid];

        if(leftA <= rightB && leftB <= rightA){
            if((n+m)%2==0){
                return (std::max(leftA, leftB)+ std::min(rightA, rightB)) / 2;
            }else {
                return std::max(leftA,leftB);
            }
        }
        else if(leftA > rightB){
            high = Amid - 1;
        }
        else{
            low = Amid + 1;
        }
    }
    return -1;
}
int main(){
    std::vector<double> A;
    std::vector<double> B;
    
    
    for(int i  = rand()%10+1;i <= 25; i++){
        A.push_back(i);
    }
    for(int i  = rand()%10+1;i <= 25; i++){
        B.push_back(i);
    }
    std::sort(A.begin(),A.end(),[](double a, double b){return a<b;});
    std::sort(B.begin(),B.end(),[](double a, double b){return a<b;});
    std::cout << medium(A, B);
}