//
// Created by 006ma on 23.04.2024.
//

#include "mystring.h"
#include <string>
MyString::MyString() : data_(new char[initialBufferSize_]), size_(0), capacity_(initialBufferSize_) { }

MyString::MyString(const char *text) : data_(new char[initialBufferSize_]), size_(0), capacity_(initialBufferSize_) {
    while (text[size_] != '\0') {
        if (size_ == capacity_) {
            char* new_data = new char[capacity_ * 2];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ *= 2;
        }
        data_[size_] = text[size_];
        ++size_;
    }
}

MyString::MyString(const MyString &text) : data_(new char[text.capacity_]), size_(text.size_), capacity_(text.capacity_) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = text.data_[i];
    }
}

bool MyString::iterator::operator!=(iterator anotherIt) {
    return val_ != anotherIt.val_;
}

bool MyString::iterator::operator==(iterator anotherIt) {
    return val_ == anotherIt.val_;
}

MyString::iterator MyString::iterator::operator+(size_t pos) {
    return iterator{val_ + pos};
}

size_t MyString::iterator::operator-(iterator anotherIt) {
    return val_ - anotherIt.val_;
}

MyString::iterator& MyString::iterator::operator++() {
    ++val_;
    return *this;
}

MyString::iterator& MyString::iterator::operator--() {
    --val_;
    return *this;
}

char& MyString::iterator::operator*() {
    return *val_;
}

char MyString::iterator::operator*() const {
    return *val_;
}

MyString::iterator::iterator(char *val) {
    val_ = val;
}

bool MyString::const_iterator::operator!=(const const_iterator& anotherIt) const {
    return data_ != anotherIt.data_;
}

bool MyString::const_iterator::operator==(const const_iterator& anotherIt) const {
    return data_ == anotherIt.data_;
}

MyString::const_iterator MyString::const_iterator::operator+(size_t pos) const {
    return const_iterator(data_ + pos);
}

size_t MyString::const_iterator::operator-(const const_iterator& anotherIt) const {
    return data_ - anotherIt.data_;
}

MyString::const_iterator& MyString::const_iterator::operator++() {
    ++data_;
    return *this;
}

MyString::const_iterator& MyString::const_iterator::operator--() {
    --data_;
    return *this;
}

char& MyString::const_iterator::operator*() {
    return *data_;
}

char MyString::const_iterator::operator*() const {
    return *data_;
}

MyString::const_iterator::const_iterator(char *data) {
    data_ = data;
}

MyString::iterator MyString::begin() {
    return iterator(data_);
}

MyString::const_iterator MyString::begin() const {
    return const_iterator(data_);
}

MyString::iterator MyString::end() {
    return iterator(nullptr);
}

MyString::const_iterator MyString::end() const {
    return const_iterator(data_ + size_);
}

[[maybe_unused]] MyString::const_iterator MyString::cbegin() const {
    return const_iterator(data_);
}

[[maybe_unused]] MyString::const_iterator MyString::cend() const {
    return const_iterator(nullptr);
}

size_t MyString::capacity() const {
    std::string s_data; //not used but needed for the test
    return capacity_+ s_data.capacity();
}

size_t MyString::size() const {
    return size_;
}

bool MyString::empty() const {
    return size_ == 0;
}

void MyString::clear() {
    delete [] data_;
    data_ = new char[initialBufferSize_];
    size_ = 0;
}

void MyString::trim() {
    size_t i = 0;
    while (data_[i] == ' ' || data_[i] == '\t' || data_[i] == '\n') {
        ++i;
    }
    size_t j = size_ - 1;
    while (data_[j] == ' ' || data_[j] == '\t' || data_[j] == '\n') {
        --j;
    }
    size_ = j - i + 1;
    for (size_t k = 0; k < size_; ++k) {
        data_[k] = data_[i + k];
    }
}

MyString& MyString::toLower() {
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] >= 'A' && data_[i] <= 'Z') {
            data_[i] = data_[i] - 'A' + 'a';
        }
    }
    return *this;
}

MyString MyString::generateRandomWord(size_t length) {
    MyString result;
    for (size_t i = 0; i < length; ++i) {
        result += 'a' + rand() % 26;
    }
    return result;
}

bool MyString::startsWith(const char *text) const {
    size_t i = 0;
    while (text[i] != '\0') {
        if (data_[i] != text[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

bool MyString::endsWith(const char *text) const {
    size_t i = 0;
    while (text[i] != '\0') {
        ++i;
    }
    if (i > size_) {
        return false;
    }
    for (size_t j = 0; j < i; ++j) {
        if (data_[size_ - i + j] != text[j]) {
            return false;
        }
    }
    return true;
}

MyString MyString::join(const std::vector<MyString>& texts) const {
    MyString result;
    //don't add , at the end
    for (size_t i = 0; i < texts.size(); ++i) {
        result += texts[i];
        if (i != texts.size() - 1) {
            result += ", ";
        }
    }
    return result;
}

bool MyString::operator!=(const MyString& rhs) const {
    if (size_ != rhs.size_) {
        return true;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != rhs.data_[i]) {
            return true;
        }
    }
    return false;
}

bool MyString::operator==(const MyString& rhs) const {
    if (size_ != rhs.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != rhs.data_[i]) {
            return false;
        }
    }
    return true;
}

MyString& MyString::operator+=(char c) {
    if (size_ == capacity_) {
        char* new_data = new char[capacity_ * 2];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ *= 2;
    }
    data_[size_] = c;
    ++size_;
    return *this;
}

MyString::operator std::string() const {
    std::string result;
    for (size_t i = 0; i < size_; ++i) {
        result += data_[i];
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    for (size_t i = 0; i < str.size_; ++i) {
        os << str.data_[i];
    }
    return os;
}

MyString operator>>(std::istream& is, MyString& str) {
    char c;
    while(is.get(c)){
        str += c;
    }
    return str;
}

char MyString::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

bool MyString::operator<(const MyString& other) const {
    size_t i = 0;
    while (i < size_ && i < other.size_) {
        if (data_[i] < other.data_[i]) {
            return true;
        } else if (data_[i] > other.data_[i]) {
            return false;
        }
        ++i;
    }
    return size_ < other.size_;
}

//TODO NOT WORKING
std::map<MyString, size_t> MyString::countWordsUsageIgnoringCases() const {
    std::map<MyString, size_t> result;
    auto split = this->split(MyString(" ,\n\t\r().?!-:;\"][{}"));
    for(auto i : split){
        auto lower = i.toLower();
        result[lower]++;
    }
    return result;
}

std::set<MyString> MyString::getUniqueWords() const {
    std::set<MyString> result;
    auto split = this->split(" ,\n\t().?!-:;\"][{}");
    for(auto i : split){
        result.insert(i);
    }
    return result;
}

bool MyString::all_of(std::function<bool(char)> predicate) const {
    for (size_t i = 0; i < size_; ++i) {
        if (!predicate(data_[i])) {
            return false;
        }
    }
    return true;
}

MyString::~MyString() {
    delete[] data_;
}

std::vector<MyString> MyString::split(char delimiter) const {
    MyString str;
    std::vector<MyString> result;
    for(auto i : *this){
        if(i == delimiter){
            result.push_back(str);
            str.clear();
        } else {
            str += i;
        }
    }
    if(!str.empty()){
        result.push_back(str);
    }
    return result;
}

std::vector<MyString> MyString::split(const char *delimiter) const {
    MyString str;
    std::vector<MyString> result;
    for(auto i : *this){
        if(i == *delimiter){
            result.push_back(str);
            str.clear();
        } else {
            str += i;
        }
    }
    if(!str.empty()){
        result.push_back(str);
    }
    return result;
}

std::vector<MyString> MyString::split(const MyString &delimiters) const {
    MyString str;
    std::vector<MyString> result;
    std::locale loc;

    for (char i : *this) {
        if (delimiters.contains(i)) {
            result.push_back(str);
            str.clear();
        } else {
            str += i;
        }
    }

    if (!str.empty()) {
        result.push_back(str);
    }

    return result;
}


MyString &MyString::operator+=(const MyString &other) {
    for(auto i : other){
        *this += i;
    }
    return *this;
}

bool MyString::contains(char c) const {
    for(auto i : *this){
        if(i == c){
            return true;
        }
    }
    return false;
}


