// These test ensure different method signatures compile

#include <memory>
#include <string>

#include <gtest/gtest.h>
#include <cpp_mock.h>

using cpp_mock::_;

struct VoidTypes
{
    virtual ~VoidTypes() = default;

    virtual void Empty() = 0;
    virtual void VoidPointerArg(void* ptr) = 0;
    virtual void* VoidPointerReturn() = 0;
};

struct MockVoidTypes : public VoidTypes
{
    MockMethod(void, Empty, ())
    MockMethod(void, VoidPointerArg, (void*))
    MockMethod(void*, VoidPointerReturn, ())
};

TEST(CompileTest, TestVoidTypes)
{
    MockVoidTypes mock;
    When(mock.Empty).Do([]() {});
    When(mock.VoidPointerArg).With(_).Do([](void*) {});
    When(mock.VoidPointerReturn).Do([]() { return nullptr; });

    mock.Empty();
    mock.VoidPointerArg(nullptr);
    mock.VoidPointerReturn();

    Verify(mock.Empty);
    Verify(mock.VoidPointerArg).With((void*)nullptr);
    Verify(mock.VoidPointerReturn);
}
