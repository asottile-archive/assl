// FILE:    ScopedClosable.h
// AUTHOR:  Anthony Sottile
// DATE:    2012-12-14
// PURPOSE: ScopedClosable is a wrapper around some disposable type which
//           automatically calls some sort of close method when falling out
//           of scope.  This is useful for making things like locks, etc.

#ifndef SCOPEDCLOSABLE_H
#define SCOPEDCLOSABLE_H

namespace assl {

    template<typename T>
    class ScopedClosable {
        public:
            typedef void (*func)(T);
        private:
            bool disposed;
            T t;
            func close;

            ScopedClosable& operator=(ScopedClosable&);
            ScopedClosable(ScopedClosable&);

        public:
            ScopedClosable(T t, func open, func close);
            ScopedClosable(T t, func close);
            ~ScopedClosable();

            // REQUIRES: data is not disposed.
            // EFFECTS:  Dispose the object before going out of scope
            void dispose();

            // REQUIRES: data is not disposed.
            // EFFECTS:  returns the private object.
            T& get();
    };

    #include "ScopedClosable.impl.h"
};

#endif
