#include <iostream>
#include <sstream> // std::ostringstream
#include <gtest/gtest.h>

#if __has_include("../fraction.h")
    #include "../fraction.h"
#elif __has_include("fraction.h")
    #include "fraction.h"
#else
    #error "File 'fraction.h' not found!"
#endif

using namespace std;
using namespace ::testing;


struct FractionTester : ::testing::Test
{
};

TEST_F(FractionTester, constructionAndGetters_expectedValuesFromConstructorReadableByGetters)
{
    { /// 1/2
        constexpr int numerator   = 1;
        constexpr int denominator = 2;

        const Fraction fraction(numerator, denominator);
        ASSERT_EQ(numerator, fraction.numerator());
        ASSERT_EQ(denominator, fraction.denominator());
    }

    { /// 4/1
        constexpr int numerator   = 4;
        constexpr int defaultDenominator = 1;

        const Fraction fraction(numerator);
        ASSERT_EQ(numerator, fraction.numerator());
        ASSERT_EQ(defaultDenominator, fraction.denominator());
    }
}

TEST_F(FractionTester, settersForMembers_expectedValuesChangesWithoutReduction)
{
    constexpr int numerator1   = 3, numerator2   = 2;
    constexpr int denominator1 = 4, denominator2 = 5;

    Fraction fraction(numerator1, denominator1);
    ASSERT_EQ(numerator1, fraction.numerator());
    ASSERT_EQ(denominator1, fraction.denominator());

    fraction.setNumerator(numerator2);
    fraction.setDenominator(denominator2);
    ASSERT_EQ(numerator2, fraction.numerator());
    ASSERT_EQ(denominator2, fraction.denominator());
}

TEST_F(FractionTester, fractionMultiplyResultFractionImpossibleForReduction_expectedSimpleMultiplyingWorking)
{
    constexpr int numerator1 = 1, denominator1 = 2;
    constexpr int numerator2 = 1, denominator2 = 3;
    constexpr int numeratorResult = 1, denominatorResult = 6;

    const Fraction fraction = Fraction(numerator1, denominator1) * Fraction(numerator2, denominator2);
    ASSERT_EQ(numeratorResult, fraction.numerator());
    ASSERT_EQ(denominatorResult, fraction.denominator());
}

TEST_F(FractionTester, fractionAdditionResultFractionImpossibleForReduction_expectedSimpleAdditionWorking)
{
    constexpr int numerator1 = 1, denominator1 = 2;
    constexpr int numerator2 = 1, denominator2 = 3;
    constexpr int numeratorResult = 5, denominatorResult = 6;

    const Fraction fraction = Fraction(numerator1, denominator1) + Fraction(numerator2, denominator2);
    ASSERT_EQ(numeratorResult, fraction.numerator());
    ASSERT_EQ(denominatorResult, fraction.denominator());
}

TEST_F(FractionTester, settingInvalidDenominarrInConstructor_expectedThrow)
{
    constexpr int numerator = 1;
    constexpr int invalidDenominator = 0;

    ASSERT_THROW(Fraction(numerator, invalidDenominator), std::invalid_argument);

    Fraction fraction = Fraction(numerator);
    ASSERT_THROW(fraction.setDenominator(invalidDenominator), std::invalid_argument);
}

TEST_F(FractionTester, fractionAdditionWithCommonDenominator_expectedReduction)
{
    constexpr int denominator = 3;
    constexpr int numerator1 = 1, numerator2 = 2;
    constexpr int numeratorResult = 1, denominatorResult = 1;

    const Fraction fraction = Fraction(numerator1, denominator)
            + Fraction(numerator2, denominator);
    ASSERT_EQ(numeratorResult, fraction.numerator());
    ASSERT_EQ(denominatorResult, fraction.denominator());
}
