#include<cassert>
#include "Property.h"

using assl::Property;

class TestClass {

    public:
        Property<TestClass, int> testProperty;

        void methodThatSetsPropertyWithAssignment(int newValue) {
            this->testProperty = newValue;
        }

        void methodThatSetsPropertyWithSet(int newValue) {
            this->testProperty.set(newValue);
        }

        void methodThatSetsPropertyWithGet(int newValue) {
            int& value = this->testProperty.get();
            value = newValue;
        }

        TestClass() { }

        TestClass(int n) : testProperty(n) { }
};

void testGet(const TestClass& c, int v) {
    assert(c.testProperty == v);
    assert(c.testProperty.get() == v);
    assert(*(&c.testProperty) == v);
}

int main() {

    TestClass a;
    testGet(a, 0);

    TestClass b(4);
    testGet(b, 4);

    a.methodThatSetsPropertyWithAssignment(4);
    testGet(a, 4);

    a.methodThatSetsPropertyWithGet(6);
    testGet(a, 6);

    a.methodThatSetsPropertyWithSet(7);
    testGet(a, 7);

    return 0;
}
