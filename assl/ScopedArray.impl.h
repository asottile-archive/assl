// FILE:    ScopedArray.impl.h
// AUTHOR:  Anthony Sottile
// DATE:    2012-12-14
// PURPOSE: Implementation of ScopedArray

template<typename T>
static void deleteArray(T* t) {
    if (t != nullptr) {
        delete[] t;
    }
}

template<typename T>
ScopedArray<T>::ScopedArray(T* t) : ScopedClosable<T*>(t, &deleteArray<T>) { }
