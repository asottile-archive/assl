// FILE:    Property.h
// AUTHOR:  Anthony Sottile
// DATE:    2012-02-18
// PURPOSE: Property<TClass, TValue> is a class intended to be used in a class
//           as a readonly property.  This is effectively supposed to simulate
//           the property sugar of C#'s public T property { get; private set; }
//          This is the implementation of the class.  Since it is a template,
//           this file must be in the building directory, but it should not
//           be included in the built cpp files (it gets included through the
//           header file).

template<typename TClass, typename TValue>
Property<TClass, TValue>::Property()
    : data() { }

template<typename TClass, typename TValue>
Property<TClass, TValue>::Property(const TValue& t)
    : data(t) { }

template<typename TClass, typename TValue>
Property<TClass, TValue>::operator TValue() const {
    return this->data;
}

template<typename TClass, typename TValue>
const TValue* Property<TClass, TValue>::operator&() const {
    return &(this->data);
}

template<typename TClass, typename TValue>
TValue& Property<TClass, TValue>::operator=(const TValue& t) {
    return this->set(t);
}

template<typename TClass, typename TValue>
TValue& Property<TClass, TValue>::set(const TValue& t) {
    return this->data = t;
}

template<typename TClass, typename TValue>
TValue& Property<TClass, TValue>::get() {
    return this->data;
}

template<typename TClass, typename TValue>
const TValue& Property<TClass, TValue>::get() const {
    return this->data;
}
