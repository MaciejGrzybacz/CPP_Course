#include <cstring> // strlen()

#include <iostream>
#include <sstream> // std::ostringstream
#include <gtest/gtest.h>

#if __has_include("../matrix.h")
    #include "../matrix.h"
#elif __has_include("matrix.h")
    #include "matrix.h"
#else
    #error "File 'matrix.h' not found!"
#endif

using namespace std;
using namespace ::testing;


namespace
{
constexpr size_t elementsInEachDimentions = 2;
} // namespace


struct MatrixTester : ::testing::Test
{
};

TEST_F(MatrixTester, constructionEmptyMatrix_expectedAllElementsAreZero)
{
#ifndef UNIMPLEMENTED_CONSTRUCTORS
    constexpr MatrixElement defaultValue = 0;

    const TwoDimensionMatrix m;
    static_assert (m.size() == elementsInEachDimentions, "Expected elements in each dimentions is 2!");

    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            ASSERT_EQ(defaultValue, m.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "Constructors not implemented";
#endif
}

TEST_F(MatrixTester, constructionMatrixFromTwoDimensionArray_expectedAllElementsCopied)
{
#ifndef UNIMPLEMENTED_CONSTRUCTORS
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    TwoDimensionMatrix m(sourceMatrix);
    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            ASSERT_EQ(sourceMatrix[row][column], m.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "Constructors not implemented";
#endif
}

TEST_F(MatrixTester, constructionMatrixFromAnotherMatrix_expectedAllElementsCopied)
{
#ifndef UNIMPLEMENTED_CONSTRUCTORS
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    const TwoDimensionMatrix m(sourceMatrix);
    TwoDimensionMatrix m2(m);
    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            ASSERT_EQ(sourceMatrix[row][column], m2.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "Constructors not implemented";
#endif
}

TEST_F(MatrixTester, assignmentOperatorCopyingDeeply_expectedAllElementsCopied)
{
#ifndef UNIMPLEMENTED_ASIGNMENT_OPERATOR
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    const TwoDimensionMatrix matrix(sourceMatrix);

    TwoDimensionMatrix matrixCopy;
    matrixCopy = matrix;
    for (size_t row=0; row < matrix.size(); ++row)
        for (size_t column=0; column < matrix.size(); ++column)
        {
            ASSERT_EQ(matrix[row][column], matrixCopy.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "operator= not implemented";
#endif
}

TEST_F(MatrixTester, assignmentOperatorCopyingFromItselve_expectedNotCrash)
{
#ifndef UNIMPLEMENTED_ASIGNMENT_OPERATOR
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    TwoDimensionMatrix matrix(sourceMatrix);

    TwoDimensionMatrix& matrixRef = matrix;
    matrix = matrixRef;
    for (size_t row=0; row < matrix.size(); ++row)
        for (size_t column=0; column < matrix.size(); ++column)
        {
            ASSERT_EQ(sourceMatrix[row][column], matrix.get(row, column)) << "row:" << row << " column:" << column;
            ASSERT_EQ(matrix.get(row, column), matrixRef.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "operator= not implemented";
#endif
}

TEST_F(MatrixTester, checkingOstreamOperator_expectedAllElementsInStream)
{
#ifndef UNIMPLEMENTED_OSTREAM_OPERATOR
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    const TwoDimensionMatrix m(sourceMatrix);

    ostringstream stream;
    stream << m << endl;

    const string textFromStream = stream.str();

    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            const string expectedElementInText = to_string(sourceMatrix[row][column]);
            const bool textFoundInStream = textFromStream.find(expectedElementInText) != string::npos;
            ASSERT_TRUE(textFoundInStream) << "Element " << expectedElementInText << " not found in stream!";
        }
#else
    ADD_FAILURE() << "operator<< not implemented";
#endif
}

TEST_F(MatrixTester, checkingIstreamOperator_expectedAllElementsReadFromStream)
{
#ifndef UNIMPLEMENTED_ISTREAM_OPERATOR
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    const string text = to_string(sourceMatrix[0][0]) + ' ' + to_string(sourceMatrix[0][1]) + '\n' +
            to_string(sourceMatrix[1][0]) + ' ' + to_string(sourceMatrix[1][1]) + '\n';

    TwoDimensionMatrix m;

    istringstream stream(text);
    stream >> m;

    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            ASSERT_EQ(sourceMatrix[row][column], m.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "operator>> not implemented";
#endif
}

TEST_F(MatrixTester, multiplicationMatrixMultipliedWithNumber_expectedAllElementsOfMatrixMultiplied)
{
#ifndef UNIMPLEMENTED_ARITHMETIC_OPERATORS
    constexpr MatrixElement number2Multiply = 3;

    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    TwoDimensionMatrix m(sourceMatrix);

    m *= number2Multiply;

    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            const auto expectedNumber = sourceMatrix[row][column] * number2Multiply;
            ASSERT_EQ(expectedNumber, m.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "arithmetic operators not implemented";
#endif
}

TEST_F(MatrixTester, additionOfTwoMatrixes_expectedMatrixWithSumOfElementsReturned)
{
#ifndef UNIMPLEMENTED_ARITHMETIC_OPERATORS
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };
    const MatrixElement sourceMatrix2[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 5, 6 },
        { 7, 8 }
    };

    const TwoDimensionMatrix m(sourceMatrix);
    const TwoDimensionMatrix m2(sourceMatrix2);
    const TwoDimensionMatrix mResult = m + m2;

    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            const auto expectedNumber = sourceMatrix[row][column] + sourceMatrix2[row][column];
            EXPECT_EQ(expectedNumber, mResult.get(row, column)) << "row:" << row << " column:" << column;
            EXPECT_EQ(sourceMatrix[row][column], m.get(row, column)) << "row:" << row << " column:" << column;
            EXPECT_EQ(sourceMatrix2[row][column], m2.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "arithmetic operators not implemented";
#endif
}

TEST_F(MatrixTester, andOfTwoMatrixes_expectedMatrixWithAllElementsAsResultOfLogicalAndReturned)
{
#ifndef UNIMPLEMENTED_ARITHMETIC_OPERATORS
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 0,  0 },
        { -3, 9 }
    };
    const MatrixElement sourceMatrix2[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 0, 6 },
        { 0, -9 }
    };

    const TwoDimensionMatrix m(sourceMatrix);
    const TwoDimensionMatrix m2(sourceMatrix2);
    const TwoDimensionMatrix mResult = m && m2;

    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            const auto expectedNumber = sourceMatrix[row][column] && sourceMatrix2[row][column];
            EXPECT_EQ(expectedNumber, mResult.get(row, column)) << "row:" << row << " column:" << column;
            EXPECT_EQ(sourceMatrix[row][column], m.get(row, column)) << "row:" << row << " column:" << column;
            EXPECT_EQ(sourceMatrix2[row][column], m2.get(row, column)) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "arithmetic operators not implemented";
#endif
}

TEST_F(MatrixTester, accessingMatrixByRowAndColumnWithIndexOperator_expectedSuccesfullAccess)
{
#ifndef UNIMPLEMENTED_SUBSCRIPT_OPERATOR
    const MatrixElement sourceMatrix[elementsInEachDimentions][elementsInEachDimentions] =
    {
        { 1, 2 },
        { 3, 4 }
    };

    constexpr MatrixElement defaultValue = 0;

    TwoDimensionMatrix m;

    for (size_t row=0; row < m.size(); ++row)
        for (size_t column=0; column < m.size(); ++column)
        {
            ASSERT_EQ(defaultValue, m[row][column]) << "row:" << row << " column:" << column;

            m[row][column] = sourceMatrix[row][column];
            ASSERT_EQ(sourceMatrix[row][column], m[row][column]) << "row:" << row << " column:" << column;
        }
#else
    ADD_FAILURE() << "subscript operators not implemented";
#endif
}

TEST_F(MatrixTester, matrixConverseOperatorIntoSizeType_expected2ReturnElementsInEachDimentions)
{
#ifndef UNIMPLEMENTED_CONVERSION_OPERATOR
    const TwoDimensionMatrix m;

    const size_t valueFromConversion = static_cast<size_t>(m);

    ASSERT_EQ(elementsInEachDimentions, valueFromConversion);
#else
    ADD_FAILURE() << "conversion operator not implemented";
#endif
}
