#include <iostream>
#include <exception>

using namespace std;

//snippetysnip_begin:result
template <typename T>
struct Result {
    bool ok;
    T* pointer;
};
//snippetysnip_end

int* get();
bool get_in_argument(int*&);
int* get_or_throw();
Result<int> get_result();

void call_get();
void call_get_in_argument();
void call_get_or_throw();
void call_get_result();

void print(int* i);

int main() {
    cout << "------" << boolalpha << endl;
    /* call_get(); */
    /* call_get_in_argument(); */
    /* call_get_or_throw(); */
    call_get_result();
}

//snippetysnip_begin:get
//Returns a pointer the first time, then returns null
int* get() {
    static int i = 0;
    return i++ == 0 ? &i : nullptr;
}
//snippetysnip_end

//snippetysnip_begin:get_in_argument
//Returns ok and updates the result pointer the first time, then returns false and does not update result pointer
bool get_in_argument(int*& result) {
    static int i = 0;
    if (i++ == 0) {
        result = &i;
        return true;
    }
    return false;
}
//snippetysnip_end

//snippetysnip_begin:get_or_throw
int* get_or_throw() {
    static int i = 0;
    if (i++ > 0) {
        throw std::exception();
    }
    return &i;
}
//snippetysnip_end

//snippetysnip_begin:get_result
Result<int> get_result() {
    static int i = 0;
    return i++ == 0
        ? Result<int>{true, &i}
        : Result<int>{false, nullptr};
}
//snippetysnip_end

void call_get() {
    //snippetysnip_begin:call_get
    int* succeeding = get();
    if (succeeding != nullptr)
        print(succeeding); //0x1035f5118, 1 

    int* failing = get();
    if (failing != nullptr)
        print(failing); //Would have been: 0x0, segfault

    //snippetysnip_end
}

void call_get_in_argument() {
    //snippetysnip_begin:call_get_in_argument
    int* succeeding;
    bool ok = get_in_argument(succeeding);
    if (ok)
        print(succeeding); //0x10fe1a11c, 1

    int* failing = nullptr;
    bool ok2 = get_in_argument(failing);
    if (!ok2)
        print(failing); //Would have been: 0x0, segfault

    //snippetysnip_end
}

void call_get_or_throw() {
    //snippetysnip_begin:call_get_or_throw
    try {
        int* succeeding = get_or_throw();
        print(succeeding); //0x10756d120, 1
    } catch (...) {}

    try {
        int* failing = get_or_throw(); //exception
        print(failing); //Would have been: 0x0, segfault
    } catch (...) {}
    //snippetysnip_end
}

void call_get_result() {
    //snippetysnip_begin:call_get_result
    Result<int> succeeding = get_result();
    if (succeeding.ok)
        print(succeeding.pointer); //0x1063c1124, 1

    Result<int> failing = get_result();
    if (!failing.ok)
        print(failing.pointer); //Would have been: 0x0, segfault
    //snippetysnip_end
}

//snippetysnip_begin:print
void print(int* i) {
    cout << i << endl;
    cout << *i << endl;
}
//snippetysnip_end
