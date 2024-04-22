#include <vector>
#include <algorithm>   // std::count_if
#include <type_traits> // std::is_same<>
#include <functional>  // std::bind, std::not_equal_to
#include <cctype>      // isspace
#include <gtest/gtest.h>

#if __has_include("../myList.h")
    #include "../myList.h"
#elif __has_include("myList.h")
    #include "myList.h"
#else
    #warning "File 'myList.h' not found!"
    #define MY_LIST_FILE_DOES_NOT_EXIST
#endif

namespace
{
using namespace std;
using namespace ::testing;
} // namespace


class MyListTester : public ::testing::Test
{
public:
    void setUp()
    {
#ifdef MY_LIST_FILE_DOES_NOT_EXIST
        ADD_FAILURE() << "File 'myList.h' not found";
#endif
    }
};

#ifdef IMPLEMENTED_nodesStoredAsUniquePtrs
/** The wrapper is to make some protected members public for tests: **/
template<typename T>
struct MyListTestWrapper : public MyList<T>
{
    using typename MyList<T>::Node;
    using MyList<T>::head_;
};
#endif

TEST_F(MyListTester, constructorOfEmptyList_expectedSizeIs0)
{
#ifdef IMPLEMENTED_constructorOfEmptyList
    const MyList<int> l;

    constexpr size_t expectedSize = 0;
    ASSERT_EQ(expectedSize, l.size());
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, pushingAndPopingElementsFront_expectedSizeIncreasingAndDecreasing)
{
#ifdef IMPLEMENTED_pushingAndPopingElementsFront
    using Container = vector<double>;
    const Container sourceElements = {3.14, 2.72, 5-3.14, 3.14/2};

    MyList<Container::value_type> l;
    size_t elements_counter = 0;
    for(const auto element : sourceElements)
    {
        l.push_front(element);
        ++elements_counter;
        ASSERT_EQ(elements_counter, l.size()) << "element = " << element;
    }
    for (size_t i=0; i < elements_counter; ++i)
    {
        ASSERT_NO_THROW(l.pop_front()) << "i = " << i;
        ASSERT_EQ(elements_counter - i - 1, l.size()) << "i = " << i;
    }
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, pushingAndPopingElementsFront_elementsAreBeingThenAddedRemoved)
{
#ifdef IMPLEMENTED_pushingAndPopingElementsFront
    using Container = vector<double>;
    const Container sourceElements = {3.14, 2.72, 5-3.14, 3.14/2};

    MyList<Container::value_type> l;
    size_t elements_counter = 0;
    for(const auto element : sourceElements)
    {
        l.push_front(element);
        ++elements_counter;
        EXPECT_EQ(element, l.front());
    }
    for (size_t i=0; i < elements_counter; ++i)
    {
        const auto poped_element = l.pop_front();
        EXPECT_EQ(sourceElements[elements_counter - i - 1], poped_element) << "i = " << i;
    }
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, nodesStoredAsUniquePtrs)
{
#ifdef IMPLEMENTED_nodesStoredAsUniquePtrs
    MyListTestWrapper<int> l;
    typedef MyListTestWrapper<int>::Node NodeType;
    l.push_front(44);

    constexpr bool headIsUniquePtr = std::is_same<decltype(l.head_), unique_ptr<NodeType>>::value;
    ASSERT_TRUE(headIsUniquePtr);
    constexpr bool nextNodeIsUniquePtr = std::is_same<decltype(l.head_->next_), unique_ptr<NodeType>>::value;
    ASSERT_TRUE(nextNodeIsUniquePtr);
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, popFromWhenEmptyList_expectedExceptionThrown)
{
#ifdef IMPLEMENTED_popFromWhenEmptyList
    MyList<int> l;
    ASSERT_THROW(l.pop_front(), out_of_range);

    constexpr int elements2Insert = 10;
    for (int i=0; i < elements2Insert; ++i)
    {
        l.push_front(i);
    }

    for (int i=0; i<elements2Insert; ++i)
    {
        l.pop_front();
    }
    ASSERT_THROW(l.pop_front(), out_of_range);
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, expectedCopyingDisabled)
{
#ifdef IMPLEMENTED_copyingDisabled
    ASSERT_FALSE(std::is_copy_constructible_v<MyList<int>>);
    ASSERT_FALSE(std::is_copy_assignable_v<MyList<int>>);
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, removingElements)
{
#ifdef IMPLEMENTED_removingElements
    constexpr int element2Remove = 1;
    const std::vector<int> elements =
    {
                      1,
                   1,   1,
                 1,   2,   1,
               1,  3,   3,   1,
             1,  4,   6,   4,   1,
           1,  5, 10,  10,   5,   1,
         1,  6,  15, 20,  15,   6,   1
    };
    remove_cv_t<decltype(elements)> elementsWithout1;
    copy_if(begin(elements), end(elements), std::back_inserter(elementsWithout1),
            std::bind(std::not_equal_to<int>(), element2Remove, placeholders::_1));

    MyList<int> l;
    for (auto element : elements)
    {
        l.push_front(element);
    }
    ASSERT_EQ(elements.size(), l.size());

    l.remove(element2Remove);

    ASSERT_EQ(elementsWithout1.size(), l.size());

    for (auto element : l)
    {
        ASSERT_NE(element2Remove, element);
    }
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, iteratorOperationsWorks)
{
#ifdef IMPLEMENTED_iteratorOperations
    MyList<int> l;
    ASSERT_FALSE(l.begin() != l.end());

    l.push_front(4);
    ASSERT_TRUE(l.begin() != l.end());

    constexpr bool iteratorReturnsInt = std::is_same_v<decltype(*l.begin()), int&>;
    ASSERT_TRUE(iteratorReturnsInt);

    constexpr bool iteratorHasPreIncrementation = std::is_same_v<decltype(l.begin()),
            remove_reference_t<decltype(++l.begin())>>;
    ASSERT_TRUE(iteratorHasPreIncrementation);
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, iterationWorksWithRangedForLoop)
{
#ifdef IMPLEMENTED_iteratorWithRangedForLoop
    using Container = vector<string>;
    const Container sourceElements =
    {
        "wlazl", "kotek", "na", "plotek",
        "i", "mruga", "ladna", "to"
        "piosenka", "nie", "dluga"
    };

    MyList<Container::value_type> l;
    for (const auto& text : sourceElements)
    {
        l.push_front(text);
    }

    auto sourceBackwardIterator = sourceElements.crbegin();
    for (auto it=l.begin(); it != l.end(); ++it)
    {
        EXPECT_EQ(*sourceBackwardIterator, *it);
        ++sourceBackwardIterator;
    }

    sourceBackwardIterator = sourceElements.crbegin();
    for (const auto& text : l)
    {
        EXPECT_EQ(*sourceBackwardIterator, text);
        ++sourceBackwardIterator;
    }
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, iteratorWorksWithStlAlgorithms)
{
#ifdef IMPLEMENTED_iteratorWithStlAlgorithm
    // source of quote: Sw. Jan Pawel II
    constexpr char text[] = "Najbardziej tworcza ze wszystkich prac jest praca nad soba, "
            "ktora pozwala odnajdywac urok mlodosci. "
            "Nie ma wiekszego bogactwa w narodzie nad swiatlych obywateli.";
    MyList<char> l;
    for (char c : text)
    {
        l.push_front(c);
    }
    const auto counterWords = count_if(l.begin(), l.end(), ::isspace) + 1;
    constexpr decltype(counterWords) expectedNumberOfWords = 23;
    ASSERT_EQ(expectedNumberOfWords, counterWords);
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}

TEST_F(MyListTester, ostreamOperator_expectedAllValuesInStream)
{
#ifdef IMPLEMENTED_ostreamOperator
    const string sourceContainer[] = {"Musicie", "od", "siebie", "wymagac",
                                      "nawet", "gdyby", "inni",
                                      "od", "was", "nie", "wymagali"};

    MyList<decay_t<decltype(sourceContainer[0])>> l;
    for (const auto& word : sourceContainer)
    {
        l.push_front(word);
    }
    ostringstream stream;
    stream << l;
    const auto textFromStream = stream.str();

    for (const auto& word : sourceContainer)
    {
        const auto wordFoundInStream = textFromStream.find(word) != string::npos;
        ASSERT_TRUE(wordFoundInStream) << "not found word: " << word;
    }
#else
    ADD_FAILURE() << "Not implemented!";
#endif
}
