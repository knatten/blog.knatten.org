#include <iostream>
#include <vector>

using namespace std;

class A
{
public:
    A() = default;
    A(const A& rhs) { cout << "Copy" << endl; }
};

int main()
{
    vector<A> a_vec(2);

    cout << "Range based for without &" << endl;
    //snippetysnip_begin:copy
    for (auto a : a_vec)
    {
    }
    //snippetysnip_end

    cout << "Range based for with &" << endl;
    //snippetysnip_begin:reference
    for (const auto& a : a_vec)
    {
    }
    //snippetysnip_end

    cout << "Iterating without &" << endl;
    //snippetysnip_begin:iterate
    for (auto a = a_vec.cbegin(); a != a_vec.cend(); ++a)
    {
    }
    //snippetysnip_end
}
