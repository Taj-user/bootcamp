#pragma once
#include <iostream>
#include <utility>

template<typename T>
class Vector {
        public:
                Vector()
                        : m_data(nullptr)
                        , m_size(0)
                        , m_capacity(0)
                {}

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

                T& operator[](const size_t index) {
                        // TODO: Finish
                }

        private:
                T* m_data;                                                                                      // memory buffer
                size_t m_size;                                                                                  // memory size
                size_t m_capacity;                                                                              // memory capacity
};
