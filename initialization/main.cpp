#include <iostream>

using std::cout;
using std::endl;

//snippetysnip_begin:demo

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
            return *this;
    }

    int m;
};

class Derived : public Parent
{
public:
    Derived() : foo(10), bar(foo*2)
    {
        Parent(7);
        m = Member(42);
    }

    int bar;
    int foo;
    Member m;
};


int main()
{
    Derived d;
    cout << d.p << " " << d.foo << " " << d.bar << " " << d.m.m << endl;
}

//snippetysnip_end

//!g++ -std=c++0x -o main main.cpp && ./main
