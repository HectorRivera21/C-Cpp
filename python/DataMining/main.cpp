#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;

typedef struct{
    vector<int> w1;
    vector<int> w2;
    vector<int> w0;
    //Class A = 1, Class B = 0;
    vector<bool> CLASS;
}EQ;

vector<float> cost(EQ a,vector<int> x, vector<int>y)
{   
    vector<float>sum;
    size_t n = x.size();
    size_t m = a.w1.size();
    for(int i = 0; i< m;++i){
        float add = 0.0f;
        for(int j = 0; j<n;++j){
            float top = ((a.w1[i]*x[j])+(a.w2[i]*y[j])+a.w0[i]);
            float bot = sqrtf((float)(pow(a.w1[i],2)+pow(a.w2[i],2)));
            float loss = top/bot;
            if(a.CLASS[j] != false && loss < 0 )
            {
                add += abs(loss);
            }
            else if (a.CLASS[j] != true && loss > 0 )
            {
                add += abs(loss);
            }
        }
        sum.push_back(add);
    }
    return sum;
}

int main(){

    EQ a;
    vector<int> x = {0,3,4,8};
    vector<int> y = {0,3,5,0};
    a.w1 = {1,1,1}; 
    a.w2 = {1,-1,2};
    a.w0 = {-12,5,3};
    a.CLASS ={false,false,true,true};
    vector<float>print =  cost(a,x,y);
    for(int i = 0; i<print.size(); ++i){
        printf("line %d loss = %f\n",i,print[i]);
    }
    return 0;
}