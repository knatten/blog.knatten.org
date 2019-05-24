Quick quiz! Given the following:
<!-- snippetysnip:ex1.cpp:overloads:(before='[sourcecode language="cpp"]', after='[/sourcecode]') -->

[sourcecode language="cpp"]
void f(unsigned int);
void f(int);
void f(char);
[/sourcecode]

<!-- snippetysnip_end:ex1.cpp:overloads -->

Which overload gets called by the following?

<!-- snippetysnip:ex1.cpp:call:(before='[sourcecode language="cpp"]', after='[/sourcecode]') -->

[sourcecode language="cpp"]
char x = 1;
char y = 2;
f(x + y);
[/sourcecode]

<!-- snippetysnip_end:ex1.cpp:call -->

Alternatives:

1. `f(unsigned int)`
2. `f(int)`
3. `f(char)`
4. No-one knows the type of `char + char`

If you answered 4), congratulations! And if you answered 2), maybe you tried the code on your own computer? Most people will get `f(int)` when they try this code, but this is actually not specified by the standard. The only thing we know for sure is that it's not 3), `f(char)`!

Let's have a look at what's going on:


Before being passed to operator `+`, the operands (`x` and `y`) go through a conversion. [expr.add]§8.7¶1:

> The usual arithmetic conversions are performed for operands of arithmetic or enumeration type.

What are "the usual arithmetic conversions"?

[expr]§8¶11:
> Many binary operators that expect operands of arithmetic or enumeration type cause conversions and yield result types in a similar way. The purpose is to yield a common type, which is also the type of the result. This pattern is called the usual arithmetic conversions, which are defined as follows:
> - [a bunch of rules for floats, enums etc]
> - Otherwise, the integral promotions (7.6) shall be performed on both operands

So both `char`s go through integral promotions. Those are defined in [conv.prom]§7.6¶1:

> A prvalue of an integer type other than `bool`, `char16_t`, `char32_t`, or `wchar_t` whose integer conversion rank (7.15) is less than the rank of `int` can be converted to a prvalue of type `int` if int can represent all the values of the source type; otherwise, the source prvalue can be converted to a prvalue of type `unsigned int`.

So a `char` gets converted to an `int` if `int` can fit all possible values of a `char`. If not, they get converted to `unsigned int`. But any `char` should fit in an `int`, right? As it turns out, that's not necessarily the case. 

First, `int` could actually be the same size as `char`. [basic.fundamental]§6.9.1¶2:

> There are five standard signed integer types : “signed char”, “short int”, “int”, “long int”, and “long long int”. In this list, each type provides at least as much storage as those preceding it in the list.

Note that it says "at least as much storage", it doesn't have to be more. So for instance you could have a sixteen bit system where both `char` and `int` are sixteen bits.

Second, `char` can be either signed or unsigned, it's up to the implementation: [basic.fundamental]§6.9.1¶1:

> It is implementation-defined whether a char object can hold negative values.

`int` is signed, so if `char` is also signed, all possible values of `char` will fit in an `int`. However, if `char` is unsigned, and `int` and `char` is the same size, `char` can actually hold larger values than `int`!

Let's see an example. If `char` and `int` are both sixteen bits, `int` (which is always signed) can hold `[-32768, 32767]`. If `char` is signed, it can also hold `[-32768, 32767]`, and any `char` fits in an `int`. However, if `char` is unsigned, it can hold `[0,65535]`, half of which fall outside the range of `int`!

In the former case, `char`s get promoted to `int`s, but in the latter case, `char`s get promoted to `unsigned int`s before being summed.

So in practice, most systems will call `f(int)` and print `i`, but some might call `f(unsigned int)` and print `u`, and they would both be confirming to the standard.


_If you enjoyed this post, you can [subscribe to my blog](http://blog.knatten.org/feed), or [follow me on Twitter](http://twitter.com/knatten)._
