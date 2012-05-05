#include <iostream>
#include <string>

using namespace std;

class MyType;

//snippetysnip_begin:functions
void doSomethingWith(int i)           { cout << "int"    << endl; };
void doSomethingWith(double d)        { cout << "double" << endl; };
void doSomethingWith(const string& s) { cout << "string" << endl; };
void doSomethingWith(const MyType& m) { cout << "MyType" << endl; };
//snippetysnip_end

//snippetysnip_begin:new_function
void doSomethingWith(const void* i) { cout << "void*" << endl; };
//snippetysnip_end

int main()
{
//snippetysnip_begin:usage
    doSomethingWith(3);
    doSomethingWith("foo");
//snippetysnip_end
}
//!g++ -o main main.cpp && ./main
