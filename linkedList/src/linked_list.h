#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>
// реализованы правило пяти
// реализованы итераторы
// реализованы операторы присваивания
// реализованы методы доступа к элементам
// реализованы методы добавления и удаления
// реалзиованы методы поиска

// изначально начал писать учитывая что head_ имеет тип unique_ptr
// однако позже узнал, что есть не очевидная проблема в использование unique_ptr, связанная с рекусривный удалением
// проблему решил написав деструктор
// в остальном функционал повторяет forward_list из стандрантной библиотеки, тесты тому подтверждение

template <class T>
class LinkedList {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;

    LinkedList();
    LinkedList(const T& data);
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    LinkedList(std::initializer_list<T> il);
    ~LinkedList();

    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList&& other) noexcept;

    reference front();
    const_reference front() const;

    class iterator;
    class const_iterator;
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    bool empty() const noexcept;

    void push_front(const T& value);
    void push_front(T&& value) noexcept;
    void pop_front();
    
    iterator find(const T& value);
    const_iterator find(const T& value) const;


private:
    struct Node {
        value_type data;
        std::unique_ptr<Node> next;

        Node(const value_type& data) : data(data), next(nullptr) {}
    };

    std::unique_ptr<Node> head_;

public:
    class iterator {
    public:
        iterator() = default;
        explicit iterator(Node* node);

        reference operator*() const;
        iterator& operator++();
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    private:
        Node* node_;
    };

    class const_iterator {
    public:
        const_iterator() = default;
        explicit const_iterator(const Node* node);
        
        const_iterator& operator=(const const_iterator&) = delete;
        const_reference operator*() const;
        const_iterator& operator++();
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
    private:
        const Node* node_;
    };

};

// =============================================================================

template <class T>
LinkedList<T>::LinkedList() : head_(nullptr) {} 

template <class T>
LinkedList<T>::LinkedList(const T& data) : head_(std::make_unique<Node>(data)) {}

template <class T>
LinkedList<T>::LinkedList(const LinkedList& other) : head_(nullptr) {
    if (!other.head_) return;
    head_ = std::make_unique<Node>(other.head_->data);
    Node* current = head_.get();
    Node* otherCurrent = other.head_->next.get();
    while (otherCurrent) {
        current->next = std::make_unique<Node>(otherCurrent->data);
        current = current->next.get();
        otherCurrent = otherCurrent->next.get();
    }
}


template <class T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept : head_(std::move(other.head_)) {}

template <class T>
LinkedList<T>::LinkedList(std::initializer_list<T> il) : head_(nullptr) {
    for (auto it = il.end(); it != il.begin();) {
        --it;
        push_front(*it);
    }
}

template <class T>
LinkedList<T>::~LinkedList() {
    while (head_) {
        head_ = std::move(head_->next);
    }
}

// =============================================================================

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        LinkedList temp(other);
        std::swap(head_, temp.head_);
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        head_ = std::move(other.head_);
        other.head_ = nullptr;
    }
    return *this;
}

// =============================================================================

template <class T>
typename LinkedList<T>::reference LinkedList<T>::front() {
    if (!head_) {
        throw std::runtime_error("LinkedList is empty");
    }
    return head_->data;
}

template <class T>
typename LinkedList<T>::const_reference LinkedList<T>::front() const {
    if (!head_) {
        throw std::runtime_error("LinkedList is empty");
    }
    return head_->data;
}

// =============================================================================

template <class T>
typename LinkedList<T>::iterator LinkedList<T>::begin() {
    if (!head_) {
        throw std::runtime_error("LinkedList is empty");
    }
    return iterator(head_.get());
}

template <class T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return iterator(nullptr);
}

template <class T>
typename LinkedList<T>::const_iterator LinkedList<T>::cbegin() const {
    if (!head_) {
        throw std::runtime_error("LinkedList is empty");
    }
    return const_iterator(head_.get());
}

template <class T>
typename LinkedList<T>::const_iterator LinkedList<T>::cend() const {
    return const_iterator(nullptr);
}

// =============================================================================

template <class T>
bool LinkedList<T>::empty() const noexcept {
    return head_ == nullptr;
}

// =============================================================================

template <class T>
void LinkedList<T>::push_front(const T& value) {
    auto temp = std::make_unique<Node>(value);
    temp->next = std::move(head_);
    head_ = std::move(temp);
}

template <class T>
void LinkedList<T>::push_front(T&& value) noexcept {
    auto temp = std::make_unique<Node>(std::move(value));
    temp->next = std::move(head_);
    head_ = std::move(temp);
}

template <class T>
void LinkedList<T>::pop_front() {
    if (head_) {
        head_ = std::move(head_->next);
    }
}

// =============================================================================

template <class T>
typename LinkedList<T>::iterator LinkedList<T>::find(const T& value) {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end();
}

template <class T>
typename LinkedList<T>::const_iterator LinkedList<T>::find(const T& value) const {
    for (auto it = cbegin(); it != cend(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return cend();
}

// =============================================================================

template <class T>
LinkedList<T>::iterator::iterator(Node* node) : node_(node) {}

template <class T>
typename LinkedList<T>::reference LinkedList<T>::iterator::operator*() const { 
    return node_->data;
}

template <class T>
typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator++() { 
    node_ = node_->next.get(); 
    return *this; 
}

template <class T>
bool LinkedList<T>::iterator::operator==(const iterator& other) const { 
    return node_ == other.node_;
}

template <class T>
bool LinkedList<T>::iterator::operator!=(const iterator& other) const {
    return !(*this == other); 
}

// =============================================================================

template <class T>
LinkedList<T>::const_iterator::const_iterator(const Node* node) : node_(node) {}

template <class T>
typename LinkedList<T>::const_reference LinkedList<T>::const_iterator::operator*() const { 
    return node_->data; 
}

template <class T>
typename LinkedList<T>::const_iterator& LinkedList<T>::const_iterator::operator++() { 
    node_ = node_->next.get(); 
    return *this;
}

template <class T>
bool LinkedList<T>::const_iterator::operator==(const const_iterator& other) const { 
    return node_ == other.node_;
}

template <class T>
bool LinkedList<T>::const_iterator::operator!=(const const_iterator& other) const { 
    return !(*this == other);
}

// =============================================================================


#endif  // LINKED_LIST_H
