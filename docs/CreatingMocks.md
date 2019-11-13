# Creating Mocks

To create a mock you'll need to create a derived class and define the methods
to be mocked:

``` C++
#include <cpp_mock.h>

class RealClass
{
public:
    virtual int GetInteger() const;
    virtual void VoidMethod(int value);
};

class MockClass : public RealClass
{
public:
    MockConstMethod(int, GetInteger, ())
    MockMethod(void, VoidMethod, (int))
};
```

As can be seen, the basic syntax for mocking a method is
`Mock[Const]Method` passing in the return type, the method name and then the
argument types (which are surrounded by parentheses, e.g. `(int, int)`). This
will by default add the `override` specifier to the generated method, as this
helps keeping the mock class synchronised with the real class. Alternatively,
if you want to provide your own method specifiers, they can be passed in after
the arguments:

``` C++
    // The following line is the same as using MockConstMethod
    MockMethod(int, GetInteger, (), const override);
```

This can be used to allow methods to be declared on the class that don't
override methods in the base class or for `volatile` methods etc.
