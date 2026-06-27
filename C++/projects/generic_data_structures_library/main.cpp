#include <iostream>
#include "LinkedList.hpp"
// #include "Queue.hpp"
// #include "Stack.hpp"
// #include "Vector.hpp"

int main(void) {
        // Testing
        LinkedList<int> list;
        // Queue<int> queue;
        // Stack<int> stack;
        // Vector<int> vec;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);

        for(auto element : list) {
                std::cout << element << " ";
        }
        return 0;
}
