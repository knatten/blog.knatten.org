//snippetysnip_begin:classes
class Base
{
public:
    void pub() {}
private:
    void priv() {}
};

class DerivedPublic : public Base
{
};

class DerivedPrivate : private Base
{
};
//snippetysnip_end

//snippetysnip_begin:DP2
class DerivedPrivate2: private Base
{
public:
    void foo() { pub(); }
};
//snippetysnip_end

//snippetysnip_begin:not_derived
class NotDerived
{
public:
    void foo() { b.pub(); }
private:
    Base b;
};
//snippetysnip_end


int main()
{
    //snippetysnip_begin:public
    DerivedPublic derivedPublic;
    derivedPublic.pub();
    //derivedPublic.priv(); //error: ‘void Base::priv()’ is private
    //snippetysnip_end

    //snippetysnip_begin:private
    DerivedPrivate derivedPrivate;
    //derivedPrivate.pub(); //error: ‘void Base::pub()’ is inaccessible
    //derivedPrivate.priv(); //error: ‘void Base::priv()’ is private
    //snippetysnip_end

    //snippetysnip_begin:flapp
    DerivedPrivate2 derivedPrivate2;
    derivedPrivate2.foo();
    //derivedPrivate2.pub(); //error: ‘void Base::pub()’ is inaccessible
    //snippetysnip_end
}

//:!g++ -std=c++0x -o main main.cpp && ./main
