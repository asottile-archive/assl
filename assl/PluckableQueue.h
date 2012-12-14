// FILE:    PluckableQueue.h
// AUTHOR:  Anthony Sottile
// DATE:    2012-12-14
// PURPOSE: PluckableQueue provides a generic queue which allows plucking
//           (removal) from the queue at an arbitrary position in O(1) given
//           the user of the queue maintains the list of nodes.

#ifndef PLUCKABLEQUEUE_H
#define PLUCKABLEQUEUE_H

namespace assl {

    template<typename T>
    class PluckableQueue {
        public:
            struct node {
                friend class PluckableQueue;
                private:
                    PluckableQueue<T>* queue;
                    node* next;
                    node* prev;
                    T t;

                    // Prevent other instantiation
                    node();
                    node(const node& other);
                    node& operator=(node& other);
                public:
                    node(const T& t);
                    T& get();
                    const T& get() const;
            };

        private:
            unsigned int count;
            node* top;
            node* bottom;

            // Prevent copy and assignment
            PluckableQueue(const PluckableQueue& other);
            PluckableQueue& operator=(const PluckableQueue& other);

        public:
            PluckableQueue();
            // Can use implicit destructor, we aren't managing the nodes.

            void push(node* node);
            node* pop();
            unsigned int size() const;

            void pluck(node* node);
            bool contains(node* node) const;
    };

    #include "PluckableQueue.impl.h"
};

#endif
