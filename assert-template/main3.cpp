//snippetysnip_begin:all
struct B{};

template <typename T>
struct A {
    //Assume sizeof(int) != 4
    static_assert(sizeof(int) == 4);
};
//snippetysnip_end
