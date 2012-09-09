#include <iostream>

using std::cout;
using std::endl;

class Parent
{
public:
    Parent(int p=0.0) : p(p)
    {
        cout << "Parent(" << p << ")" << endl;
    }

    int p;
};

class Member
{
public:
    Member(int m=0.0) : m(m)
    {
        cout << "Member(" << m << ")" << endl;
    }

    Member& operator=(const Member& rhs)
    {
            cout << "Member is copied" << endl;
            m = rhs.m;
    }

    int m;
};

//snippetysnip_begin:cleaned
class Derived : public Parent
{
public:
    Derived() : Parent(7), foo(10), bar(foo*2), m(42) {}

    int foo;
    int bar;
    Member m;
};
//snippetysnip_end


int main()
{
    Derived d;
    cout << d.p << " " << d.foo << " " << d.bar << " " << d.m.m << endl;
};


//!g++ -std=c++0x -o main2 main2.cpp && ./main2
