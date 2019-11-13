#include <memory>
#include <string>

#include <gtest/gtest.h>
#include <cpp_mock.h>

using cpp_mock::_;

class ExampleInterface
{
public:
    virtual ~ExampleInterface() = default;

    virtual int ExampleMethod(int value, const std::string& reference, std::unique_ptr<int>&& moved) = 0;
    virtual void VoidMethod(int value) = 0;

    virtual int GetInteger() const = 0;
    virtual bool TryGetInteger(int& value) const = 0;
};

class MockExample : public ExampleInterface
{
public:
    MockMethod(int, ExampleMethod, (int, const std::string&, std::unique_ptr<int>&&))
    MockMethod(void, VoidMethod, (int))
    MockConstMethod(int, GetInteger, ())
    MockConstMethod(bool, TryGetInteger, (int&))
};

TEST(MockingTest, TestArrangeDo)
{
    MockExample example;

    When(example.ExampleMethod)
        .Do([](int i, const std::string&, const std::unique_ptr<int>&)
        {
            return i;
        });

    int result = example.ExampleMethod(123, "string", nullptr);

    EXPECT_EQ(123, result);
}

TEST(MockingTest, TestArrangeReturn)
{
    MockExample example;

    When(example.GetInteger).Return({ 1, 2 });

    int result1 = example.GetInteger();
    int result2 = example.GetInteger();
    int result3 = example.GetInteger();

    EXPECT_EQ(1, result1);
    EXPECT_EQ(2, result2);
    EXPECT_EQ(2, result3);
}

TEST(MockingTest, TestArrangeSetReference)
{
    MockExample example;

    When(example.TryGetInteger)
        .Do([](int& value)
        {
            value = 123;
            return true;
        });

    int referenceParam = 0;
    bool result = example.TryGetInteger(referenceParam);

    EXPECT_TRUE(result);
    EXPECT_EQ(123, referenceParam);
}

TEST(MockingTest, TestArrangeThrow)
{
    MockExample example;

    When(example.GetInteger).Throw<std::invalid_argument>("args");

    EXPECT_THROW(example.GetInteger(), std::invalid_argument);
}

TEST(MockingTest, TestMultipleArrange)
{
    MockExample example;

    When(example.ExampleMethod)
        .Do([](int, const std::string&, const std::unique_ptr<int>&)
        {
            return 1;
        });

    When(example.ExampleMethod)
        .With(123, [](const std::string& s) { return s.size() > 0; }, _)
        .Do([](int, const std::string&, const std::unique_ptr<int>&)
        {
            return 2;
        });

    int result1 = example.ExampleMethod(123, "", nullptr);
    int result2 = example.ExampleMethod(123, "string", nullptr);

    EXPECT_EQ(1, result1);
    EXPECT_EQ(2, result2);
}

TEST(MockingTest, TestVerificationFailure)
{
    MockExample example;

    EXPECT_THROW(Verify(example.ExampleMethod), std::runtime_error);
}

TEST(MockingTest, TestVerificationArgMatching)
{
    MockExample example;

    example.ExampleMethod(123, "test", nullptr);
    example.ExampleMethod(1, "test", nullptr);

    Verify(example.ExampleMethod)
        .With(1, _, _)
        .Times(1);
}
