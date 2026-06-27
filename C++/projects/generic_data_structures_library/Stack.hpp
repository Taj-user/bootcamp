#pragma once
#include <initializer_list>
#include "Vector.hpp"

template<typename T>
class Stack {
        public:
                Stack()
                        : vec()
                {}

                Stack(std::initializer_list<T> list)
                        : vec(list)
                {}

                void push(T value) {
                        vec.push_back(value);
                }

                void pop() {
                        vec.pop_back();
                }

                T& top() {
                        return vec[vec.size() - 1];
                }

                const T& top() const {
                        return vec[vec.size() - 1];
                }

                bool empty() const {
                        return vec.size() == 0;
                }

                size_t size() const {
                        return vec.size();
                }

        private:
                Vector<T> vec;
};
