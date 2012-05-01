#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//snippetysnip_begin:classdef
struct DomainObject
{
    string label;
};
vector<DomainObject> objects;
//snippetysnip_end


ostream& operator<<(ostream& os, const vector<string>& v)
{
    for (auto& s : v)
    {
        os << s << ",";;   
    }
    os << endl;

    return os;
}

//snippetysnip_begin:stl-helper
string label_for(const DomainObject& obj)
{
    return obj.label;
}
//snippetysnip_end

int main()
{
    objects.push_back(DomainObject{"one"});
    objects.push_back(DomainObject{"two"});
    objects.push_back(DomainObject{"three"});

    {
    //snippetysnip_begin:transform_indexed
    vector<string> labels(objects.size());
    for (size_t i = 0; i < objects.size(); ++i)
        labels[i] = objects[i].label;
    //snippetysnip_end
    cout << labels;
    }

    { 
    //snippetysnip_begin:transform_stl
    vector<string> labels(objects.size());
    transform(objects.begin(), objects.end(), labels.begin(), label_for);
    //snippetysnip_end
    cout << labels;
    }

    { 
    //snippetysnip_begin:transform_lambda
    vector<string> labels(objects.size());
    transform(objects.begin(), objects.end(), labels.begin(), [](const DomainObject& o){return o.label;});
    //snippetysnip_end
    cout << labels;
    }

    {
    //snippetysnip_begin:find_if
    auto matched = find_if(objects.begin(), objects.end(), [](const DomainObject& o) { return o.label == "two"; });
    cout << matched->label << endl;
    //snippetysnip_end
    }

}

//!g++ -std=c++0x -o main main.cpp && ./main
