#pragma once
#include <cstddef>

template<typename T, size_t N>
requires (N > 0 && (N & (N - 1)) == 0)
class RingBuffer {
        public:
                bool push(const T& value);
                bool pop(T& out);
                bool empty() const;
                bool full() const;
                size_t size() const;

        private:
                T data[N];
                size_t head = 0;
                size_t tail = 0;
                size_t count = 0;
};

template<typename T, size_t N>
requires (N > 0 && (N & (N - 1)) == 0)
bool RingBuffer<T, N>::empty() const {
        return count == 0;
}

template<typename T, size_t N>
requires (N > 0 && (N & (N - 1)) == 0)
bool RingBuffer<T, N>::full() const {
        return count == N;
}

template<typename T, size_t N>
requires (N > 0 && (N & (N - 1)) == 0)
bool RingBuffer<T, N>::push(const T& value) {
        if(count == N) return false;
        data[tail] = value;
        tail = (tail + 1) & (N - 1);
        count++;
        return true;
}

template<typename T, size_t N>
requires (N > 0 && (N & (N - 1)) == 0)
bool RingBuffer<T, N>::pop(T& out) {
        if(count == 0) return false;
        out = data[head];
        head = (head + 1) & (N - 1);
        count--;
        return true;
}

template<typename T, size_t N>
requires (N > 0 && (N & (N - 1)) == 0)
size_t RingBuffer<T, N>::size() const {
        return count;
}
