#pragma once
#include "LinkedList.hpp"

template<typename T>
class Queue {
        public:
                Queue()
                        : ll()
                {}

                Queue(std::initializer_list<T> list) 
                        : ll(list)
                {}

                void enqueue(T value) {
                        ll.push_back(value);
                }

                void dequeue() {
                        ll.pop_front();
                }

                T& front() {
                        return ll.front();
                }

                const T& front() const {
                        return ll.front();
                }

                bool empty() const {
                        return ll.empty();
                }

                size_t size() const {
                        return ll.size();
                }

        private:
                LinkedList<T> ll;
};
