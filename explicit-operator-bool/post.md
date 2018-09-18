The other day I was TDD-ing a resource handling class, and needed to add some operators to it.

For brevity, let's say the handle class can optionally hold any positive integer, using the sentinel value `0` to represent not currently holding a value. Sort of how a `unique_ptr` can hold any pointer, using `nullptr` to represent "no pointer".

Here's a minimal implementation:

```
class handle {
public:
    handle(int value) : value(value){}
    int value;
};
```

Also, to avoid complicating the issue of a unit testing framework, let's just use `assert` to test drive the implementation.

First, let's initialize a `handle` object:

```
    handle one(1);
    assert(one.value == 1);
```

Now we want to add an `operator bool()`, so we can do this:

```
    if (one) {do_something_with(one);}
```

First, let's add some tests:
```
    handle zero(0);
    handle one(1);
    assert((bool)zero == false);
    assert((bool)one == true);
```

The implementation is simple, just add `operator bool()` to the `handle` class:

```
class handle {
public:
    handle(int value) : value(value){}
    int value;

    operator bool() { return value != 0; } // <----
};
```

And our tests pass.

Next, I needed to compare handles, so I wanted to add `operator <`. Let's add the test first, to see that it fails to compile:

```
    handle one(1);
    handle two(2);
    assert(one < two); //Assertion failed: (one < two)
```

Wait, what? We didn't implement `operator <` yet? This shouldn't compile.
