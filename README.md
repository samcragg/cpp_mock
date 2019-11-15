# cpp_mock

`cpp_mock` is a simple to use and install C++ library to allow the mocking of
classes. It overrides virtual methods to allow them to be easily setup and,
optionally, verified in a unit test.

## Installation

The library is a small header only file - simple copy `include/cpp_mock.h` to
your include path and then you're ready to build!

It's designed to work with any C++ 11 compiler, regularly tested with G++
and VS C++. It should be warning free (with the exception of pedantic) - if you
spot anything then please raise an issue.

## Usage

Here's a basic example of how you can use the library:

```C++
#include <cpp_mock.h>

class MockCalculator : public Calculator
{
public:
    MockMethod(int, Add, (int, int))
};

void UnitTest()
{
    // Arrange our mock
    MockCalculator calculator;
    When(calculator.Add).Return(5);

    // Act on it
    int result = calculator.Add(1, 2);

    // Assert we got the expected result
    assert(result == 5);
}
```

You can also verify a method was called without having to set it up:

```C++
class MockService : public MyService
{
public:
    MockMethod(void, SaveCounter, (int))
};

void UnitTest()
{
    // Nothing to arrange this time
    MockService service;

    // Act on it
    objectThatUsesService.ExportCounter(service);

    // Assert it was actually used - this will throw an exception if the method
    // was not called
    Verify(service.SaveCounter);
}
```

Here is some more documentation on the basic constructs:

+ [Creating mocks](docs/CreatingMocks.md)
+ [Arranging mocks](docs/Arranging.md)
+ [Verifying mocks](docs/Asserting.md)
+ [Matching arguments](docs/ArgumentMatching.md)

## License

This project is licensed under the MIT license.
