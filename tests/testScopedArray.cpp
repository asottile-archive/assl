#include "ScopedArray.h"

using assl::ScopedArray;

int main() {

    // XXX: This is a shitty test without overriding delete[]

    {
        ScopedArray<char> arr(new char[5]);
        arr.get()[0] = 'A';
    }

    return 0;
}
