#ifndef MYLIST_H
#define MYLIST_H
#define IMPLEMENTED_constructorOfEmptyList
#define IMPLEMENTED_pushingAndPopingElementsFront
#define IMPLEMENTED_nodesStoredAsUniquePtrs
#define IMPLEMENTED_popFromWhenEmptyList
#define IMPLEMENTED_copyingDisabled
#define IMPLEMENTED_removingElements
#define IMPLEMENTED_iteratorOperations
#define IMPLEMENTED_iteratorWithRangedForLoop
#define IMPLEMENTED_iteratorWithStlAlgorithm
#define IMPLEMENTED_ostreamOperator
#include <memory>
#include <ostream>
#include <cctype>

template<typename T>
class MyList {
public:
    struct Node {
        T data;
        std::unique_ptr<Node> next_;
    };

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        explicit Iterator(Node *node) : node_(node) {}

        Iterator& operator++() {
            if (node_ != nullptr) {
                node_ = node_->next_.get();
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        T& operator*() const {
            return node_->data;
        }

        friend bool operator==(Iterator iter1, Iterator iter2) {
            return iter1.node_ == iter2.node_;
        }

        friend bool operator!=(Iterator iter1, Iterator iter2) {
            return iter1.node_ != iter2.node_;
        }

    //private:
        Node *node_;
    };

    using value_type = T;

    Iterator begin() const {
        return Iterator(head_.get());
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    MyList() : head_{nullptr} {}

    [[nodiscard]] int size() const;

    void push_front(T val);

    T pop_front();

    T front();

    void remove(const T& val);

    MyList(const MyList<T>&) = delete;

    MyList<T>& operator=(const MyList<T>&) = delete;

//private: the same case as before
    std::unique_ptr<Node> head_;
};

template<typename T>
int MyList<T>::size() const {
    if (head_ == nullptr)
        return 0;
    int size_=1;
    std::unique_ptr<Node>* node1 = &(head_->next_);
    while (*node1 != nullptr) {
        node1 = &((*node1)->next_);
        size_++;
    }
    return size_;
}

template<typename T>
void MyList<T>::push_front(T val) {
    std::unique_ptr<Node> new_head = std::make_unique<Node>();
    new_head->data = val;
    new_head->next_ = std::move(head_);
    head_ = std::move(new_head);
}

template<typename T>
T MyList<T>::pop_front() {
    if (!head_) {
        throw std::out_of_range("List is empty");
    }
    T val = std::move(head_->data);
    head_ = std::move(head_->next_);
    return val;
}

template<typename T>
T MyList<T>::front() {
    if (!head_) {
        throw std::out_of_range("List is empty");
    }
    return head_->data;
}

template<typename T>
void MyList<T>::remove(const T& val) {
    if (head_ == nullptr)
        return;
    std::unique_ptr<Node>* node1 = &(head_->next_);
    std::unique_ptr<Node>* node2 = &head_;
    while (*node1 != nullptr) {
        if ((*node1)->data == val) {
            (*node2)->next_ = std::move((*node1)->next_);
            node1 = node2;
        }
        node2 = node1;
        node1 = &((*node1)->next_);
    }
    if (head_->data == val) {
        std::unique_ptr<Node> new_head = std::move(head_->next_);
        head_ = std::move(new_head);
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyList<T>& list) {
    for (const auto& val : list) {
        os << val << " ";
    }
    return os;
}

#endif //MYLIST_H
