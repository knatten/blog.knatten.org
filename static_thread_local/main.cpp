#include <iostream>
#include <vector>
#include <thread>

#ifdef __GNUC__
#define thread_local __thread //GCC doesn't have C++11 thread_local yet
#endif

using namespace std;

//snippetysnip_begin:helper
class Helper 
{
public:
    Helper(char id)
    {
        cout << "Helper created for thread " << id;
    }
};
//snippetysnip_end

//snippetysnip_begin:process
class Processor
{
public:
    void process(char data, int iteration)
    {
        cout << "Iteration " << iteration << " ";
        Helper h(data);
        //Use the helper object
        cout << endl;
    }
//snippetysnip_end


//snippetysnip_begin:threadlocal
    void process_threadlocal(char data, int iteration)
    {
        cout << "Iteration " << iteration << " ";
        static thread_local Helper* h = nullptr; 
        if (h == nullptr)
            h = new Helper(data);
        //Use the helper object
        cout << endl;
    }
//snippetysnip_end

};

//snippetysnip_begin:main
int main() 
{
    Processor processor;

    cout << endl << "LOCAL" << endl;
    for (char thread_id = 'A'; thread_id <= 'C'; ++thread_id) {
        thread([&]() {
            for (size_t i = 0; i < 3; ++i) {
                processor.process(thread_id, i);
            }
        }).join();
    }

    cout << endl << "STATIC THREAD LOCAL:" << endl;
    for (char thread_id = 'A'; thread_id <= 'C'; ++thread_id) {
        thread([&]() {
            for (size_t i = 0; i < 3; ++i) {
                processor.process_threadlocal(thread_id, i);
            }
        }).join();
    }

}
//snippetysnip_end

//!g++ -Wextra -Weffc++ -std=c++0x -pthread -o main main.cpp && ./main
