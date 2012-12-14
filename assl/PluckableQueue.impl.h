// FILE:    PluckableQueue.impl.h
// AUTHOR:  Anthony Sottile
// DATE:    2012-12-14
// PURPOSE: Implementation of PluckableQueue

#include<cassert>

template<typename T>
PluckableQueue<T>::node::node(const T& t)
    : queue(nullptr), next(nullptr), prev(nullptr), t(t) { }

template<typename T>
T& PluckableQueue<T>::node::get() {
   return this->t;
}

template<typename T>
const T& PluckableQueue<T>::node::get() const {
   return this->t;
}

template<typename T>
PluckableQueue<T>::PluckableQueue() {
    this->top = nullptr;
    this->bottom = nullptr;
    this->count = 0;
}

template<typename T>
void PluckableQueue<T>::push(PluckableQueue<T>::node* node) {
    assert(node);
    assert(!node->queue);
    assert(!node->next);
    assert(!node->prev);

    this->count += 1;

    node->queue = this;
    node->next = nullptr;
    node->prev = this->bottom;

    // If it is empty, then this node becomes the first as well
    // Otherwise update the linkage on the existing last node
    if (this->top == nullptr) {
        this->top = node;
    } else {
        this->bottom->next = node;
    }
    this->bottom = node;
}

template<typename T>
typename PluckableQueue<T>::node* PluckableQueue<T>::pop() {
    assert(this->top);

    node* top = this->top;
    this->pluck(top);
    return top;
}

template<typename T>
void PluckableQueue<T>::pluck(PluckableQueue<T>::node* node) {
    assert(node->queue == this);

    PluckableQueue<T>::node* prev = node->prev;
    PluckableQueue<T>::node* next = node->next;

    // If prev is nullptr, we're removing the top
    // Otherwise the previous's next should point to this guy's next.
    if (prev == nullptr) {
        this->top = next;
    } else {
        prev->next = next;
    }

    // If next is null, we're removing the bottom
    // Otherwise the next's previous should point to this guy's previous.
    if (next == nullptr) {
        this->bottom = prev;
    } else {
        next->prev = prev;
    }

    node->queue = nullptr;
    node->prev = nullptr;
    node->next = nullptr;
    this->count -= 1;
}

template<typename T>
bool PluckableQueue<T>::contains(PluckableQueue<T>::node* node) const {
    return node->queue == this;
}

template<typename T>
unsigned int PluckableQueue<T>::size() const {
    return this->count;
}
