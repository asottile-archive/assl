#include<cassert>
#include "ScopedClosable.h"

using assl::ScopedClosable;

static bool calledClose = false;
static int value = -1;
static bool calledOpen = false;

static void open(int x) {
    value = x;
    calledOpen = true;
}

static void close(int x) {
    value = x;
    calledClose = true;
}

static void clear() {
    value = -1;
    calledOpen = false;
    calledClose = false;
}

static void assertState(int x, bool opened, bool closed) {
    assert(value == x);
    assert(calledOpen == opened);
    assert(calledClose == closed);
}

static void assertNoState() {
    assertState(-1, false, false);
}

int main() {

    // Test normal functionality with open and close
    {
        ScopedClosable<int> closable(1, &open, &close);
        assert(closable.get() == 1);
        assertState(1, true, false);
        clear();
    }
    assertState(1, false, true);
    clear();

    // Test dispose method
    {
        ScopedClosable<int> closable(2, &close);
        assertNoState();
        closable.dispose();
        assertState(2, false, true);
        clear();
    }
    // Already disposed, don't dispose twice
    assertNoState();

    return 0;
}
