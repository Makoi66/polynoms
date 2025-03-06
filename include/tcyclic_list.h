#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>

template <typename T>
class CyclicList {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(T value = nullptr, Node* next = nullptr) : data(value), next(next) {}
    };

    Node* head = nullptr;
    size_t size_ = 0;

public:
    CyclicList() = default;

    ~CyclicList() {
        clear();
    }

    CyclicList(CyclicList& oth) {
        if (oth.empty()) {
            return;
        }
        else {
            Node* curr = oth.head;
            do {
                push_back(curr->data);
                curr = curr->next;
            } while (curr != oth.head);
        }
    }

    CyclicList& operator=(CyclicList& oth) {
        if (this == &oth) {
            return *this;
        }

        clear();

        if (oth.empty()) {
            return *this;
        }
        Node* curr = oth.head;
        head = new Node(curr->data);
        head->next = head;
        size_++;
        curr = curr->next;
        do {
            push_back(curr->data);
            curr = curr->next;
        } while (curr != oth.head);
        return *this;
    }

    bool empty() const{
        return (size_ == 0);
    }

    void clear() {
        if (size_ == 0) return;

        Node* curr = head;
        Node* nextCurr;

        do {
            nextCurr = curr->next;
            delete curr;
            curr = nextCurr;
        } while (curr != head);
        head = nullptr;
        size_ = 0;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = newNode;
            head->next = head;
        }
        else {
            Node* curr = head;
            do {
                curr = curr->next;
            } while (curr->next != head);

            newNode->next = head;
            curr->next = newNode;
        }
        size_++;
    }

    void push_front(const T& value) {
        if (empty()) {
            push_back(value);
        }
        else {
            Node* newNode = new Node(value);
            newNode->next = head;

            Node* curr = head;
            do {
                curr = curr->next;
            } while (curr->next != head);
            
            head = newNode;
            curr->next = head;
            size_++;
        }
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        Node* curr = head;
        do {
            curr = curr->next;
        } while (curr->next->next != head);
        delete curr->next;
        curr->next = head;
        size_--;

    }

    void pop_front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        Node* curr = head;
        do {
            curr = curr->next;
        } while (curr->next != head);
        head = head->next;
        delete curr->next;
        curr->next = head;
        size_--;
    }


    size_t size() const {
        return size_;
    }


    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }

        Node* curr = head;
        
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }

        Node* curr = head;

        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }


    int find(const T& value) const{
        if (empty()) {
            return -1;
        }

        Node* curr = head;
        int index = 0;
        do {
            if (curr->data == value) return index;
            curr = curr->next;
            index++;
        } while (curr != head);

        return -1;
    }



    void insert(size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            push_front(value);
        }
        else if (index == size_) {
            push_back(value);
        }
        else {
            Node* newNode = new Node(value);
            Node* curr = head;
            for (int i = 0; i < index - 1; i++) {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
            size_++;
        }
    }

    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            pop_front();
        }
        else if (index == size_ - 1) {
            pop_back();
        }
        else {
            Node* curr = head;
            for (int i = 0; i < index - 1; i++) {
                curr = curr->next;
            }
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
            size_--;
        }
    }


    void sort(const bool reverse = false) {
        if (empty()) {
            return;
        }

        bool swapped;
        Node* curr;

        do {
            swapped = false;
            curr = head;

            do {
                if ((!reverse) == (curr->data > curr->next->data)) {
                    std::swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            } while (curr->next != head);
        } while (swapped);
    }


    void reverse() {
        if (empty()) {
            return;
        }

        Node* f = head;
        Node* s = head->next;
        Node* t = head->next->next;
        do {
            s->next = std::move(f);
            f = s;
            s = t;
            t = s->next;
        } while (s != head);
        head = f;
        s->next = head;
    }

    size_t count(const T& value) const {
        if (empty()) return 0;

        size_t n = 0;
        Node* curr = head;
        do {
            if (curr->data == value) {
                n++;
            }
            curr = curr->next;
        } while (curr != head);
        return n;
    }


    void print() const {
        Node* curr = head;
        do {
            std::cout << curr->data << " ";
            curr = curr->next;
        } while (curr != head);
        std::cout << std::endl;
    }
};