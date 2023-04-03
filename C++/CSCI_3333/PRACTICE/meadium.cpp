#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <algorithm>

// double medium(std::vector<double>& A, std::vector<double>& B){
//     // vector sizes
//     int n = A.size();
//     int m = B.size();
//     // check for if A is bigger than B runs in O(1)
//     if(n > m){
//         return medium(B, A); //make sure b is the smaller one
//     }
//     int low = 0;
//     int high = n;
//     // modified binary search which runs in O(log n)
//     while(high >= low){
//         // find mid of A vector
//         int Amid = (low + high)/2;
//         // find mid of B vector
//         int Bmid = (n+m+1)/2 - Amid;
//         //checks for if Amid / Bmid become to close to the start of the vector or end and assigns them values 
//         // that would check pass the check in the next stage this runs in O(1) 
//         double leftA = (Amid == 0) ? -1 : A[Amid-1];
//         double rightA = (Amid == n) ? INT_MAX : A[Amid];
//         double leftB = (Bmid == 0) ? -1 : B[Bmid-1];
//         double rightB = (Bmid == m) ? INT_MAX : B[Bmid];
//         // check for if leftA is greater than rightB and left B is greater than rightA
//         if(leftA <= rightB && leftB <= rightA){
//             //check if size of vectors combined is even or odd
//             if((n+m)%2==0){
//                 // return the average of the max of leftA or leftB and the min of rightA and rightB O(1)
//                 return (std::max(leftA, leftB)+ std::min(rightA, rightB)) / 2;
//             }else {
//                 //odd case return the max of leftA and left B O(1)
//                 return std::max(leftA,leftB);
//             }
//         }// leftA greater than rigthB
//         else if(leftA > rightB){
//             // move our high to Amid - 1 which would be the left of the vector O(n/2)
//             high = Amid - 1;
//         }
//         else{
//             // move that start of our vector to the mid + 1 being the right side of the vector O(n/2)
//             low = Amid + 1;
//         }
//     }
//     //if not found
//     return -1;
// }

int main(){
    // steps to add numbers to the vector
    // std::vector<double> A(7);
    // std::vector<double> B(9);
    
    
    // std::srand(unsigned(std::time(nullptr)));
    // std::generate(A.begin(), A.end(), std::rand);
    // std::generate(B.begin(), B.end(), std::rand);


    // std::sort(A.begin(),A.end(),[](double a, double b){return a<b;});
    // std::sort(B.begin(),B.end(),[](double a, double b){return a<b;});
    // std::cout <<"The Median Value: "<<medium(A, B);
    return 0;
}