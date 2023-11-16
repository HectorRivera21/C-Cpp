#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;

typedef struct{
    vector<int> x = {0,1,1,0};
    vector<int> y = {0,1,0,1};
    vector<int> CLASS;
}Model;
typedef struct{
    vector<float> w;
}Weight;

void updateW(Model a)
{
    (void)a;
    float ep = 0.2;
    (void)ep;
}

vector<float> cost(Weight w,vector<int> x, vector<int>y)
{   
    vector<float>sum;
    size_t n = x.size();
    size_t m = a.w1.size();
    for(size_t i = 0; i< m;++i){
        float add = 0.0f;
        for(size_t j = 0; j<n;++j){
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

double gradient_decent(double side)
{
    double side2 = side*side;
    return side2;
}

int main(){

    Model *A;
    A->x = {0,1,1,0};
    A->y = {0,1,0,1};
    A->CLASS = {-1,1,-1,1};  
    Weight *W;
    W->w[0] = 0.5f;
    W->w[1] = -0.5f;
    W->w[2] = -0.5f;
    float ep = 0.2f;
    double side = gradient_decent(20);


    return 0;
}