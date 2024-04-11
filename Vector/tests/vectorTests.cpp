#include <string>
#include <gtest/gtest.h>

#if __has_include("../vector.h")
    #include "../vector.h"
#elif __has_include("vector.h")
    #include "vector.h"
#else
    #error "File 'vector.h' not found!"
#endif

namespace
{
using namespace std;
using namespace ::testing;


[[maybe_unused]] string toString(const Fraction& fraction [[maybe_unused]])
{
#ifndef PRINTING_FROM_TESTS_DISABLED
    return std::to_string(fraction.numerator()) + "/" + std::to_string(fraction.denominator());
#else
    return {};
#endif
}

template<size_t N>
string fractionArray2String(const Fraction (&fractions[[maybe_unused]])[N])
{
    string s = "array(" + to_string(N) + ") = {";
#ifndef PRINTING_FROM_TESTS_DISABLED
    s += toString(fractions[0]);
    for (size_t i=1; i < N; ++i)
    {
        s += ", " + toString(fractions[i]);
    }
    s += "}";
#endif

    return s;
}

string vector2String(const Vector& v[[maybe_unused]])
{
#ifndef PRINTING_FROM_TESTS_DISABLED
    string s = "Vector(" + to_string(v.size()) + ") = {";
    if (v.size())
    {
        s += toString(v[0]);
    }
    for (size_t i=1; i < v.size(); ++i)
    {
        s += ", " + toString(v[i]);
    }
    s += "}";

    return s;
#else
    return {};
#endif
}
} // namespace


namespace MyOwnMemoryManagement
{
unsigned deletions = 0;
}

void *operator new[](size_t size)
{
    void* newMemory = malloc(size);
    return newMemory;
}

void operator delete[](void *memory2remove) noexcept
{
    ++MyOwnMemoryManagement::deletions;
    free(memory2remove);
}

void operator delete[](void* memory2remove, size_t) noexcept
{
    ++MyOwnMemoryManagement::deletions;
    free(memory2remove);
}


class VectorTest : public ::testing::Test
{
};

TEST_F(VectorTest, constructionAndGetters_expectedValuesFromConstructorReadableByGetters)
{
    { /// default constructor
        Vector v;
        constexpr size_t expectedCapacity = 0;

        ASSERT_EQ(expectedCapacity, v.size());
        ASSERT_EQ(expectedCapacity, v.capacity());
    }

    {  /// constructor with single argument
        constexpr size_t expectedSize = 0;
        constexpr size_t expectedCapacity = 10;

        Vector v(expectedCapacity);

        ASSERT_EQ(expectedSize, v.size());
        ASSERT_EQ(expectedCapacity, v.capacity());
    }
}

TEST_F(VectorTest, destructOfNotEmptyVector_expectedMemoryFreedOnce)
{
    constexpr decltype(MyOwnMemoryManagement::deletions) expectedReallocations = 1;
    MyOwnMemoryManagement::deletions = 0;
    {
        constexpr size_t expectedCapacity = 10;

        Vector v(expectedCapacity);
        ASSERT_EQ(expectedCapacity, v.capacity());
    }
    ASSERT_EQ(expectedReallocations, MyOwnMemoryManagement::deletions);
}

TEST_F(VectorTest, addingMultipleElementsWithoutReallocation_expectedSizeIncreasesButCapacityDoesNot)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v(fractionCount);
    for (size_t i=0; i < fractionCount; ++i)
    {
        v.push_back(fractions[i]);
        EXPECT_EQ(i+1, v.size()) << "i = " << i << ", " << vector2String(v);
        EXPECT_EQ(fractionCount, v.capacity()) << "i = " << i << ", " << vector2String(v);
    }
}

TEST_F(VectorTest, accessingWithIndexOperator_expectedProperElementsInProperPlaces)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v(fractionCount);
    for (size_t i=0; i < fractionCount; ++i)
    {
        v.push_back(fractions[i]);

        EXPECT_EQ(fractions[i].numerator(),   v[i].numerator()) << "i = " << i << ", " << vector2String(v) << ", " << fractionArray2String(fractions);
        EXPECT_EQ(fractions[i].denominator(), v[i].denominator()) << "i = " << i << ", " << vector2String(v) << ", " << fractionArray2String(fractions);
    }
}

TEST_F(VectorTest, copyAndMoveConstructor_expectedSuccessfulCopyAndMove)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v(fractionCount);
    for (size_t i=0; i < fractionCount; ++i)
    {
        v.push_back(fractions[i]);
    }

    {  /// copying:
        const Vector vCopied = v;
        ASSERT_EQ(fractionCount, vCopied.size());
        ASSERT_EQ(fractionCount, vCopied.capacity());
        for (size_t i=0; i < fractionCount; ++i)
        {
            EXPECT_EQ(fractions[i].numerator(),   vCopied[i].numerator())
                << "i = " << i << ", Current: " << vector2String(vCopied) << ", Expected: " << fractionArray2String(fractions);
            EXPECT_EQ(fractions[i].denominator(), vCopied[i].denominator())
                << "i = " << i << ", Current: " << vector2String(vCopied) << ", Expected: " << fractionArray2String(fractions);

            EXPECT_EQ(fractions[i].numerator(),   v[i].numerator())
                << "i = " << i << ", Current: " << vector2String(v) << ", Expected: " << fractionArray2String(fractions);
            EXPECT_EQ(fractions[i].denominator(), v[i].denominator())
                << "i = " << i << ", Current: " << vector2String(v) << ", Expected: " << fractionArray2String(fractions);
        }
    }


    {  /// moving:
        const Vector vMoved = std::move(v);
        constexpr size_t expectedCapacityAfterMoving = 0;
        EXPECT_EQ(expectedCapacityAfterMoving, v.size());
        EXPECT_EQ(expectedCapacityAfterMoving, v.capacity());
        ASSERT_EQ(fractionCount, vMoved.size());
        ASSERT_EQ(fractionCount, vMoved.capacity());

        for (size_t i=0; i < fractionCount; ++i)
        {
            EXPECT_EQ(fractions[i].numerator(),   vMoved[i].numerator())
                << "i = " << i << ", Current: " << vector2String(vMoved) << ", Expected: " << fractionArray2String(fractions);
            EXPECT_EQ(fractions[i].denominator(), vMoved[i].denominator())
                << "i = " << i << ", Current: " << vector2String(vMoved) << ", Expected: " << fractionArray2String(fractions);
        }
    }
}
TEST_F(VectorTest, assignmentOperatorCopyingAndMoving_expectedSuccessfulCopyAndMove)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v(fractionCount), v2, v3;
    for (size_t i=0; i < fractionCount; ++i)
    {
        v.push_back(fractions[i]);
    }

    {  /// copying:
        v2 = v;
        ASSERT_EQ(fractionCount, v2.size());
        ASSERT_EQ(fractionCount, v2.capacity());
        for (size_t i=0; i < fractionCount; ++i)
        {
            EXPECT_EQ(fractions[i].numerator(),   v2[i].numerator())
                << "i = " << i << ", Current: " << vector2String(v) << ", Expected: " << fractionArray2String(fractions);
            EXPECT_EQ(fractions[i].denominator(), v2[i].denominator())
                << "i = " << i << ", Current: " << vector2String(v) << ", Expected: " << fractionArray2String(fractions);

            EXPECT_EQ(fractions[i].numerator(),   v[i].numerator())
                << "i = " << i << ", Current: " << vector2String(v) << ", Expected: " << fractionArray2String(fractions);
            EXPECT_EQ(fractions[i].denominator(), v[i].denominator())
                << "i = " << i << ", Current: " << vector2String(v) << ", Expected: " << fractionArray2String(fractions);
        }
    }

    {  /// moving:
        v3 = std::move(v);
        constexpr size_t expectedCapacityAfterMoving = 0;
        EXPECT_EQ(expectedCapacityAfterMoving, v.size());
        EXPECT_EQ(expectedCapacityAfterMoving, v.capacity());
        ASSERT_EQ(fractionCount, v3.size());
        ASSERT_EQ(fractionCount, v3.capacity());

        for (size_t i=0; i < fractionCount; ++i)
        {
            EXPECT_EQ(fractions[i].numerator(),   v3[i].numerator())
                << "i = " << i << ", Current: " << vector2String(v3) << ", Expected: " << fractionArray2String(fractions);
            EXPECT_EQ(fractions[i].denominator(), v3[i].denominator())
                << "i = " << i << ", Current: " << vector2String(v3) << ", Expected: " << fractionArray2String(fractions);
        }
    }
}

TEST_F(VectorTest, accessingWithIndexOperatorOutOfRange_expectedExceptionWhenOutOfRange)
{
    Vector v;
    ASSERT_THROW(v[v.size()], std::out_of_range);

    constexpr size_t expectedCapacity = 10;
    const Fraction fraction{1, 2};

    Vector v2(expectedCapacity);
    for (size_t i=0; i < expectedCapacity; ++i)
    {
        v2.push_back(fraction);

        ASSERT_NO_THROW(v2[i]) << "i = " << i << ", Current: " << vector2String(v2);
    }
    ASSERT_THROW(v2[expectedCapacity+1], std::out_of_range);
}

TEST_F(VectorTest, addingElementsWithReallocationNecessairy)
{
    const Fraction fractions[] = { Fraction{1, 2}, Fraction{3, 4}, Fraction{5, 6} };
    constexpr size_t fractionCount = sizeof(fractions) / sizeof(fractions[0]);

    Vector v;
    for (size_t i=0; i < fractionCount; ++i)
    {
        v.push_back(fractions[i]);
        ASSERT_EQ(i+1, v.size()) << "i = " << i << ", Current: " << vector2String(v) << ", Expected: " << fractionArray2String(fractions);
        ASSERT_EQ(v.size(), v.capacity()) << "i = " << i << ", Current: " << vector2String(v) << ", Expected: " << fractionArray2String(fractions);
    }
}
