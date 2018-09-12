#include <iostream>
#include <vector>

//snippetysnip_begin:classes
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
//snippetysnip_end

using namespace std;
int main() {
    /*
//snippetysnip_begin:vector_unique
    vector<unique_ptr<int>> vu{make_unique<int>(1), make_unique<int>(2)};
    //error: call to implicitly-deleted copy constructor of unique_ptr
//snippetysnip_end
    */
//snippetysnip_begin:vector_int
    vector<int> vi1{1,2,3};
    vector<int> vi2 = {1,2,3};
//snippetysnip_end

//snippetysnip_begin:vector_copyable
    Copyable c1(1);
    Copyable c2(2);
    vector<Copyable> vc1{c1, c2};
    vector<Copyable> vc2 = {c1, c2};
//snippetysnip_end

    /*
//snippetysnip_begin:vector_noncopyable
    NonCopyable n1(1);
    NonCopyable n2(2);
    vector<NonCopyable> vn1{n1, n2}; //error: call to deleted constructor of 'const NonCopyable'
    vector<NonCopyable> vn2 = {n1, n2}; //error: call to deleted constructor of 'const NonCopyable'
//snippetysnip_end

//snippetysnip_begin:vector_noncopyable_move
    vector<NonCopyable> vn3{std::move(n1), std::move(n2)}; //error: call to deleted constructor of 'const NonCopyable'
    vector<NonCopyable> vn3{NonCopyable(4), NonCopyable(5)}; //error: call to deleted constructor of 'const NonCopyable'
//snippetysnip_end
    */
}
