#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
//snippetysnip_begin:old_vec_init
    int tmp_v[] = {1, 1, 2, 3, 5, 8};
    vector<int> old_v(tmp_v, tmp_v + sizeof(tmp_v) / sizeof(tmp_v[0]));
//snippetysnip_end

//snippetysnip_begin:new_vec_init
    vector<int> new_v = {1, 1, 2, 3, 5, 8};
//snippetysnip_end

//snippetysnip_begin:ints
    vector<pair<int, string>> ints = {{1, "one"}, {2, "two"}};
//snippetysnip_end

//snippetysnip_begin:old_loop
    for (vector<pair<int, string>>::const_iterator it = ints.begin(); it != ints.end(); ++it)
    {
        cout << it->first << ":" << it->second << " ";
    }
//snippetysnip_end
    cout << endl;

//snippetysnip_begin:auto
    for (auto it = ints.begin(); it != ints.end(); ++it)
    {
        cout << it->first << ":" << it->second << " ";
    }
    cout << endl;
//snippetysnip_end

//snippetysnip_begin:range_for
    for (auto& elm : ints)
    {
        cout << elm.first << ":" << elm.second << " ";
    }
    cout << endl;
//snippetysnip_end

//snippetysnip_begin:find_old
    class CompareString
    {
        public:
            CompareString(string s) : s(s) {}
            bool operator()(const pair<int,string>& p) { return p.second == s; };
        private:
            string s;
    };

    auto it = find_if(ints.begin(), ints.end(), CompareString("two"));
//snippetysnip_end

//snippetysnip_begin:find_lambda
    auto it2 = find_if(ints.begin(), ints.end(),
        [](const pair<int,string>& p) { return p.second == "two";});    
//snippetysnip_end

    cout << it2->first << endl;
}
