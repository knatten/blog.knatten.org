Quiz time! Which of the following programs can you expect to not compile? For bonus points, which are required by the C++ standard to not compile?
#### Program 1
<!-- snippetysnip:main1.cpp:all:(before='```', after='```') -->

```
struct B{};

template <typename T>
struct A {
    //Assume sizeof(B) != 4
    static_assert(sizeof(T) == 4);
};

A<B> a; 
```

<!-- snippetysnip_end:main1.cpp:all -->
#### Program 2
<!-- snippetysnip:main2.cpp:all:(before='```', after='```') -->

```
struct B{};

template <typename T>
struct A {
    //Assume sizeof(B) != 4
    static_assert(sizeof(T) == 4);
};

A<B>* a; 
```

<!-- snippetysnip_end:main2.cpp:all -->
#### Program 3
<!-- snippetysnip:main3.cpp:all:(before='```', after='```') -->

```
struct B{};

template <typename T>
struct A {
    //Assume sizeof(int) != 4
    static_assert(sizeof(int) == 4);
};
```

<!-- snippetysnip_end:main3.cpp:all -->

In case you're not familiar with `static_assert`, it takes a constant boolean expression, and if it evaluates to false, you get a compilation error. The most basic example is just doing `static_assert(false)`, like in Program 3. If you have that anywhere in your program, compilation fails. But let's start at the beginning:

#### Program 1
<!-- snippetysnip:main1.cpp:all:(before='```', after='```') -->

```
struct B{};

template <typename T>
struct A {
    //Assume sizeof(B) != 4
    static_assert(sizeof(T) == 4);
};

A<B> a; 
```

<!-- snippetysnip_end:main1.cpp:all -->

Here we have a class template `struct A`, which takes a type `T` as its single template parameter. We then assert that the size of the provided template argument is `4`.

We then define a variable `a` of type `A<B>`. In order to do that, we need the complete definition of `A<B>`, so that specialization of `A` gets implicitly instantiated. In that specialization, `sizeof(T)` becomes `sizeof(B)`, which is not equal to `4`, and **compliation fails**.

#### Program 2
<!-- snippetysnip:main2.cpp:all:(before='```', after='```') -->

```
struct B{};

template <typename T>
struct A {
    //Assume sizeof(B) != 4
    static_assert(sizeof(T) == 4);
};

A<B>* a; 
```

<!-- snippetysnip_end:main2.cpp:all -->

This is the exact same problem as in Program 1, except we only define a pointer to `A<B>`. Does this result in a implicit instantiation? Let's have a look at [temp.inst] (§17.7.1) ¶1 in the C++17 standard:
> Unless a class template specialization has been explicitly instantiated (17.7.2) or explicitly specialized (17.7.3), the class template specialization is implicitly instantiated when the specialization is referenced in a context that requires a completely-defined object type or when the completeness of the class type affects the semantics of the program.

The class template specialization `A<B>` has not been explicitly instantiated nor explicitly specialized, so the question is then whether it's implicitly instantiated. We're only declaring a pointer to it, which doesn't require a completely-defined object type, so it's not instantiated. The program **compiles just fine**.

#### Program 3
<!-- snippetysnip:main3.cpp:all:(before='```', after='```') -->

```
struct B{};

template <typename T>
struct A {
    //Assume sizeof(int) != 4
    static_assert(sizeof(int) == 4);
};
```

<!-- snippetysnip_end:main3.cpp:all -->

In this variation, we're asserting on the size of `int`, rather than the size of the template argument. And given the assumption that `sizeof(int) != 4`, that assertion will always fail. However, we're never actually instantiating any specialization of `A` whatsoever. In Program 2, not instatiating the template allowed us to ignore the `static_assert`. Does the same apply here? In fact, it doesn't. Let's have a look at [temp.inst] (§17.6) ¶8 in the C++17 standard:

> The program is ill-formed, no diagnostic required, if:
> [...]
> a hypothetical instantiation of a template immediately following its definition would be ill-formed due to a construct that does not depend on a template parameter

The `static_assert(sizeof(int) == 4)` does _not_ depend on a template parameter, so if we were to instantiate `A` immediately following its definition, `A` would always be ill-formed.

So our program is **ill-formed, no diagnostic required**.

Now what does that mean? *ill-formed* is the terminology used by the standard for a program that's not valid C++, where compilation is required to fail with an error message. *Ill-formed, no diagnostic required* however means our program is not valid C++, but that the compiler *isn't required to let us know*. The standard makes no guarantees on the behaviour of the program, i.e. we have undefined behaviour.

So Program 3 **has undefined behaviour**. In practice however, both [Clang](https://godbolt.org/z/oi7uvX), [gcc](https://godbolt.org/z/YDTjzq) and [msvc](https://godbolt.org/z/UwSBiN) gives a **compilation error** in this case.

#### Summary

|Program | Because ... | ... the standard says | In practice |
|---|---|---|---|
| 1 | We need the class definition | Compilation error | Compilation error |
| 2 | We don't need the class definition | No error | No error |
| 3 | The assertion doesn't depend on `T` | Undefined behaviour | Compilation error |

_If you enjoyed this post, you can [subscribe to my blog](http://blog.knatten.org/feed), or [follow me on Twitter](http://twitter.com/knatten)._
