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
void call_get();
bool get_in_argument(int*&);
void call_get_in_argument();
void call_get_or_throw();
int* get_or_throw();
Result<int> get_result();

int main() {
    cout << "------" << boolalpha << endl;
    /* call_get(); */
    /* call_get_in_argument(); */
    call_get_or_throw();


    /* Result<int> i7 = get_result(); //true, 0x10d0e509c */
    /* Result<int> i8 = get_result(); //false, null */
}

void call_get() {
    //snippetysnip_begin:call_get
    int* success = get();
    cout << success << endl; //0x101d78118
    cout << *success << endl; //1

    int* failure = get();
    cout << failure << endl; //0x0
    cout << *failure << endl; //segfault!
    //snippetysnip_end
}

void call_get_in_argument() {
    //snippetysnip_begin:call_get_in_argument
    int* success;
    bool ok = get_in_argument(success);
    cout << ok << " " << success << endl; //true 0x10d3ce11c
    cout << *success << endl; //1

    int* failure = nullptr;
    bool ok2 = get_in_argument(failure);
    cout << ok2 << " " << failure << endl;  //false 0x0
    cout << *failure << endl; //segfault!
    //snippetysnip_end
}

void call_get_or_throw() {
    //snippetysnip_begin:call_get_or_throw
    int* success = get_or_throw();
    cout << success << endl; //0x101d78118
    cout << *success << endl; //1

    int* failure = get_or_throw(); //exception
    cout << failure << endl; //never reached
    cout << *failure << endl; //never reached
    //snippetysnip_end
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

Result<int> get_result() {
    static int i = 0;
    return i++ == 0
        ? Result<int>{true, &i}
        : Result<int>{false, nullptr};
}
