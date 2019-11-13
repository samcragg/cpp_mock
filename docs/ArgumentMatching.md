# Argument Matching

Both for setting up and for verification, argument matchers are used to see if
the method call is applicable.

``` C++
MockClass mockClass;
When(mockClass.Add).With(_, 2).Return(123);

assert(mockClass.Add(1, 2) == 123);
```

Here, `_` will match any argument and the `2` uses `operator==` to check for
value equality. Alternatively, a predicate can be provided to check if the
argument matches a condition:

``` C++
When(mockClass.Add).With(_, [](int b) { return b > 2; }).Return(10);
When(mockClass.Add).With(_, std::bind(std::less<int>(), _1, 3)).Return(20);

assert(mockClass.Add(1, 2) == 20);
assert(mockClass.Add(1, 3) == 10);
```
