// FILE:    ScopedClosable.impl.h
// AUTHOR:  Anthony Sottile
// DATE:    2012-12-14
// PURPOSE: Implementation of Scoped Closable

#include<cassert>

template<typename T>
ScopedClosable<T>::ScopedClosable(T t, func open, func close)
    : disposed(false), t(t), close(close) {
    open(t);
}

template<typename T>
ScopedClosable<T>::ScopedClosable(T t, func close)
    : disposed(false), t(t), close(close) { }

template<typename T>
ScopedClosable<T>::~ScopedClosable() {
    if (!this->disposed) {
        this->dispose();
    }
}

template<typename T>
void ScopedClosable<T>::dispose() {
    assert(!this->disposed);
    this->close(this->t);
    this->disposed = true;
}

template<typename T>
T& ScopedClosable<T>::get() {
    assert(!this->disposed);
    return this->t;
}
