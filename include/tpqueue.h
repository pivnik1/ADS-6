// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
    struct Node {
        T item;
        Node* next;
        explicit Node(const T& item) : item(item), next(nullptr) {}
    };

    Node* head;

 public:
    TPQueue() : head(nullptr) {}

    void push(const T& item) {
        Node* newNode = new Node(item);

        if (!head || item.prior > head->item.prior) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && current->next->item.prior >= item.prior) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    T pop() {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }

        Node* temp = head;
        T item = temp->item;
        head = head->next;
        delete temp;
        return item;
    }

    ~TPQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
