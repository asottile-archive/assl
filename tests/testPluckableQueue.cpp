#include<cassert>
#include "PluckableQueue.h"

using assl::PluckableQueue;

int main() {

    // Tests that on construction, the queue is empty
    PluckableQueue<int> queue;
    PluckableQueue<int> otherQueue;
    PluckableQueue<int>::node* node = nullptr;
    PluckableQueue<int>::node* node2 = nullptr;
    PluckableQueue<int>::node* node3 = nullptr;

    assert(queue.size() == 0);

    // Constructs a node
    // Make sure the getter works.
    node = new PluckableQueue<int>::node(5);
    assert(node->get() == 5);
    assert(!queue.contains(node));
    assert(!otherQueue.contains(node));

    // Now push to the queue
    queue.push(node);
    assert(queue.size() == 1);
    assert(queue.contains(node));
    assert(!otherQueue.contains(node));

    node2 = queue.pop();
    assert(node2 == node);
    assert(!queue.contains(node));
    assert(!otherQueue.contains(node));

    delete node;
    node = nullptr;
    node2 = nullptr;

    node = new PluckableQueue<int>::node(1);
    node2 = new PluckableQueue<int>::node(2);
    node3 = new PluckableQueue<int>::node(3);

    queue.push(node);
    queue.push(node2);
    queue.push(node3);
    assert(queue.size() == 3);
    assert(queue.contains(node));
    assert(queue.contains(node2));
    assert(queue.contains(node3));

    queue.pluck(node2);
    assert(!queue.contains(node2));
    assert(queue.size() == 2);

    PluckableQueue<int>::node* temp = queue.pop();
    assert(temp->get() == 1);
    assert(queue.size() == 1);
    assert(!queue.contains(temp));
    assert(temp == node);
    temp = queue.pop();
    assert(temp->get() == 3);
    assert(queue.size() == 0);
    assert(!queue.contains(temp));
    assert(temp == node3);

    delete node;
    node = nullptr;
    delete node2;
    node2 = nullptr;
    delete node3;
    node3 = nullptr;
    return 0;
}
