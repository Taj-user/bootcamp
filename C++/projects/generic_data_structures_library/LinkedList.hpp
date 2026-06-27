#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class LinkedList {
        struct Node {
                T data;
                Node* next;
        };

        public:
                LinkedList()
                        : head(nullptr)
                        , tail(nullptr)
                {}

                LinkedList(std::initializer_list<T> list)
                        : head(nullptr)
                        , tail(nullptr)
                {
                        for(const T& value : list) push_back(value);
                }

                LinkedList(const LinkedList& source)
                        : head(nullptr)
                        , tail(nullptr)
                {
                        Node* temp = source.head;
                        while(temp != nullptr) {
                                push_back(temp->data);
                                temp = temp->next;
                        }
                }

                LinkedList& operator=(const LinkedList& source) {
                        if(this == &source) return *this;
                        while(!empty()) {
                                pop_front();
                        }
                        Node* temp = source.head;
                        while(temp != nullptr) {
                                push_back(temp->data);
                                temp = temp->next;
                        }
                        return *this;
                }

                LinkedList(LinkedList&& source)
                        : head(source.head)
                        , tail(source.tail)
                {
                        source.head = nullptr;
                        source.tail = nullptr;
                }

                LinkedList& operator=(LinkedList&& source) {
                        if(this == &source) return *this;
                        while(!empty()) {
                                pop_front();
                        }
                        head = source.head;
                        tail = source.tail;
                        source.head = nullptr;
                        source.tail = nullptr;
                        return *this;
                }

                ~LinkedList() {
                        while(!empty()) {
                                pop_front();
                        }
                }

                void push_back(T value) {
                        if(head == nullptr && tail == nullptr) {
                                Node* n = new Node;
                                n->data = value;
                                n->next = nullptr;
                                head = n;
                                tail = n;
                        }
                        else {
                                Node* n = new Node;
                                n->data = value;
                                n->next = nullptr;
                                tail->next = n;
                                tail = n;
                        }
                }

                void pop_front() {
                        if(head == nullptr && tail == nullptr) throw std::out_of_range("No elements to pop");
                        else {
                                if(head->next == nullptr) {
                                        Node* temp = head;
                                        head = nullptr;
                                        tail = nullptr;
                                        delete temp;
                                }
                                else {
                                        Node* temp = head;
                                        head = temp->next;
                                        delete temp;
                                }
                        }
                }

                T& front() {
                        return head->data;
                }

                const T& front() const {
                        return head->data;
                }

                size_t size() const {
                        if(head == nullptr && tail == nullptr) return 0;
                        size_t count = 1;
                        Node* i = head;
                        while(i->next != nullptr) {
                                i = i->next;
                                count++;
                        }
                        return count;
                }

                bool empty() const {
                        return head == nullptr && tail == nullptr;
                }

                class Iterator {
                        public:
                                Iterator(Node* n)
                                        : current(n)
                                {}

                                void operator++() {
                                        current = current->next;
                                }

                                bool operator!=(Iterator iterator) {
                                        return current != iterator.current;
                                }

                                T& operator*() {
                                        return current->data;
                                }

                        private:
                                Node* current;
                };

                Iterator begin() {
                        Iterator it(head);
                        return it;
                }

                Iterator end() {
                        Iterator it(nullptr);
                        return it;
                }

                Iterator begin() const {
                        Iterator it(head);
                        return it;
                }

                Iterator end() const {
                        Iterator it(nullptr);
                        return it;
                }

        private:
                Node* head;
                Node* tail;
};
