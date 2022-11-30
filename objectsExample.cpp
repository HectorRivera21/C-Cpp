#include <iostream>
#include <stdio.h>
using namespace std;

class Example
{
    private:
     int key;
    public:
        int num = 15;
        string hello = "hello";
        void HelloWorld(){
            cout<<"HelloWorld"<<endl;
        }
        int add(int a, int b);
}; 

int Example::add(int a, int b){
    return a+b;
}

int main()
{
    //creation of obj
    Example obj;
    
    cout <<"integer from class example: "<<obj.num<<endl;
    cout <<"string from class example: "<<obj.hello<<endl;
    obj.HelloWorld();
    cout <<"9+8="<<obj.add(9,8)<<endl;
    return 0;
}