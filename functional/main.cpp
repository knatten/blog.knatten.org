#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <iostream>
#include <utility>
#include <vector>

//snippetysnip_begin:sum_mean
double sum(const std::vector<double>& v)
{
    return std::accumulate(v.begin(), v.end(), 0, std::plus<double>());
}

double mean(const std::vector<double>& v)
{
    return sum(v) / v.size();
}

double squared(double d)
{
    return d*d;
}

//snippetysnip_end

namespace stateful {
//snippetysnip_begin:stateful
    void square(std::vector<double>& v)
    {
        std::transform(v.begin(), v.end(), v.begin(), [](double d) { return d*d; });
    }

    double rms(std::vector<double>& v)
    {
        square(v);
        double the_mean = mean(v);
        double the_rms = std::sqrt(the_mean);
        return the_rms;
    }

    int main()
    {
        std::vector<double> v = {1,2,3};
        double the_rms = rms(v);
        std::cout << the_rms << std::endl;
        return 0;
    }
//snippetysnip_end
}

namespace slow {
//snippetysnip_begin:slow
    std::vector<double> squared(std::vector<double> v)
    {
        std::transform(v.begin(), v.end(), v.begin(), [](double d) { return d*d; });
        return v;
    }

    double rms(const std::vector<double>& v)
    {
        return std::sqrt(mean(squared(v)));
    }

    int main()
    {
        std::cout << rms({1,2,3}) << std::endl;
        return 0;
    }
//snippetysnip_end
}

namespace fast {
//snippetysnip_begin:fast
    std::vector<double> squared(std::vector<double>&& v)
    {
        std::transform(v.begin(), v.end(), v.begin(), [](double d) { return d*d; });
        return std::move(v);
    }

    double rms(std::vector<double>&& v)
    {
        return std::sqrt(mean(squared(std::move(v))));
    }

    int main()
    {
        std::cout << rms({1,2,3}) << std::endl;
        return 0;
    }
//snippetysnip_end
}

int main()
{
    stateful::main();
    slow::main();
    fast::main();

    //snippetysnip_begin:invalid
    std::vector<double> v = {1,2,3};
    //rms(v); //invalid initialization of reference of type ‘std::vector<double>&&’ from expression of type ‘std::vector<int>’
    //snippetysnip_end
    fast::rms(std::move(v)); 
    fast::rms(std::vector<double>(v)); 
}


//g++-4.7 -Wall -std=c++0x -o main main.cpp && ./main
