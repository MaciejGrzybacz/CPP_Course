#ifndef MYSTRING_H
#define MYSTRING_H

#include <vector>
#include <string>
#include <set>
#include <map>
#include <functional>
#include <iostream>
#include <algorithm>
#include <map>
#include <cctype>

// My implementation of the std::string class
// It uses a dynamic array of characters to store the string
// (I don't want to split data as I'm expected to do in the laboratory)

class MyString {
public:
    static const int initialBufferSize_ = 20;
    char* data_;
    size_t size_;
    size_t capacity_;

    struct iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;
        using reference = char&;

        char* val_;
        iterator() = default;
        explicit iterator(char* val);
        bool operator!=(iterator anotherIt);
        bool operator==(iterator anotherIt);
        iterator operator+(size_t pos);
        size_t operator-(iterator anotherIt);
        iterator& operator++();
        iterator& operator--();
        char& operator*();
        char operator*() const;
    };

    struct const_iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;
        using reference = char&;
        char* data_{};
        std::string s_data_;
        const_iterator() = default;
        explicit const_iterator(char* data);
        bool operator!=(const const_iterator& anotherIt) const;
        bool operator==(const const_iterator& anotherIt) const;
        const_iterator operator+(size_t pos) const;
        size_t operator-(const const_iterator& anotherIt) const;
        const_iterator& operator++();
        const_iterator& operator--();
        char& operator*();
        char operator*() const;
    };

    MyString();
    MyString(const char *text);
    MyString(const MyString &text);
    ~MyString();

    [[nodiscard]] iterator begin();
    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] iterator end();
    [[nodiscard]] const_iterator end() const;

    [[maybe_unused]] [[nodiscard]] const_iterator cbegin() const;

    [[maybe_unused]] [[nodiscard]] const_iterator cend() const;

    [[nodiscard]] size_t capacity() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool empty() const;
    void clear();
    void trim();
    MyString& toLower();
    static MyString generateRandomWord(size_t length);
    bool startsWith(const char *text) const;
    bool endsWith(const char *text) const;
    [[nodiscard]] MyString join(const std::vector<MyString>& texts) const;
    [[nodiscard]] std::vector<MyString> split(char delimiter) const;
    [[nodiscard]] std::vector<MyString> split(const char *delimiter) const;
    [[nodiscard]] std::vector<MyString> split(const MyString& delimiters) const; //splits by any of the characters in delimiters
    [[nodiscard]] bool contains(char c) const;


    bool operator!=(const MyString& rhs) const;
    bool operator==(const MyString& rhs) const;
    MyString& operator+=(char c);
    MyString& operator+=(const MyString& other);
    explicit operator std::string() const;
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend MyString operator>>(std::istream& is, MyString& str);
    char operator[](size_t index) const;
    bool operator<(const MyString& other) const;

    [[nodiscard]] std::map<MyString, size_t> countWordsUsageIgnoringCases() const;
    [[nodiscard]] std::set<MyString> getUniqueWords() const;
    [[nodiscard]] bool all_of(std::function<bool(char)> predicate) const;
};

#endif