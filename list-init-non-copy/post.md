You're probably used to intitalizing vectors like this:

    vector<int> vi1{1,2,3};
    vector<int> vi2 = {1,2,3};
    //TODO SNIP THIS

This of course also works with user defined classes. Let's say you have a class `Copyable`, then you can for instance do:

    Copyable c1(1);
    Copyable c2(2);
    vector<Copyable> vc1{c1, c2};
    vector<Copyable> vc2 = {c1, c2};
    //TODO SNIP THIS

The `Copyable` class is reproduced at the end of the post, but in short it has a constructor taking an `int`, and a `default`ed copy constructor, move constructor, copy assignment operator and move assignment operator.

Now what happens if we have a non-copyable class `NonCopyable`? It can also be seen at the end of the post, but is identical to `Copyable` except that the move constructor and move assignment operators have been `delete`ed.

<hr>

{} is braced initialization. in this case it means list-initialization.

Copying an initializer-list does not copy the underlying elements, and the only way to iterate over it is by const pointers:
[support.initlist] only has
constexpr const E* begin() const noexcept; // first element
constexpr const E* end() const noexcept; // one past the last element

So there's no way to copy out of it.

Say something about this not being related to whether we direct initialize or copy initialize, the latter actually supports moving non-copyable types
