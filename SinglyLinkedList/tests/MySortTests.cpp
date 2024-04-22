#include <array>
#include <vector>
#include <algorithm> // std::copy, std::sort
#include <gtest/gtest.h>

#if __has_include("../mySorting.h") && __has_include("../myList.h")
    #include "../mySorting.h"
    #include "../myList.h"
    #define MY_SORTING_INCLUDED 1
#elif __has_include("mySorting.h") && __has_include("myList.h")
    #include "mySorting.h"
    #include "myList.h"
    #define MY_SORTING_INCLUDED 1
#else
    #warning "Files 'mySorting.h' or 'myList.h' not found!"
    #define MY_SORTING_INCLUDED 0
#endif

namespace
{
using namespace std;
using namespace ::testing;
} // namespace

class MySortTester : public ::testing::Test
{
public:
    template<typename T, size_t N>
    auto returnSortedArray(T (&arr)[N])
    {
        std::array<T, N> arrCopy;
        std::copy(begin(arr), end(arr), begin(arrCopy));
        std::sort(begin(arrCopy), end(arrCopy));
        return arrCopy;
    }

    template<typename Container>
    auto returnSortedContainer(const Container& container)
    {
        Container containerCopy = container;
        std::sort(begin(containerCopy), end(containerCopy));
        return containerCopy;
    }
};

TEST_F(MySortTester, sortingStaticArray_expectedArraySorted)
{
#if MY_SORTING_INCLUDED == 1
    int values[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    const auto sortedValues = returnSortedArray(values);

    mySort(values);
    for (size_t i=0; i < std::size(values); ++i)
    {
        EXPECT_EQ(sortedValues[i], values[i]) << "i=" << i;
    }
#else
    ADD_FAILURE() << "File `mySorting.h` not added!";
#endif
}

TEST_F(MySortTester, sortingStdVector_expectedContainerSorted)
{
#if MY_SORTING_INCLUDED == 1
    vector<int> values = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    const auto sortedValues = returnSortedContainer(values);

    mySort(values);
    for (size_t i=0; i < std::size(values); ++i)
    {
        EXPECT_EQ(sortedValues[i], values[i]) << "i=" << i;
    }
#else
    ADD_FAILURE() << "File `mySorting.h` not added!";
#endif
}

TEST_F(MySortTester, sortingMyList_expectedElementsInTheListSorted)
{
#if MY_SORTING_INCLUDED == 1
    const vector<int> sortedValues = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    MyList<int> l;
    std::copy(begin(sortedValues), end(sortedValues), front_inserter(l));

    mySort(l);

    auto it = sortedValues.cbegin();
    for (auto v : l)
    {
        EXPECT_EQ(*it, v) << "index = " << distance(sortedValues.cbegin(), it);
        ++it;
    }
#else
    ADD_FAILURE() << "File `mySorting.h` not added!";
#endif
}

TEST_F(MySortTester, sortingConstCharPtrAllUpperCases_expectedAllWordsSorted)
{
#if MY_SORTING_INCLUDED == 1
    char randomGermanNames[][20] = { "MARLON", "OLAF", "MANFRED", "URS", "THEOPHILUS", "TORSTEN", "UDO", "MORITZ", "VIET", "RAINER", "OLIVER", "OSCAR", "WILBUR", "OLE", "YANNICK", "ZOLTHAR", "OSKAR", "UWE", "XAVER", "WIM", "MALTE", "RUDI", "OLLI", "WILMAR", "PASCAL", "OTTO", "MARTIN", "NOAH", "ULLI", "MIKA", "SVEN", "TORBEN", "WILFRIED", "MATHIS", "WILIBALD", "ROLF", "WILHELM", "MARVIN", "WALTER", "WOLF", "WILLY", "NIELS", "MADS", "MATTHIAS", "TEO", "VOLKER", "ROTGIER" };
    constexpr char sortedGermanNames[][20] = { "MADS", "MALTE", "MANFRED", "MARLON", "MARTIN", "MARVIN", "MATHIS", "MATTHIAS", "MIKA", "MORITZ", "NIELS", "NOAH", "OLAF", "OLE", "OLIVER", "OLLI", "OSCAR", "OSKAR", "OTTO", "PASCAL", "RAINER", "ROLF", "ROTGIER", "RUDI", "SVEN", "TEO", "THEOPHILUS", "TORBEN", "TORSTEN", "UDO", "ULLI", "URS", "UWE", "VIET", "VOLKER", "WALTER", "WILBUR", "WILFRIED", "WILHELM", "WILIBALD", "WILLY", "WILMAR", "WIM", "WOLF", "XAVER", "YANNICK", "ZOLTHAR" };

    mySort(randomGermanNames);

    for (size_t i=0; i < size(randomGermanNames); ++i)
    {
        EXPECT_STREQ(sortedGermanNames[i], randomGermanNames[i]) << "index = " << i;
    }
#else
    ADD_FAILURE() << "File `mySorting.h` not added!";
#endif
}

TEST_F(MySortTester, sortingConstCharPtrIgnoreCases_expectedAllWordsSortedDespiteDifferentCases)
{
#if MY_SORTING_INCLUDED == 1
    char words[][20] = { "Bazyli", "lubi", "Malfreda", "ktorego", "poznal", "u", "Stoigniewa", "stojacego", "przy", "barze", "mamy" };
    constexpr char sortedWords[][20] = { "barze", "Bazyli", "ktorego", "lubi", "Malfreda", "mamy", "poznal", "przy", "Stoigniewa", "stojacego", "u" };

    mySort(words);

    for (size_t i=0; i<size(words); ++i)
    {
        EXPECT_STREQ(sortedWords[i], words[i]) << "index = " << i;
    }
#else
    ADD_FAILURE() << "File `mySorting.h` not added!";
#endif
}
