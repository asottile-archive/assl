// FILE:    Property.h
// AUTHOR:  Anthony Sottile
// DATE:    2012-02-18
// PURPOSE: Property<TClass, TValue> is a class intended to be used in a class
//           as a readonly property.  This is effectively supposed to simulate
//           the property sugar of C#'s public T property { get; private set; }
//          This is the header file for the implementation.  Since it is
//           a template, the .cpp file must be in the building directory, but
//           it should not be included in the built cpp files (it gets
//           included through the header file).

#ifndef PROPERTY_H
#define PROPERTY_H

namespace assl {
    template<typename TClass, typename TValue>
    class Property {
        // OVERVIEW: Property is a public get, private set property.
        //           TClass is the class that will contain a property.
        //           TValue is the value type of the property.

        // Friend with containing class.
        // This allows the containing class access to the private constructors,
        //  assignment operators, etc.
        friend TClass;

        private:
            TValue data;

            // NOTE: Constructors, assignment, and acquiring a non-const
            //        reference are limited to private scope so only the
            //        containing class can access these.  The containing
            //        class gains access through friending.

            // EFFECTS: Constructs the property with the default constructor of
            //           the value type.
            Property();

            // EFFECTS: Constructs the property with the copy constructor of the
            //           value type.
            Property(const TValue& t);

            // EFFECTS: Returns a non-const reference to the private editable
            //           data.
            TValue& get();

            // MODIFIES: this
            // EFFECTS:  Assigns the private data to the value.
            TValue& operator=(const TValue& value);
            TValue& set(const TValue& value);
        public:
            // EFFECTS: Returns a const reference to the private readonly data.
            const TValue& get() const;

            // NOTE:    Implicit casting operator.
            // EFFECTS: Returns a copy of the private readonly data.  With bulky
            //           private data, use .get() instead.
            operator TValue() const;

            // NOTE:    This is added so &(c.property) doesn't return a pointer
            //           to the Property<TClass, TValue> itself.
            // EFFECTS: Returns a const pointer pointing at the private data.
            const TValue* operator&() const;
    };

    #include "Property.impl.h"
};

#endif
