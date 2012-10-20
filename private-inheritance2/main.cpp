#include <string>
#include <iostream>

using namespace std;

//snippetysnip_begin:LanguageQuality
class LanguageQuality
{
public:
    virtual ~LanguageQuality() {}

    double quality() const
    {
        return 100.0 / charsForHelloWorld();
    }
protected:
    virtual int charsForHelloWorld() const = 0;
};
//snippetysnip_end

//snippetysnip_begin:CppInfo
class CppInfo
{
public:
    string info()
    {
        return "Language: C++\nCreator : Bjarne Stroustrup\nQuality : ??";
    }
};
//snippetysnip_end

//snippetysnip_begin:CppInfo_UsingInheritance
class CppInfo_UsingInheritance : private LanguageQuality
{
public:
    string info()
    {
        return "Language: C++\nCreator : Bjarne Stroustrup\nQuality : " + to_string(quality());
    }
private:
    int charsForHelloWorld() const
    {
        return string("#include <iostream>\nint main() { std::cout << \"Hello World\"; }").size();
    }
};
//snippetysnip_end

//snippetysnip_begin:CppQuality
class CppQuality : public LanguageQuality
{
protected:
    int charsForHelloWorld() const 
    {
        return string("#include <iostream>\nint main() { std::cout << \"Hello World\"; }").size();
    }
};
//snippetysnip_end

//snippetysnip_begin:CppInfoMember
class CppInfoMember 
{
public:
    string info()
    {
        return "Language: C++\nCreator : Bjarne Stroustrup\nQuality : " + to_string(cppQuality.quality());
    }
private:
    CppQuality cppQuality;
};
//snippetysnip_end

class JavaQuality : public LanguageQuality
{
protected:
    int charsForHelloWorld() const 
    {
        return string("public class HelloWorld\npublic static void main(String[] args) { System.out.println(\"Hello World\"); }}").size();
    }
};

class JavaInfoMember 
{
public:
    string info()
    {
        return "Language: Java\nCreator : James Gosling\nQuality : " + to_string(javaQuality.quality());
    }
private:
    JavaQuality javaQuality;
};

class PythonQuality : public LanguageQuality
{
protected:
    int charsForHelloWorld() const 
    {
        return string("print \"Hello World\"").size();
    }
};

class PythonInfoMember 
{
public:
    string info()
    {
        return "Language: Python\nCreator : Guido van Rossum\nQuality : " + to_string(pythonQuality.quality());
    }
private:
    PythonQuality pythonQuality;
};

int main()
{
    cout << CppInfo().info() << endl;
    cout << CppInfo_UsingInheritance().info() << endl;
    cout << CppInfoMember().info() << endl;
    cout << JavaInfoMember().info() << endl;
    cout << PythonInfoMember().info() << endl;
}
//:!g++-4.7 -o main main.cpp && ./main
