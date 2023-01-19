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
class Computer
{
	public:
		string gpu;
		string cpu;
		int ram;
		Computer(string x, string y, int z);
		void nice();
};
class Employee {
  private:
    // Private attribute
    int salary;

  public:
		// Setter
		void setSalary(int s) {
			salary = s;
		}
		// Getter
		int getSalary() {
			return salary;
		}
};
class Vehicle {
  public:
    string brand = "Ford";
    void honk() {
      cout << "Tuut, tuut! \n" ;
    }
};

// Derived class
class Car: public Vehicle {
  public:
    string model = "Mustang";
};
int Example::add(int a, int b){
	return a+b;
}
Computer::Computer(string x, string y, int z){   
	cpu = x;
	gpu = y;
	ram = z;
}
void Computer::nice(){
	cout<<"nice";
}

int main()
{
	//creation of obj
	Example obj;
	Computer expensive("INTEL","NVIDA",3600);
	Computer cheap("AMD","RADEON",3600);
	Employee myObj;
	Car myCar;

	cout <<"integer from class example: "<<obj.num<<endl;
	cout <<"string from class example: "<<obj.hello<<endl;
	obj.HelloWorld();
	cout <<"9+8="<<obj.add(9,8)<<endl;
	cout <<"---------------------------------------------"<<endl;
	cout <<"CONSTRUCTORS"<<endl;
	cout <<"CPU: "<<cheap.cpu<<" "<<"GPU: "<<cheap.gpu<<" "<<"RAM: "<<cheap.ram<<endl;
	cout <<"CPU: "<<expensive.cpu<<" "<<"GPU: "<<expensive.gpu<<" "<<"RAM: "<<expensive.ram<<endl;
	myObj.setSalary(50000);
	cout <<"SALARY: "<< myObj.getSalary()<<endl;
	myCar.honk();
	cout << myCar.brand + " " + myCar.model;
	cout <<"-----------------------------------------------"<<endl;
	expensive.nice();
	return 0;
}