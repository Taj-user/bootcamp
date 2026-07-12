#pragma once
#include <cstddef>

template<typename T, size_t N>
class StaticVector {
        public:
                T&      operator[](size_t index);
                T*      at(size_t index);
                size_t  size() const;
                bool    push_back(const T& value);
                bool    pop_back(T& out);
                bool    full() const;
                bool    empty() const;

        private:
                T       data[N];
                size_t  m_size = 0;
};

template<typename T, size_t N>
T& StaticVector<T, N>::operator[](size_t index) {
        return data[index];
}

template<typename T, size_t N>
T* StaticVector<T, N>::at(size_t index) {
        if(index >= m_size) return nullptr;
        return &data[index];
}

template<typename T, size_t N>
size_t StaticVector<T, N>::size() const {
        return m_size;
}

template<typename T, size_t N>
bool StaticVector<T, N>::push_back(const T& value) {
        if(m_size == N) return false;
        data[m_size] = value;
        m_size++;
        return true;
}

template<typename T, size_t N>
bool StaticVector<T, N>::pop_back(T& out) {
        if(m_size == 0) return false;
        out = data[m_size - 1];
        m_size--;
        return true;
}

template<typename T, size_t N>
bool StaticVector<T, N>::full() const {
        return m_size == N;
}

template<typename T, size_t N>
bool StaticVector<T, N>::empty() const {
        return m_size == 0;
}
