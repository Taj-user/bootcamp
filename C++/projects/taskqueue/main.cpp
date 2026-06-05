#include <iostream>
#include <chrono>
#include "TaskQueue.h"


int main(void) {
    TaskQueue taskq;

    taskq.enqueue([]() { std::cout << "Hello\n"; });
    taskq.enqueue([]() { std:: cout << "Bread\n"; });
    taskq.enqueue([]() { std:: cout << "World\n"; });
    taskq.enqueue([]() { std:: cout << "Message\n"; });
    taskq.enqueue([]() { std:: cout << "Something\n"; });

    taskq.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    taskq.stop();

    return 0;
}
