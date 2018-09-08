#include <iostream>
#include <vector>

class Copyable {
public:
    Copyable(int i): i(i){}
    Copyable(const Copyable&) = default;
    Copyable(Copyable&&) = default;
    Copyable& operator=(const Copyable&) = default;
    Copyable& operator=(Copyable&&) = default;
    ~Copyable() = default;
    int i;
};

class NonCopyable {
public:
    NonCopyable(int i): i(i){}
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(const NonCopyable&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
    ~NonCopyable() = default;
    int i;
};

using namespace std;
int main() {
    vector<int> vi1{1,2,3};
    vector<int> vi2 = {1,2,3};

    Copyable c1(1);
    Copyable c2(2);
    vector<Copyable> vc1{c1, c2};
    vector<Copyable> vc2 = {c1, c2};

    NonCopyable n1(1);
    NonCopyable n2(2);
    /*
    vector<NonCopyable> vn1{n1, n2};
    vector<NonCopyable> vn2 = {n1, n2};
    */

    vector<NonCopyable> vn3{move(n1), move(n2)};
    vector<NonCopyable> vn3{NonCopyable(4), NonCopyable(5)};
}
