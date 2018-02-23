//snippetysnip_begin:question
#include <iostream>

struct B {
  B() {
    std::cout << 'b';
  }
  ~B() {
    std::cout << 'B';
  }
};

struct D : B {
  D() {
    std::cout << 'd';
  }
  ~D() {
    std::cout << 'D';
  }
};

int main() {
  B* p = new D;
  delete p;
}
//snippetysnip_end
