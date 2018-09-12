Have you ever wondered why you can't list-initialize vectors of non-copyable types? This is for instance not possible:

<!-- snippetysnip:main.cpp:vector_unique:(before='[sourcecode language="cpp"]', after='[/sourcecode]') -->

[sourcecode language="cpp"]
    vector<unique_ptr<int>> vu{make_unique<int>(1), make_unique<int>(2)};
    //error: call to implicitly-deleted copy constructor of unique_ptr
[/sourcecode]

<!-- snippetysnip_end:main.cpp:vector_unique -->

If you ever wondered, or if you now are, read on!

Since C++11, you're probably used to intitalizing vectors like this:

<!-- snippetysnip:main.cpp:vector_int:(before='[sourcecode language="cpp"]', after='[/sourcecode]') -->

[sourcecode language="cpp"]
    vector<int> vi1{1,2,3};
    vector<int> vi2 = {1,2,3};
[/sourcecode]

<!-- snippetysnip_end:main.cpp:vector_int -->

This of course also works with user defined types. Let's say you have a class `Copyable`, then you can for instance do:

<!-- snippetysnip:main.cpp:vector_copyable:(before='[sourcecode language="cpp"]', after='[/sourcecode]') -->

[sourcecode language="cpp"]
    Copyable c1(1);
    Copyable c2(2);
    vector<Copyable> vc1{c1, c2};
    vector<Copyable> vc2 = {c1, c2};
[/sourcecode]

<!-- snippetysnip_end:main.cpp:vector_copyable -->

The `Copyable` class is reproduced at the end of the post, but in short it has a constructor taking an `int`, and a `default`ed copy constructor, move constructor, copy assignment operator and move assignment operator.

Now what happens if we have a non-copyable class `NonCopyable`? It can also be seen at the end of the post, but is identical to `Copyable` except that the move constructor and move assignment operators have been `delete`ed.

<!-- snippetysnip:main.cpp:vector_noncopyable:(before='[sourcecode language="cpp"]', after='[/sourcecode]') -->

[sourcecode language="cpp"]
    NonCopyable n1(1);
    NonCopyable n2(2);
    vector<NonCopyable> vn1{n1, n2}; //error: call to deleted constructor of 'const NonCopyable'
    vector<NonCopyable> vn2 = {n1, n2}; //error: call to deleted constructor of 'const NonCopyable'
[/sourcecode]

<!-- snippetysnip_end:main.cpp:vector_noncopyable -->

Well, `n1` and `n2` are lvalues, so no wonder it tries to copy them. What if we turn them into `rvalues`, either with `std::move` or by creating temporaries?
<!-- snippetysnip:main.cpp:vector_noncopyable_move:(before='[sourcecode language="cpp"]', after='[/sourcecode]') -->

[sourcecode language="cpp"]
    vector<NonCopyable> vn3{move(n1), move(n2)}; //error: call to deleted constructor of 'const NonCopyable'
    vector<NonCopyable> vn3{NonCopyable(4), NonCopyable(5)}; //error: call to deleted constructor of 'const NonCopyable'
[/sourcecode]

<!-- snippetysnip_end:main.cpp:vector_noncopyable_move -->

So what's going on here? Let's see what the standard has to say in [dcl.init.list]¶1:
> _List-initialization_ is initialization of an object or reference from a _braced-init-list_.

A _braced-init-list_ is the `{elements, go, here}` syntax we saw above. The standard continues:

> Such an initializer is called an initializer list. (...) List-initialization can occur in direct-initialization or copy-initialization contexts.



#### Appendix: The `Copyable` and `Uncopyable` classes:

<!-- snippetysnip:main.cpp:classes:(before='[sourcecode language="cpp"]', after='[/sourcecode]') --,

[sourcecode language="cpp"]
class Copyable {
public:
    Copyable(int i): i(i){}
    Copyable(const Copyable&) = default;
    Copyable(Copyable&&) = default;
    Copyable& operator=(const Copyable&) = default;
    Copyable& operator=(Copyable&&) = default;
    ~Copyable() = default;
    int i;
};

class NonCopyable {
public:
    NonCopyable(int i): i(i){}
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(const NonCopyable&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
    ~NonCopyable() = default;
    int i;
};
[/sourcecode]

<!-- snippetysnip_end:main.cpp:classes --,

<hr>

{} is braced initialization. in this case it means list-initialization.

Copying an initializer-list does not copy the underlying elements, and the only way to iterate over it is by const pointers:
[support.initlist] only has
constexpr const E* begin() const noexcept; // first element
constexpr const E* end() const noexcept; // one past the last element

So there's no way to copy out of it.

Say something about this not being related to whether we direct initialize or copy initialize, the latter actually supports moving non-copyable types
