#include <algorithm>
#include <stdexcept>
#include <utility> // std::swap()
#include "vector.h"

Vector::Vector(int initial_capacity) : data_(new Fraction[initial_capacity]), size_(0), capacity_(initial_capacity) {}

Vector::Vector(const Vector &other) : data_(new Fraction[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

Vector::Vector(Vector &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Vector::~Vector() {
    delete[] data_;
}

Fraction* Vector::data() const {
    return data_;
}

size_t Vector::size() const {
    return size_;
}

size_t Vector::capacity() const {
    return capacity_;
}

Vector& Vector::operator=(const Vector &other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new Fraction[capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    return *this;
}

Vector& Vector::operator=(Vector &&other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

void Vector::push_back(const Fraction &fraction) {
    if (size_ == capacity_) {
        reallocate(capacity_ + 1);
    }
    data_[size_] = fraction;
    size_++;
}

Fraction& Vector::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range!");
    }
    return data_[index];
}

void Vector::reallocate(size_t new_capacity) {
    auto* new_data = new Fraction[new_capacity];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}
