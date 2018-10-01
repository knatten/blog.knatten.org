//snippetysnip_begin:all
struct B{};

template <typename T>
struct A {
    //Assume sizeof(B) != 4
    static_assert(sizeof(T) == 4);
};

A<B>* a; 
//snippetysnip_end
