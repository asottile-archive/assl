// FILE:    ScopedArray.h
// AUTHOR:  Anthony Sottile
// DATE:    2012-12-14
// PURPOSE: A ScopedArray is a heap array that deletes when it falls out of
//           scope.

#ifndef SCOPEDARRAY_H
#define SCOPEDARRAY_H

#include "ScopedClosable.h"

namespace assl {

    template<typename T>
    class ScopedArray : public ScopedClosable<T*> {
        public:
            ScopedArray(T* t);
    };

    #include "ScopedArray.impl.h"
};

#endif
