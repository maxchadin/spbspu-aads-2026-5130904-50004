#ifndef CHADIN_BILIST_HPP
#define CHADIN_BILIST_HPP

#include <stdexcept>
#include <utility>
#include <iterator>

namespace chadin {
    template<typename T>
    struct Node {
        T val;
        Node *prev, *next;
        Node(const T& v) : val(v), prev(nullptr), next(nullptr) {}
    };

    template<typename T> class BiList;

    template<typename T>
    class LIter : public std::iterator<std::bidirectional_iterator_tag, T> {
        Node<T>* node_;
        Node<T>* head_;
        friend class BiList<T>;
        LIter(Node<T>* n, Node<T>* h) : node_(n), head_(h) {}
    public:
        LIter() : node_(nullptr), head_(nullptr) {}
        T& operator*() const { return node_->val; }
        LIter& operator++() {
            node_ = node_->next;
            if (node_ == head_) node_ = nullptr;
            return *this;
        }
        LIter& operator--() {
            if (node_ == nullptr) node_ = head_->prev;
            else node_ = node_->prev;
            return *this;
        }
        bool operator==(const LIter& o) const { return node_ == o.node_; }
        bool operator!=(const LIter& o) const { return node_ != o.node_; }
    };

    template<typename T>
    class LCIter : public std::iterator<std::bidirectional_iterator_tag, const T> {
        const Node<T>* node_;
        const Node<T>* head_;
        friend class BiList<T>;
        LCIter(const Node<T>* n, const Node<T>* h) : node_(n), head_(h) {}
    public:
        LCIter() : node_(nullptr), head_(nullptr) {}
        const T& operator*() const { return node_->val; }
        LCIter& operator++() {
            node_ = node_->next;
            if (node_ == head_) node_ = nullptr;
            return *this;
        }
        LCIter& operator--() {
            if (node_ == nullptr) node_ = head_->prev;
            else node_ = node_->prev;
            return *this;
        }
        bool operator==(const LCIter& o) const { return node_ == o.node_; }
        bool operator!=(const LCIter& o) const { return node_ != o.node_; }
    };

    template<typename T>
    class BiList {
        Node<T>* head_ = nullptr;
        size_t size_ = 0;
    public:
        BiList() = default;
        ~BiList() { clear(); }

        void pushBack(const T& val) {
            Node<T>* newNode = new Node<T>(val);
            if (!head_) {
                newNode->next = newNode->prev = newNode;
                head_ = newNode;
            } else {
                Node<T>* tail = head_->prev;
                newNode->next = head_;
                newNode->prev = tail;
                tail->next = head_->prev = newNode;
            }
            size_++;
        }

        void clear() { while(size_) popFront(); }
        void popFront() {
            if (!head_) return;
            Node<T>* old = head_;
            if (size_ == 1) head_ = nullptr;
            else {
                head_->prev->next = head_->next;
                head_->next->prev = head_->prev;
                head_ = head_->next;
            }
            delete old;
            size_--;
        }

        LIter<T> begin() { return LIter<T>(head_, head_); }
        LIter<T> end() { return LIter<T>(nullptr, head_); }
        LCIter<T> cbegin() const { return LCIter<T>(head_, head_); }
        LCIter<T> cend() const { return LCIter<T>(nullptr, head_); }
        bool isEmpty() const { return size_ == 0; }
        size_t getSize() const { return size_; }
    };
}
#endif
