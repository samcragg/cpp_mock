# Verifying Calls

To verify that a method was called on a mock, the `Verify` method can be used;
should the check fail then an exception will be raised.

``` C++
MockClass mockClass;

mockClass.Add(1, 2);

Verify(mockClass.Add);
```

You can also use argument matchers to ensure that it was invoked with specific
values:

``` C++
mockClass.Add(1, 2);

Verify(mockClass.Add).With(1, 2);
```

By default, the verify method will allow multiple calls, however, you can
specify that a method was only called a specific number of times too. This can
also be used to verify the method was never called.

``` C++
mockClass.Add(1, 2);
mockClass.Add(2, 3);

Verify(mockClass.Add).With(1, 2).Times(1);
Verify(mockClass.Add).With(2, 2).Times(0);
```
