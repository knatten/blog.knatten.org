Have you ever wondered why you can't list-initialize containers of non-copyable types? This is for instance not possible:

<!-- snippetysnip:main.cpp:vector_unique:(before='```', after='```') -->

```
    vector<unique_ptr<int>> vu{
        make_unique<int>(1), make_unique<int>(2)};
    //error: call to implicitly-deleted copy constructor of unique_ptr
```

<!-- snippetysnip_end:main.cpp:vector_unique -->

If you ever wondered, or if you now are, read on!

### List-initialization
Since C++11, you're probably used to intitalizing containers like this:

<!-- snippetysnip:main.cpp:vector_int:(before='```', after='```') -->

```
    vector<int> vi1{1,2,3};
    vector<int> vi2 = {1,2,3};
```

<!-- snippetysnip_end:main.cpp:vector_int -->

This of course also works with user defined types. Let's say you have a class `Copyable`, then you can for instance do:

<!-- snippetysnip:main.cpp:vector_copyable:(before='```', after='```') -->

```
    Copyable c1(1);
    Copyable c2(2);
    vector<Copyable> vc1{c1, c2};
    vector<Copyable> vc2 = {c1, c2};
```

<!-- snippetysnip_end:main.cpp:vector_copyable -->

(`Copyable` is just an arbitrary class which can be copied. It's reproduced at the end of the post.)

Now what happens if we have a non-copyable class `NonCopyable`? (`NonCopyable` is just an arbitrary class which can be moved but not copied, it too is reproduced at the end of the post.)

<!-- snippetysnip:main.cpp:vector_noncopyable:(before='```', after='```') -->

```
    NonCopyable n1(1);
    NonCopyable n2(2);
    vector<NonCopyable> vn1{n1, n2}; //error: call to deleted constructor of 'const NonCopyable'
    vector<NonCopyable> vn2 = {n1, n2}; //error: call to deleted constructor of 'const NonCopyable'
```

<!-- snippetysnip_end:main.cpp:vector_noncopyable -->

Well, `n1` and `n2` are lvalues, so no wonder it tries to copy them. What if we turn them into `rvalues`, either with `std::move` or by creating temporaries?
<!-- snippetysnip:main.cpp:vector_noncopyable_move:(before='```', after='```') -->

```
    vector<NonCopyable> vn3{std::move(n1), std::move(n2)}; //error: call to deleted constructor of 'const NonCopyable'
    vector<NonCopyable> vn3{NonCopyable(4), NonCopyable(5)}; //error: call to deleted constructor of 'const NonCopyable'
```

<!-- snippetysnip_end:main.cpp:vector_noncopyable_move -->

So what's going on here, why is it trying to copy our rvalues? Let's see what the standard has to say in [dcl.init.list]¶1:
> _List-initialization_ is initialization of an object or reference from a _braced-init-list_.

A _braced-init-list_ is the `{element1, element2, ...}` syntax we saw above. The standard continues:

> Such an initializer is called an initializer list. (...) List-initialization can occur in direct-initialization or copy-initialization contexts.

So _list-initialization_ applies both to the forms `vector<Copyable> vc1{c1, c2}` and `vector<Copyable> vc2 = {c1, c2}`, which we saw above. The former is an example of _direct-initialization_, the latter of _copy-initialization_. In both cases, `{c1, c2}` is the _braced-init-list_. 

(Note that the word _copy-initialization_ here is not what causes a copy. _Copy-initialization_ simply refers to the form `T t = expression`, which doesn't necessarily invoke the copy constructor.)

### Creating the `initializer_list`

Now what exactly happens with the _braced_init_list_, and how do its elements end up inside the container we're initializing?

[dcl.init.list]¶5
> An object of type `std::initializer_list<E>` is constructed from an initializer list as if the implementation generated and materialized (7.4) a prvalue of type "array of` N const E`", where `N` is the number of elements in the initializer list. Each element of that array is copy-initialized with the corresponding element of the initializer list, and the` std::initializer_list<E>` object is constructed to refer to that array.

So the initializer_list can be thought of as just a wrapper for a temporary array we initialize with the elements in the braced-init-list. Sort of like if we'd been doing this:

<!-- snippetysnip:main.cpp:temp_array:(before='```', after='```') -->

```
    const Copyable arr[2] = {c1, c2};    
    vector<Copyable> vc3(initializer_list<Copyable>(arr, arr+2));
```

<!-- snippetysnip_end:main.cpp:temp_array -->

### Consuming the `initializer_list`
Now that our `initializer_list` has been created and passed to the `vector` constructor, what can that constructor do with it? How does it get the elements out of the `initializer_list` and into the `vector`?

[initializer_list.syn] lists the very sparse interface of `std::initializer_list`:
```
constexpr const E* begin() const noexcept; // first element
constexpr const E* end() const noexcept; // one past the last element
```

There's no access to the elements as rvalue references, only `const` iterators of pointers to `const`, so we only get lvalues, and we need to copy. Why is there no access as rvalue references?

As we saw in the quote above, "the `std::initializer_list<E>` object is constructed to refer to that array." So it only refers to it, and does not own the elements. In particular, this means that if we copy the `initializer_list`, we do _not_ copy the elements, we only copy a reference to them. In fact, this is spelled out in a note [initializer_list.syn]¶1:

> Copying an initializer list does not copy the underlying elements.

So even if we get passed the `initializer_list` by value, we do _not_ get a copy of the elements, and it would _not_ be safe to move them out, as another copy of the `initializer_list` could be used again somewhere else. This is why `initializer_list` offers no rvalue reference access.

### Summary
In summary: When you do `T t{elm1, elm2}`, an `initializer_list` is created, referring to those elements. Copying that `initializer_list` does not copy the elements. When a constructor takes an `initializer_list`, it does not know whether it's the only consumer of those elements, so it's not safe to move them out of the `initializer_list`. The only safe way to get the elements out is by copy, so a copy constructor needs to be available.

_As usual, the code for this blog post is available [on GitHub](https://github.com/knatten/blog.knatten.org/blob/master/list-init-non-copy/main.cpp)._

_If you enjoyed this post, you can <a href="http://blog.knatten.org/feed/">subscribe to my blog</a>, or <a href="http://twitter.com/#!/knatten">follow me on Twitter</a>._

### Appendix: The `Copyable` and `Uncopyable` classes:

<!-- snippetysnip:main.cpp:classes:(before='```', after='```') -->

```
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
```

<!-- snippetysnip_end:main.cpp:classes -->
