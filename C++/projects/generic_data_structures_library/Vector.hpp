#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template<typename T>
class Vector {
        public:
                Vector()
                        : m_data(nullptr)
                        , m_size(0)
                        , m_capacity(0)
                {}

                Vector(std::initializer_list<T> list)
                        : m_data(nullptr)
                        , m_size(0)
                        , m_capacity(0)
                {
                        for(const T& value : list) push_back(value);
                }

                Vector(const Vector& source)
                        : m_data(nullptr)
                        , m_size(0)
                        , m_capacity(source.capacity())
                {
                        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
                        for(const T& value : source) {
                                push_back(value);
                        }
                }

                Vector& operator=(const Vector& source) {
                        if(this == &source) return *this;
                        for(size_t i = m_size; i > 0; --i) {
                                m_data[i - 1].~T();
                        }
                        ::operator delete(m_data);

                        m_size = 0;
                        m_capacity = source.capacity();
                        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));

                        for(const T& value : source) {
                                push_back(value);
                        }
                        return *this;
                }

                Vector(Vector&& source)
                        : m_data(source.m_data)
                        , m_size(source.m_size)
                        , m_capacity(source.m_capacity)
                {
                        source.m_data = nullptr;
                        source.m_size = 0;
                        source.m_capacity = 0;
                }

                Vector& operator=(Vector&& source) {
                        if(this == &source) return *this;
                        for(size_t i = m_size; i > 0; --i) {
                                m_data[i - 1].~T();
                        }
                        ::operator delete(m_data);

                        m_data = source.m_data;
                        m_size = source.m_size;
                        m_capacity = source.m_capacity;

                        source.m_data = nullptr;
                        source.m_size = 0;
                        source.m_capacity = 0;

                        return *this;
                }

                ~Vector() {
                        for(size_t i = m_size; i > 0; --i) {
                                m_data[i - 1].~T();
                        }
                        ::operator delete(m_data);
                }

                void push_back(T value) {
                        if(m_capacity > m_size) {
                                new (m_data + m_size) T(value);                                                 // construct element
                                m_size++;
                        }
                        else if(m_capacity == m_size){
                                if(m_capacity == 0) m_capacity = 8;                                             // update initial capacity
                                else m_capacity *= 2;                                                           // update capacity if it's full

                                T* new_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));          // resize buffer
                                for(size_t i = 0; i < m_size; i++) {                                            // move data from old buffer to new buffer
                                        new(new_data + i) T(std::move(*(m_data + i)));
                                }

                                for(size_t i = 0; i < m_size; i++) {                                            // destructor loop
                                        m_data[i].~T();
                                }
                                ::operator delete(m_data);

                                m_data = new_data;                                                              // point to new buffer
                                new(m_data + m_size) T(value);                                                  // construct new element
                                m_size++;
                        }
                }

                void pop_back() {
                        if(m_size == 0) throw std::out_of_range("No elements in vector to pop");
                        m_data[m_size - 1].~T();
                        m_size--;
                }

                T& operator[](const size_t index) {                                                             // for vec[index]
                        if(index > m_size) throw std::out_of_range("Index out of range");
                        return *(m_data + index);
                }

                const T& operator[](const size_t index) const {
                        if(index > m_size) throw std::out_of_range("Index out of range");
                        return *(m_data + index);
                }

                size_t size() const {
                        return m_size;
                }

                size_t capacity() const {
                        return m_capacity;
                }

                class Iterator {
                        public:
                                Iterator(T* i)
                                        : current(i)
                                {}

                                void operator++() {
                                        current++;
                                }

                                bool operator!=(Iterator iterator) {
                                        return current != iterator.current;
                                }

                                T& operator*() {
                                        return *current;
                                }

                        private:
                                T* current;
                };

                Iterator begin() {                                                                              // iterator to the first element
                        Iterator it(m_data + 0);
                        return it;
                }

                Iterator end() {                                                                                // iterator to one position after the last element
                        Iterator it(m_data + m_size);
                        return it;
                }

                Iterator begin() const {
                        Iterator it(m_data + 0);
                        return it;
                }

                Iterator end() const {
                        Iterator it(m_data + m_size);
                        return it;
                }

        private:
                T* m_data;                                                                                      // memory buffer
                size_t m_size;                                                                                  // memory size
                size_t m_capacity;                                                                              // memory capacity
};
