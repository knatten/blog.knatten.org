#include <vector>

using namespace std;

vector<int> getNumbers();

void doStuffWith(vector<int> v);




//snippetysnip_begin:imperative
void square(vector<int>& v) { /*multiply each element with itself*/ }

void imperative()
{
    vector<int> v = getNumbers();
    square(v);
    doStuffWith(v);
}
//snippetysnip_end


//snippetysnip_begin:functional
vector<int> squared(const vector<int>& v) { /*return a new vector with squared elements*/ }

void functional()
{
    doStuffWith(
        squared(
            getNumbers()));
}
//snippetysnip_end


//g++-4.7 -Wall -std=c++0x -c examples.cpp
