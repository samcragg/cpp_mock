# Setting Up Mocks

## Returning Values

The most common scenario is returning a value when a method is invoked on the
mock object. This can be done like so:

``` C++
MockClass mockClass;
When(mockClass.Add).Return(123);

assert(mockClass.Add(1, 2) == 123);
```

By default a zero initialized value will be returned from the method (i.e.
`return {}`) if nothing has been setup. Also, there is no error/warning if you
setup a method and it is not called. If you want to return a value for specific
arguments, then you can use argument matchers:

``` C++
When(mockClass.Add).With(1, 2).Return(3);

assert(mockClass.Add(1, 2) == 3);
```

The arrange methods setup is searched in reverse order, so the most recent call
to `When` will take priority. This enables you to setup a default value and then
to provide a more specific one:

``` C++
When(mockClass.Add).Return(5);
When(mockClass.Add).With(1, 2).Return(3);

assert(mockClass.Add(1, 2) == 3);
assert(mockClass.Add(2, 2) == 123);
```

It's also possible to setup return values over multiple calls (notice that the
last value in the list will be used for all subsequent calls):

``` C++
When(mockClass.Add).Return({1, 2});

assert(mockClass.Add(1, 2) == 1);
assert(mockClass.Add(1, 2) == 2);
assert(mockClass.Add(1, 2) == 2);
```

## Performing Actions

Instead of returning a value from a method, you can execute some arbitrary code
that calculates the value:

``` C++
When(mockClass.Add).Do([](int a, int b) { return a * b; });

assert(mockClass.Add(2, 3) == 6);
```

The same rules with regards to argument matching and setup order that apply to
`Return` also apply to `Do` (i.e. the most recent call to `Do` will be checked
if the arguments match first). Although it's possible to throw an exception with
the above, there's a simpler method available:

``` C++
When(mockClass.Add).Throws<std::out_of_range>("Expected");

try
{
    mockClass.Add(1, 2);
    assert(false)
}
catch (const std::out_of_range& ex)
{
    assert(std::strcmp(ex.what(), "Expected") == 0);
}
```

Using the `Do` method also allows you to set arguments that have been passed as
references (a.k.a output parameters), like the following:

``` C++
When(mockClass.TryGetValue).Do([](int& out) { out = 123; return true; });

int output = 0;
assert(mockClass.TryGetValue(output) == true);
assert(output == 123);
```
