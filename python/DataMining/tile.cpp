#include<iostream>
#include<cmath>

int main(){
    const double pi = 3.141592;
    double sina = 33.0f;
    double beta = 67.25f;
    double total = 0.0f;

    sina = sin(sina);
    sina = round(sina*(pi/1000.0));
    beta = cos(beta);
    beta = round(beta*1000)/1000;
    total = sina + beta;
    std::cout<<total;
 return 0;
}