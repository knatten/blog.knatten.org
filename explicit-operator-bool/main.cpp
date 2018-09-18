#include <iostream>
#include <cassert>

class handle {
public:
    handle(int value) : value(value){}
    int value;

    operator bool() { return value != 0; }
};

/* bool operator<(const handle& lhs, const handle& rhs) { return lhs.value < rhs.value; } */

void do_something_with(const handle& h) {}

int main() {
    handle one(1);
    assert(one.value == 1);

    if (one) {do_something_with(one);}

    handle zero(0);
    assert((bool)zero == false);
    assert((bool)one == true);

    handle two(2);
    assert(one < two);
}
